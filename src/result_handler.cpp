#include "result_handler.h"
#include "event_bus.h"
#include "events.h"
#include <iostream>
#include <any>

ResultHandler::ResultHandler() {
    // Subscribe to the DATA_PROCESSED event
    EventBus::instance().subscribe(EventType::DATA_PROCESSED,
                                   [this](const EventData& event) {
                                       handleProcessedData(event);
                                   });
}

void ResultHandler::handleProcessedData(const EventData& event) {
    if (event.type == EventType::DATA_PROCESSED) {
        if (event.data.has_value()) {
            try {
                int result = std::any_cast<int>(event.data);
                std::cout << "ResultHandler: Received processed data: " << result << std::endl;
            } catch (const std::bad_any_cast& e) {
                std::cerr << "ResultHandler: Error casting event data: " << e.what() << std::endl;
            }
        } else {
            std::cout << "ResultHandler: Received DATA_PROCESSED event with no data." << std::endl;
        }
    }
}