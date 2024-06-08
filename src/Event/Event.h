/**
 * @file Event.h
 * @brief Header file of the Event class.
 */

#ifndef EVENT_H
#define EVENT_H

#include <QDateTime>

/**
 * @class Event
 * @brief The Event class represents an event in the warehouse simulation.
 *
 * This class encapsulates the details of an event, including its type and the time it occurred.
 */
class Event
{
private:
    QString eventType; ///< Type of the event.
    QDateTime time;    ///< Timestamp of the event occurrence.

public:
    /**
     * @brief Constructor for the Event class.
     *
     * Initializes a new instance of the Event class with the specified type and time.
     * @param eventType The type of the event.
     * @param time The timestamp when the event occurred.
     */
    Event(QString eventType, QDateTime time);

    /**
     * @brief Generates a random event based on the given seed.
     *
     * This static method creates a new event with a random time offset based on the provided seed.
     * @param eventType The type of the event to generate.
     * @param seed The seed for the random number generator.
     * @return A new Event instance with the specified type and a random time.
     */
    static Event generateEvent(QString eventType, int seed);

    // Getters
    QString getEventType() const; ///< Retrieves the type of the event.
    QDateTime getTime() const;    ///< Retrieves the timestamp of the event.
};

#endif // EVENT_H
