#include "event_bus.h"
#include <iostream>
#include <thread>

EventBus& EventBus::instance() {
    static EventBus instance_;
    return instance_;
}

void EventBus::subscribe(EventType type, std::function<void(const EventData&)> callback) {
    std::lock_guard<std::mutex> lock(mutex_);
    subscribers_[type].push_back(callback);
    std::cout << "Event Subscription " << std::this_thread::get_id() << std::endl;
    
}

void EventBus::publish(const EventData& event) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (subscribers_.count(event.type)) {
        for (const auto& callback : subscribers_[event.type]) {
            std::cout << "Event Publish " << std::this_thread::get_id() << std::endl;
    
            callback(event);
        }
    }
}