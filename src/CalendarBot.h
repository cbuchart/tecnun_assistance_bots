#ifndef TECNUN_ARQUI_2021_2022_CALENDARBOT_H
#define TECNUN_ARQUI_2021_2022_CALENDARBOT_H

#include "IBot.h"

namespace tecnun
{
    struct CalendarBot : IBot
    {
        using IBot::IBot;

        void run() override;

        static void print_notes_with_date(Notes const& p_notes, Date const& p_date);
    };
}

#endif