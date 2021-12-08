#ifndef TECNUN_ARQUI_2021_2022_NOTE_H
#define TECNUN_ARQUI_2021_2022_NOTE_H

#include "Date.h"

#include <string>
#include <vector>

namespace tecnun
{
    struct Note
    {
        using ids_t = std::vector<std::string>;
        using dates_t = std::vector<Date>;

        std::string text;

        ids_t tags;
        ids_t mentions;

        dates_t dates;

        explicit Note(std::string p_text) : text{std::move(p_text)} {}
    };

    using Notes = std::vector<std::shared_ptr<Note>>;
}

#endif
