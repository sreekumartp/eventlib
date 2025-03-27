#include "logger.h"
#include "event_bus.h"
#include "events.h"
#include <iostream>
#include <thread>
#include <chrono>

Logger::Logger() {
    // Subscribe to the TASK_COMPLETED event
    EventBus::instance().subscribe(EventType::TASK_COMPLETED,
                                  [](const EventData& event) {
                                       std::cout << "Logger: Task completed event received." << std::endl;
                                       // Log details from event.data if needed
                                   });
}

void Logger::someTask() {
    std::cout << "Logger: Performing some task..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    EventBus::instance().publish({EventType::TASK_COMPLETED});
}