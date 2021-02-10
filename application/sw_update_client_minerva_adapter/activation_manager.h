/***************************************************************************/ /**
                                                                               * \file
                                                                               *activation_manager.hpp
                                                                               *
                                                                               * \brief  Activation
                                                                               *manager classes for
                                                                               *timer driven
                                                                               *activation \author
                                                                               *Markus Braun \date
                                                                               *2020-11-16 \note
                                                                               *TODO: additional
                                                                               *notes
                                                                               ******************************************************************************/
#ifndef ACTIVATIONMANAGER_HPP
#define ACTIVATIONMANAGER_HPP

/* C system includes */
#include <sys/time.h>

/* C++ system includes */
#include <chrono>
#include <string>
#include <vector>

/* Project specific includes */
#ifdef SPDLOG
#include <spdlog/spdlog.h>
#endif /* SPDLOG */

/***************************************************************************/ /**
                                                                               * \brief Activation
                                                                               *manager base class.
                                                                               ******************************************************************************/
class ActivationManagerBase {
protected:
    std::string name_; /**< Name of the activation manager */
#ifdef SPDLOG
    std::shared_ptr<spdlog::logger> logger_; /**< Logger for all log messages */
#endif /* SPDLOG */
    const std::chrono::nanoseconds cycle_time_{0}; /**< Cycle time for the activation */
    uint64_t cycle_count_{0}; /**< Counter for activation cycles */
    struct timespec desired_wakeup_ {
    }; /**< Desired absolute wakeup time */
    struct timespec actual_wakeup_ {
    }; /**< Actual absolute wakeup time */
    uint64_t missed_{0}; /**< Number of missed wakeups */
    uint64_t total_missed_{0}; /**< Total number off missed wakeups */
    int64_t jitter_time_nsec_{0}; /**< Jitter time between desired and actual wakeup [ns] */
    int64_t jitter_time_max_nsec_{0}; /**< Maximum wakeup jitter [ns] */

public:
    /***************************************************************************/ /**
                                                                                   * \brief Deleted
                                                                                   *default
                                                                                   *constructor.
                                                                                   ******************************************************************************/
    ActivationManagerBase() = delete;

    /***************************************************************************/ /**
                                                                                   * \brief
                                                                                   *Constructor.
                                                                                   ******************************************************************************/
    ActivationManagerBase(
        std::chrono::nanoseconds cycle_time, const std::string name = "activation manager");

    /***************************************************************************/ /**
                                                                                   * \brief
                                                                                   *Destructor.
                                                                                   ******************************************************************************/
    virtual ~ActivationManagerBase();

    /***************************************************************************/ /**
                                                                                   * \brief Wait
                                                                                   *until activation
                                                                                   *happens.
                                                                                   *
                                                                                   * \note The
                                                                                   *implementations
                                                                                   *of this function
                                                                                   *MUST call
                                                                                   *       initializeDesiredWakeup()
                                                                                   *as first
                                                                                   *instruction
                                                                                   *after entering
                                                                                   *the method to
                                                                                   *ensure the
                                                                                   *desired_wakeup_
                                                                                   *is set up
                                                                                   *correctly!
                                                                                   *
                                                                                   * \note The
                                                                                   *implementations
                                                                                   *of this function
                                                                                   *MUST call
                                                                                   *       calculateJitter()
                                                                                   *as first
                                                                                   *instruction
                                                                                   *after the real
                                                                                   *wake up happend
                                                                                   *to ensure
                                                                                   *correct jitter
                                                                                   *calculation.
                                                                                   *
                                                                                   * \note The
                                                                                   *implementations
                                                                                   *of this function
                                                                                   *MUST update the
                                                                                   *       desired_wakeup_
                                                                                   *member to enable
                                                                                   *correct jitter
                                                                                   *calculation in
                                                                                   *the next cycle.
                                                                                   ******************************************************************************/
    virtual void wait() = 0;

    /***************************************************************************/ /**
                                                                                   * \brief Get
                                                                                   *cycle count
                                                                                   *based on
                                                                                   *activation type.
                                                                                   ******************************************************************************/
    virtual uint64_t getCycle() = 0;

protected:
    /***************************************************************************/ /**
                                                                                   * \brief
                                                                                   *Initialize the
                                                                                   *desired wakeup
                                                                                   *time if needed.
                                                                                   ******************************************************************************/
    void initializeDesiredWakeup();

    /***************************************************************************/ /**
                                                                                   * \brief Update
                                                                                   *the actual
                                                                                   *wakeup time.
                                                                                   ******************************************************************************/
    void updateActualWakeup();

    /***************************************************************************/ /**
                                                                                   * \brief
                                                                                   *Calculate wakeup
                                                                                   *jitter and
                                                                                   *missed
                                                                                   *activations.
                                                                                   ******************************************************************************/
    void calculateJitter();
};

/***************************************************************************/ /**
                                                                               * \brief Activation
                                                                               *manager purely based
                                                                               *on a timer. The
                                                                               *cycle time is
                                                                               *derived from the
                                                                               *parameters given in
                                                                               *the call to setup()
                                                                               ******************************************************************************/
class ActivationManagerTimer : public ActivationManagerBase {
protected:
public:
    /***************************************************************************/ /**
                                                                                   * \brief Deleted
                                                                                   *default
                                                                                   *constructor.
                                                                                   ******************************************************************************/
    ActivationManagerTimer() = delete;

    /***************************************************************************/ /**
                                                                                   * \brief
                                                                                   *Constructor.
                                                                                   ******************************************************************************/
    ActivationManagerTimer(
        std::chrono::nanoseconds cycle_time, const std::string name = "activation manager");

    /***************************************************************************/ /**
                                                                                   * \brief
                                                                                   *Destructor.
                                                                                   ******************************************************************************/
    virtual ~ActivationManagerTimer();

    /***************************************************************************/ /**
                                                                                   * \brief Wait
                                                                                   *until the timer
                                                                                   *expires.
                                                                                   ******************************************************************************/
    void wait();

    /***************************************************************************/ /**
                                                                                   * \brief Get
                                                                                   *monotonic
                                                                                   *incremented
                                                                                   *cycle count.
                                                                                   ******************************************************************************/
    uint64_t getCycle();
};

#endif /* end of include guard: ACTIVATIONMANAGER_HPP */
