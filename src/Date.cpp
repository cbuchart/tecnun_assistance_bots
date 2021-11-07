#include "Date.h"

tecnun::Date::Date(std::string const& p_str)
{
    if (p_str[2] == '/') { // dd/mm/yyyy
        day = std::stoul(p_str.substr(0, 2));
        month = std::stoul(p_str.substr(3, 2));
        year = std::stoul(p_str.substr(6, 4));
    } else { // yyyy/mm/dd
        year = std::stoul(p_str.substr(0, 4));
        month = std::stoul(p_str.substr(5, 2));
        day = std::stoul(p_str.substr(8, 2));
    }
}

bool tecnun::Date::operator==(Date const& o) const
{
    return year == o.year && month == o.month && day == o.day;
}
