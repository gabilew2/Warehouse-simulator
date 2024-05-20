#ifndef EVENT_H
#define EVENT_H

#include <QDateTime>

/**
 * @brief The Event class represents an event in the department store simulation.
 *
 * This class is responsible for handling events that occur within the simulation.
 * Each event has a type and a timestamp indicating when it occurred.
 */
class Event
{
private:
    QString eventType; ///< Type of the event.
    QDateTime time;    ///< Timestamp of the event occurrence.

public:
    /**
     * @brief Construct a new Product object.
     *
     * @param eventType Type of the event.
     * @param time Timestamp of the event occurrence.
     */
    Event(QString eventType, QDateTime time);

    /**
     * @brief Generates an event.
     *
     * This static method is responsible for creating a new event with a specific type and time.
     * @param eventType Type of the event.
     * @return Event& The generated event object.
     */
    static Event generateEvent(QString eventType);

    //Getters
    QString getEventType(); ///< Get type of the event.
    QDateTime getTime();    ///< Get time of the event.
};

#endif // EVENT_H
