#include "utils.h"

#include <iostream>

void tecnun::utils::print_notes(Notes const& p_notes)
{
    std::cout << p_notes.size() << '\n';
    for (auto const& note : p_notes) { std::cout << note->text << '\n'; }
}

std::pair<std::string, std::string> tecnun::utils::parse_line(std::string const& p_line)
{
    auto const first_sep = p_line.find(' ');
    auto const command = p_line.substr(0, first_sep);
    auto const argument = first_sep != std::string::npos ? p_line.substr(first_sep + 1) : "";

    return {command, argument};
}