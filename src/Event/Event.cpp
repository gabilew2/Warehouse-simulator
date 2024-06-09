/**
 * @file Event.cpp
 * @brief Source file of the Event class.
 */

#include "Event.h"
#include <QRandomGenerator>

/**
 * @brief Construct a new Event object.
 */
Event::Event(QString eventType, QDateTime time)
{
    this -> eventType = eventType;
    this -> time = time;
}

/**
 * @brief Generates an event with a random time offset.
 *
 * @param eventType The type of the event to generate.
 * @param seed The seed for the random number generator.
 * @return A new Event instance with the specified type and a random time.
 */
Event Event::generateEvent(QString eventType, int seed)
{
    QDateTime time = QDateTime::currentDateTime().addMSecs(QRandomGenerator::global() -> bounded(seed));
    return Event(eventType, time);
}

// Getters implementation

/**
 * @brief Retrieves the type of the event.
 *
 * @return The event type as a QString.
 */
QString Event::getEventType() const
{
    return eventType;
}

/**
 * @brief Retrieves the timestamp of the event.
 *
 * @return The event time as a QDateTime.
 */
QDateTime Event::getTime() const
{
    return time;
}
