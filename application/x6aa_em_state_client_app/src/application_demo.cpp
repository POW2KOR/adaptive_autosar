/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH. All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file
 *        \brief  A demo adaptive application to the execution management.
 *
 *      \details  Handles signals, reports its application states, uses the failure handler client.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include <unistd.h>
#include <atomic>
#include <chrono>
#include <csignal>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "application_demo.h"
#include "ara/exec/application_client.h"
#include "ara/exec/state_client.h"

namespace application_demo {

AdaptiveApplication::AdaptiveApplication()
    : application_client_(),
      state_client_(),
      exit_requested_(false),
      threads_(),
      is_state_client_(false),
      log_(ara::log::CreateLogger("EMDA", "Logging context for the EXEC Demo App AdaptiveApplication")),
      failure_handler_{exit_requested_} {}

AdaptiveApplication::AdaptiveApplication(bool is_state_client)
    : application_client_(),
      state_client_(),
      exit_requested_(false),
      threads_(),
      is_state_client_(is_state_client),
      log_(ara::log::CreateLogger("EMDA", "Logging context for the EXEC Demo App AdaptiveApplication")),
      failure_handler_{exit_requested_} {
  if (is_state_client) {
    state_client_.emplace();
  }
}

void AdaptiveApplication::SignalHandlerThread() {
  sigset_t signal_set;
  int sig = -1;
  sigemptyset(&signal_set);        /* empty the set of signals */
  sigaddset(&signal_set, SIGTERM); /* Add only SIGTERM to set */
  while (sig != SIGTERM) {
    sigwait(&signal_set, &sig);
    log_.LogDebug(
        [&](ara::log::LogStream &s) { s << "AdaptiveApplication::SignalHandlerThread: Caught Signal: " << sig; });
  }
  exit_requested_ = true;
  log_.LogDebug([&](ara::log::LogStream &s) {
    s << "AdaptiveApplication::SignalHandlerThread: application with pid " << getpid() << " received signal SIGTERM";
  });
}

void AdaptiveApplication::PeriodicWork(PeriodicWorkStateType &state) {
  /* Do the actual work. */
  state.my_data = 0;
}

void AdaptiveApplication::PeriodicThread() {
  /* store the current point of time in next_run */
  std::chrono::steady_clock::time_point next_run(std::chrono::steady_clock::now());
  /* define a time interval of 100 milliseconds */
  std::chrono::steady_clock::duration duration(std::chrono::milliseconds(100));
  /* define a state variable to store information across runs of PeriodicWork() */
  PeriodicWorkStateType cross_iteration_state;

  while (!exit_requested_) {
    /* do some work here */
    PeriodicWork(cross_iteration_state);
    /* calculate the next point of time to be rescheduled */
    next_run += duration;
    /* Blocks the execution of the current thread until specified point of time (next_run) has been reached */
    std::this_thread::sleep_until(next_run);
  }
}

void AdaptiveApplication::Start() { Initialize(); }

void AdaptiveApplication::Initialize() {
  log_.LogDebug([&](ara::log::LogStream &s) { s << "AdaptiveApplication::Initialize"; });
  /* Block all signals for this thread. Signal mask will be inherited by subsequent threads. */
  sigset_t signals;
  sigfillset(&signals);
  pthread_sigmask(SIG_SETMASK, &signals, NULL);
  /* reserve space in std::vector */
  threads_.reserve(kNumOfThreads);
  /* spawn a new signal handler thread*/
  threads_.emplace_back(&AdaptiveApplication::SignalHandlerThread, this);

  /* As there can be only one failure handler client, initialize it only if this app is started as state client */
  if (is_state_client_) {
    /* Initialize Failure Handler */
    failure_handler_.Initialize();

    /* Spawn a thread to handle failure client events */
    threads_.emplace_back(&FailureHandler::PeriodicThread, &failure_handler_);
  }

  /* May spawn some more threads here */
  threads_.emplace_back(&AdaptiveApplication::PeriodicThread, this);

  Run();
}

void AdaptiveApplication::Run() {
  ara::exec::ApplicationReturnType ret =
      application_client_.ReportApplicationState(ara::exec::ApplicationState::kRunning);
  if (ret == ara::exec::ApplicationReturnType::kGeneralError) {
    log_.LogWarn([&](ara::log::LogStream &s) { s << "AdaptiveApplication::Run: Error reporting application state"; });
  } else {
    log_.LogDebug([&](ara::log::LogStream &s) { s << "AdaptiveApplication::Run"; });
  }
  /* store the current point of time in next_run */
  std::chrono::steady_clock::time_point next_run(std::chrono::steady_clock::now());
  /* define a time interval of 5 seconds */
  std::chrono::steady_clock::duration duration(std::chrono::seconds(5));

  std::string function_group = "MachineState";
  std::string machine_state;

  // GetMachineState
  if (is_state_client_) {
    bool ongoing_transition{true};
    while (ongoing_transition) {
      ara::exec::StateReturnType returned_state_error = state_client_->GetState(function_group, machine_state);
      if (returned_state_error == ara::exec::StateReturnType::kSuccess) {
        log_.LogDebug([&](ara::log::LogStream &s) {
          s << "AdaptiveApplication::Run: GetState success. Machine State is ";
          s << ara::core::StringView{machine_state};
        });
        ongoing_transition = false;
      } else if (returned_state_error == ara::exec::StateReturnType::kBusy) {
        log_.LogDebug([&](ara::log::LogStream &s) {
          s << "AdaptiveApplication::Run: GetState: There is currently a machine mode change ongoing";
        });
        // Initial state change to startup. Give the initiale state change some time to finish.
        std::this_thread::sleep_for(std::chrono::seconds(1));
      } else {
        log_.LogDebug([&](ara::log::LogStream &s) { s << "AdaptiveApplication::Run: GetState: Unknown Error"; });
        // Consider an error also as finished transition.
        ongoing_transition = false;
      }
    }
    /* Get current process states */
    failure_handler_.LogProcessStates();
  }

  bool running_reached{false};
  while (!exit_requested_) {
    // SetMachineState to running.
    if (is_state_client_ && !running_reached) {
      ara::exec::StateReturnType returned_state_error = state_client_->SetState(function_group, "Running");
      if (returned_state_error == ara::exec::StateReturnType::kSuccess) {
        log_.LogDebug([&](ara::log::LogStream &s) {
          s << "AdaptiveApplication::Run: SetState success. Machine State is Running";
        });
        running_reached = true;
      } else if (returned_state_error == ara::exec::StateReturnType::kBusy) {
        log_.LogDebug([&](ara::log::LogStream &s) {
          s << "AdaptiveApplication::Run: SetState: There is currently an machine mode change ongoing";
        });
      } else {
        log_.LogDebug([&](ara::log::LogStream &s) { s << "AdaptiveApplication::Run: SetState: Unknown Error"; });
      }
      /* Get current process states */
      failure_handler_.LogProcessStates();
    }

    /* do some work here */
    /* calculate the next point of time to be rescheduled */
    next_run += duration;
    /* Blocks the execution of the current thread until specified point of time (next_run) has been reached */
    std::this_thread::sleep_until(next_run);

    // GetMachineState
    std::string new_machine_state;
    if (is_state_client_ && !running_reached) {
      ara::exec::StateReturnType returned_state_error = state_client_->GetState(function_group, new_machine_state);
      if (returned_state_error == ara::exec::StateReturnType::kSuccess) {
        log_.LogDebug([&](ara::log::LogStream &s) {
          s << "AdaptiveApplication::Run: GetState success. Machine State is ";
          s << ara::core::StringView{new_machine_state};
        });
        if (new_machine_state == "Running") {
          running_reached = true;
        }
      } else if (returned_state_error == ara::exec::StateReturnType::kBusy) {
        log_.LogDebug([&](ara::log::LogStream &s) {
          s << "AdaptiveApplication::Run: GetState: There is currently an machine mode change ongoing";
        });
      } else {
        log_.LogDebug([&](ara::log::LogStream &s) { s << "AdaptiveApplication::Run: GetState: Unknown Error"; });
      }
      /* Get current process states */
      failure_handler_.LogProcessStates();
    } else {
      sleep(1);
    }
  }

  Shutdown();
}

void AdaptiveApplication::Shutdown() {
  ara::exec::ApplicationReturnType ret =
      application_client_.ReportApplicationState(ara::exec::ApplicationState::kTerminating);
  if (ret == ara::exec::ApplicationReturnType::kGeneralError) {
    log_.LogWarn(
        [&](ara::log::LogStream &s) { s << "AdaptiveApplication::Shutdown: Error reporting application state"; });
  } else {
    log_.LogDebug([&](ara::log::LogStream &s) { s << "AdaptiveApplication::Shutdown: Shutdown reported"; });
  }

  /* do application clean-up in here */
  /* wait till other threads have joined */
  for (std::vector<std::thread>::iterator it = threads_.begin(); it != threads_.end(); ++it) {
    it->join();
  }
}

}  // namespace application_demo
