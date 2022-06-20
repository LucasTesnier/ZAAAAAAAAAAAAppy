/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** scheduler
*/

/// \file src/zappy_server_src/core/include/scheduler/scheduler.h

#ifndef SCHEDULER_H
    #define SCHEDULER_H

    #include <uuid/uuid.h>
    #include <sys/queue.h>
    #include <stdbool.h>

/// \brief represent a scheduler event that will be stored inside the scheduler
typedef struct scheduler_event_s {
    /// \brief The entity uuid bound to the event
    uuid_t id;

    /// \brief The amount of time to wait before the event is over
    int ticks;

    /// \brief The clock of the event
    time_t clock;

    /// \brief The collection of events
    TAILQ_ENTRY(scheduler_event_s) events;
} scheduler_event_t;

/// Scheduler events list definition
TAILQ_HEAD(scheduler_event_list, scheduler_event_s);

typedef struct scheduler_s {

    /// \brief The multiplicative inverse of a second
    double freq;

    /// \brief The list of events
    struct scheduler_event_list events;
} scheduler_t;

/// \brief Create a new scheduler with a given frequency
scheduler_t *create_scheduler(double freq);

/// \brief Destroy a previously created scheduler
void scheduler_delete(scheduler_t *scheduler);

/// \brief Schedule a new event bound to an uuid
/// \return true or false if the event has been scheduled
bool scheduler_schedule_event(scheduler_t *self, uuid_t uuid, int ticks);

/// /\brief Update the scheduler, decrementing the ticks of each event
/// and removing the ones that have reached 0
void scheduler_update(scheduler_t *self);

/// \brief Check if a given uuid has a pending event
/// \param uuid The uuid to check
/// \return return true or false if the event has been scheduled
bool scheduler_has_event(scheduler_t *self, uuid_t uuid);

/// \brief Return the amout of time before the event closest to finish is over
/// \note If the returned time is 0, either there is no event scheduled or self
/// is null
struct timeval scheduler_get_smallest_timeout(scheduler_t *self);

#endif /* SCHEDULER_H */
