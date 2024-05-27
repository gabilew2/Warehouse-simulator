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
 * @brief Generates an event.
 */
Event Event::generateEvent(QString eventType)
{
    QDateTime time = QDateTime::currentDateTime();
    // FIXME
    time = time.addMSecs(QRandomGenerator::global()->bounded(100));

    return Event(eventType, time);
}

// Getters implementation

QString Event::getEventType()
{
    return eventType;
}

QDateTime Event::getTime()
{
    return time;
}
