#include "BotWorker.h"

#include <iostream>

tecnun::BotWorker::~BotWorker()
{
    // Wait for thread to finish when the worker is destroyed
    if (thread.joinable()) { thread.join(); }
}
