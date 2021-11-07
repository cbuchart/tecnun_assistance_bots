#ifndef TECNUN_ARQUI_2021_2022_NOTE_H
#define TECNUN_ARQUI_2021_2022_NOTE_H

#include "Date.h"

#include <string>
#include <vector>

namespace tecnun
{
    struct Note
    {
        std::string text;

        std::vector<std::string> tags;
        std::vector<std::string> mentions;

        std::vector<Date> dates;

        explicit Note(std::string p_text) : text{std::move(p_text)} {}
    };

    using Notes = std::vector<std::shared_ptr<Note>>;
}

#endif
