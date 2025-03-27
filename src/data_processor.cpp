#include "data_processor.h"
#include "event_bus.h"
#include "events.h"
#include <iostream>
#include <thread>
#include <chrono>

void DataProcessor::process() {
    std::cout << "DataProcessor: Starting data processing..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    int result = 42;
    std::cout << "DataProcessor: Data processing complete. Publishing event." << std::endl;
    EventBus::instance().publish({EventType::DATA_PROCESSED, result});
}