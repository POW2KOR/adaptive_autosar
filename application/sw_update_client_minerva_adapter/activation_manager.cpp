/***************************************************************************/ /**
                                                                               * \file
                                                                               *activation_manager.cpp
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
/* include own header first to make sure it is self contained */
#include "activation_manager.h"

/* C system includes */

/* C++ system includes */
#include <cmath>

/* Project specific includes */

ActivationManagerBase::ActivationManagerBase(
    std::chrono::nanoseconds cycle_time, const std::string name)
    : name_(name)
    , cycle_time_(cycle_time)
{
#ifdef SPDLOG
    logger_ = spdlog::stdout_color_mt(name_);
#endif /* SPDLOG */
}

ActivationManagerBase::~ActivationManagerBase()
{
}

void ActivationManagerBase::initializeDesiredWakeup()
{
    if (0 == desired_wakeup_.tv_sec && 0 == desired_wakeup_.tv_nsec) {
        /* get the current time of day and use it for later sleeps. All sleeps will use this time as
         * base and only add (multiple) cycle times */
        clock_gettime(CLOCK_MONOTONIC, &desired_wakeup_);
        desired_wakeup_.tv_nsec += cycle_time_.count();
        desired_wakeup_.tv_sec += desired_wakeup_.tv_nsec
            / std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)).count();
        desired_wakeup_.tv_nsec
            %= std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1))
                   .count();
    }
}

void ActivationManagerBase::updateActualWakeup()
{
    /* get the current time right after wakeup */
    clock_gettime(CLOCK_MONOTONIC, &actual_wakeup_);
}

void ActivationManagerBase::calculateJitter()
{
    /* calculate the jitter between desired and actual wakeup time */
    if (actual_wakeup_.tv_sec == desired_wakeup_.tv_sec) {
        jitter_time_nsec_ = actual_wakeup_.tv_nsec - desired_wakeup_.tv_nsec;
    } else {
        if (actual_wakeup_.tv_sec == desired_wakeup_.tv_sec + 1) {
            jitter_time_nsec_ = actual_wakeup_.tv_nsec
                + std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1))
                      .count()
                - desired_wakeup_.tv_nsec;
        } else {
            if (actual_wakeup_.tv_sec == desired_wakeup_.tv_sec - 1) {
                jitter_time_nsec_ = actual_wakeup_.tv_nsec
                    - std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1))
                          .count()
                    - desired_wakeup_.tv_nsec;
            } else {
#ifdef SPDLOG
                logger_->critical("total overrun of clock occured (>1s) !!!!");
                logger_->critical(
                    "expected: {:}.{:06d}, actual: {:}.{:06d}.",
                    desired_wakeup_.tv_sec,
                    desired_wakeup_.tv_nsec,
                    actual_wakeup_.tv_sec,
                    actual_wakeup_.tv_nsec);
#endif /* SPDLOG */
                exit(1);
            }
        }
    }

    /* store the current maximum jitter of wakeup time */
    if (std::abs(jitter_time_max_nsec_) < std::abs(jitter_time_nsec_)) {
        jitter_time_max_nsec_ = jitter_time_nsec_;
#ifdef SPDLOG
        logger_->info("new maximum wakeup jitter is {:d} ns", jitter_time_max_nsec_);
#endif /* SPDLOG */
    }

    /* calculate the number off missed wakeups */
    if (jitter_time_nsec_ > 0) {
        missed_ = jitter_time_nsec_ / cycle_time_.count();
    } else {
        missed_ = 0;
    }
    if (0 != missed_) {
        total_missed_ += missed_;
#ifdef SPDLOG
        logger_->critical(
            "missed {:d} wakeups, now total missed {:12d} wakeups (too late by {} ns)",
            missed_,
            total_missed_,
            jitter_time_nsec_);
#endif /* SPDLOG */
    }

    /* print warning if we did not miss a wakeup but we have only left less than 90% of the cycle
     * time */
    if ((0 == missed_) && (0 < jitter_time_nsec_)
        && (static_cast<int64_t>(jitter_time_nsec_) > (cycle_time_.count() / 10))) {
#ifdef SPDLOG
        logger_->warn(
            "when activated only less than 90 % of cycle time is left (cycle: {} µs, delay: {} µs)",
            std::chrono::duration_cast<std::chrono::microseconds>(cycle_time_).count(),
            jitter_time_nsec_ / 1000);
#endif /* SPDLOG */
    }
}

ActivationManagerTimer::ActivationManagerTimer(
    std::chrono::nanoseconds cycle_time, const std::string name)
    : ActivationManagerBase(cycle_time, name)
{
}

ActivationManagerTimer::~ActivationManagerTimer()
{
}

void ActivationManagerTimer::wait()
{
    /* initialize the desired wakeup time if needed */
    initializeDesiredWakeup();

    /* go to sleep until the next absolute wakeup time is reached */
    while (EINTR == clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &desired_wakeup_, NULL))
        ;

    /* update actual wakeup time */
    updateActualWakeup();

    /* calculate the jitter between desired and actual wakeup time */
    calculateJitter();

    /* advance the wakeup time. Take into account that we might have missed some
     * wakeups. Therefore the next desired wakeup time is incremented by one
     * cycle duration plus the number of missed wakeups multiplied by the cycle duration. */
    desired_wakeup_.tv_nsec += (missed_ + 1) * cycle_time_.count();
    desired_wakeup_.tv_sec += desired_wakeup_.tv_nsec
        / std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)).count();
    desired_wakeup_.tv_nsec
        %= std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1)).count();

    /* increment the cycle counter */
    cycle_count_++;
}

uint64_t ActivationManagerTimer::getCycle()
{
    return cycle_count_;
}
