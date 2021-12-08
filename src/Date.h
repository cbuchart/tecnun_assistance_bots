#ifndef TECNUN_ARQUI_2021_2022_DATE_H
#define TECNUN_ARQUI_2021_2022_DATE_H

#include <string>

namespace tecnun
{
    /**
     * General date type.
     */
    struct Date
    {
        uint8_t day;
        uint8_t month;
        uint32_t year;

        explicit Date(std::string const& p_str);

        bool operator==(Date const& o) const;
    };
}

#endif
