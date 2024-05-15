#ifndef EVENT_H
#define EVENT_H

#include <QDateTime>

class Event{
private:
    QString eventType;
    QDateTime time;
public:
    Event generateEvent();
};

#endif
