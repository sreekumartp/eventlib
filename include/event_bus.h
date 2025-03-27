#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include "events.h"
#include <functional>
#include <vector>
#include <map>
#include <mutex>

class EventBus {
private:
    std::map<EventType, std::vector<std::function<void(const EventData&)>>> subscribers_;
    std::mutex mutex_;

    // Singleton pattern (private constructor and static instance)
    EventBus() = default;
    ~EventBus() = default;
    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

public:
    static EventBus& instance();

    void subscribe(EventType type, std::function<void(const EventData&)> callback);
    void publish(const EventData& event);
};

#endif // EVENT_BUS_H