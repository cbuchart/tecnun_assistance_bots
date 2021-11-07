#ifndef TECNUN_ARQUI_2021_2022_UTILS_H
#define TECNUN_ARQUI_2021_2022_UTILS_H

#include "Note.h"

namespace tecnun::utils
{
    template<typename Container>
    bool contains(Container const& p_container, typename Container::value_type const& p_value)
    {
        return std::any_of(begin(p_container), end(p_container),
                           std::bind(std::equal_to(), std::placeholders::_1, p_value));
    }

    void print_notes(Notes const& p_notes);

    std::pair<std::string, std::string> parse_line(std::string const& p_line);
}

#endif
