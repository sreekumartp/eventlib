#ifndef EVENTS_H
#define EVENTS_H

#include <string>
#include <any>
#include <ostream>

enum class EventType {
    DATA_PROCESSED,
    TASK_COMPLETED,
    USER_LOGGED_IN,
    A2B_EVENT,
    B2A_EVENT
    // Add more event types as needed
};

struct EventData {
    EventType type;
    std::any data; // Use std::any to hold arbitrary data (C++17 and later)
};


// Overload the << operator for EventType
inline std::ostream& operator<<(std::ostream& os, const EventType& eventType) {
    switch (eventType) {
        case EventType::A2B_EVENT:
            os << "A2B_EVENT";
            break;
        case EventType::B2A_EVENT:
            os << "B2A_EVENT";
            break;
        case EventType::DATA_PROCESSED:
            os << "DATA_PROCESSED";
            break;
        default:
            os << "Unknown EventType";
            break;
    }
    return os;
}


#endif // EVENTS_H