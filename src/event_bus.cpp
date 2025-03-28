#include "event_bus.h"

EventBus& EventBus::instance() {
    static EventBus instance;
    return instance;
}

EventBus::EventBus() : stop(false) {
    startThreadPool();
}

EventBus::~EventBus() {
    stopThreadPool();
}

void EventBus::subscribe(EventType type, Subscriber subscriber) {
    std::lock_guard<std::mutex> lock(subscribersMutex);
    subscribers[type].push_back(subscriber);
}

void EventBus::publish(const EventData& event) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        eventQueue.push(event);
    }
    queueCondition.notify_one();
}

void EventBus::startThreadPool() {
    // const size_t threadCount = std::thread::hardware_concurrency();
    const size_t threadCount = std::min(std::thread::hardware_concurrency(), static_cast<unsigned int>(MAX_THREAD_POOL_SIZE));
    for (size_t i = 0; i < threadCount; ++i) {
        threadPool.emplace_back([this]() {
            while (true) {
                EventData event;
                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    queueCondition.wait(lock, [this]() { return stop || !eventQueue.empty(); });

                    if (stop && eventQueue.empty()) {
                        return;
                    }

                    event = eventQueue.front();
                    eventQueue.pop();
                }

                // Notify subscribers
                notifySubscribers(event);
            }
        });
    }
}

void EventBus::stopThreadPool() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stop = true;
    }
    queueCondition.notify_all();

    for (std::thread& thread : threadPool) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void EventBus::notifySubscribers(const EventData& event) {
    std::vector<Subscriber> eventSubscribers;
    {
        std::lock_guard<std::mutex> lock(subscribersMutex);
        if (subscribers.find(event.type) != subscribers.end()) {
            eventSubscribers = subscribers[event.type];
        }
    }

    for (const auto& subscriber : eventSubscribers) {
        subscriber(event);
    }
}