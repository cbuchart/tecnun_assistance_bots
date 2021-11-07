#ifndef TECNUN_ARQUI_2021_2022_IBOT_H
#define TECNUN_ARQUI_2021_2022_IBOT_H

#include "Note.h"

#include <memory>

namespace tecnun
{
    struct IBot
    {
        std::shared_ptr<Note> note;

        explicit IBot(std::shared_ptr<Note> p_note) : note{p_note} {}

        virtual void run() = 0;
    };
}

#endif
