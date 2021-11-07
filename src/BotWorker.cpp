#include "BotWorker.h"

#include <iostream>

tecnun::BotWorker::~BotWorker()
{
    if (thread.joinable()) { thread.join(); }
}
