#ifndef RESULT_HANDLER_H
#define RESULT_HANDLER_H

#include "events.h"
class ResultHandler {
public:
    ResultHandler();

private:
    void handleProcessedData(const EventData& event);
};

#endif // RESULT_HANDLER_H