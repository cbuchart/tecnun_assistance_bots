#ifndef TECNUN_ARQUI_2021_2022_BOTWORKER_H
#define TECNUN_ARQUI_2021_2022_BOTWORKER_H

#include "IBot.h"

#include <memory>
#include <thread>

namespace tecnun
{
    /**
     * Class to associate a bot with a thread.
     */
    struct BotWorker
    {
        std::shared_ptr<IBot> bot;
        std::thread thread;

        explicit BotWorker(std::shared_ptr<IBot> p_bot) : bot{p_bot}, thread{&IBot::run, p_bot} {}

        BotWorker(BotWorker&& other) = default;

        ~BotWorker();
    };
}

#endif
