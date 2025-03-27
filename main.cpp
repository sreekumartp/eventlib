#include "data_processor.h"
#include "result_handler.h"
#include "logger.h"
#include <thread>
#include <iostream>

#include "event_bus.h"
#include "events.h"


class A {


private:
    EventBus& eventBus;
    std::thread workerThread;
    bool stopThread;
    EventData classAEvent;

public:
    A(EventBus& bus) : eventBus(bus), stopThread(false) {
        eventBus.instance().subscribe(EventType::B2A_EVENT, [this](const EventData& event) {
            handleEvent(event);
        });
        workerThread = std::thread(&A::run, this);
    }

    ~A() {
        stopThread = true;
        if (workerThread.joinable()) {
            workerThread.join();
        }
    }

    void run() {
        while (!stopThread) {
            // Simulate some work
            std::this_thread::sleep_for(std::chrono::seconds(1));
            classAEvent.type = EventType::A2B_EVENT;
            classAEvent.data = "Event from A";
            eventBus.instance().publish(classAEvent);
        }
    }

    void handleEvent(const EventData& event) {
        // Handle the event
        std::cout << "A: Event received in thread: " << std::this_thread::get_id() << " " << event.type << std::endl;
    
    }


};

class B {
public:
    B(EventBus& bus) : eventBus(bus), stopThread(false) {
        eventBus.instance().subscribe(EventType::A2B_EVENT, [this](const EventData& event) {
            handleEvent(event);
        });
        workerThread = std::thread(&B::run, this);
    }

    ~B() {
        stopThread = true;
        if (workerThread.joinable()) {
            workerThread.join();
        }
    }

    void run() {
        while (!stopThread) {
            // Simulate some work
            std::this_thread::sleep_for(std::chrono::seconds(1));
            EventData classBEvent;
            classBEvent.type = EventType::B2A_EVENT;
            classBEvent.data = "Event from B";
            eventBus.instance().publish(classBEvent);
        }
    }

    void handleEvent(const EventData& event) {
        // Handle the event
        std::cout << "A: Event received in thread: " << std::this_thread::get_id() << " " << event.type << std::endl;

    }

private:
    EventBus& eventBus;
    std::thread workerThread;
    bool stopThread;
};

int main() {
    // ResultHandler handler;
    // Logger logger;
    // DataProcessor processor;

    // std::thread processor_thread(&DataProcessor::process, &processor);
    // std::thread logger_thread(&Logger::someTask, &logger);

    // processor_thread.join();
    // logger_thread.join();
// 


EventBus& eventBus = EventBus::instance();

A a(eventBus);
B b(eventBus);

while(true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
    return 0;
}