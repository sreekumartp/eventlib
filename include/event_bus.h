#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "events.h"

#define MAX_THREAD_POOL_SIZE 16

class EventBus {
public:
    static EventBus& instance();

    using Subscriber = std::function<void(const EventData&)>;
    void subscribe(EventType type, Subscriber subscriber);
    void publish(const EventData& event);

private:
    EventBus();
    ~EventBus();
    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    void startThreadPool();
    void stopThreadPool();
    void notifySubscribers(const EventData& event);

    // Thread pool
    std::vector<std::thread> threadPool;
    std::queue<EventData> eventQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondition;
    bool stop;

    // Subscribers
    std::unordered_map<EventType, std::vector<Subscriber>> subscribers;
    std::mutex subscribersMutex;
};

#endif // EVENT_BUS_H