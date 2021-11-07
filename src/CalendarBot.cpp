#include "CalendarBot.h"

#include "utils.h"

#include <regex>

namespace
{
    void extract_dates_with_format(std::shared_ptr<tecnun::Note> p_note, std::string const& p_format)
    {
        std::smatch match{};
        std::regex_search(p_note->text, match, std::regex{p_format});
        for (auto const& str : match) { p_note->dates.emplace_back(str); }
    }
}

void tecnun::CalendarBot::run()
{
    extract_dates_with_format(note, "\\d{2}/\\d{2}/\\d{4}");
    extract_dates_with_format(note, "\\d{4}/\\d{2}/\\d{2}");
}

void tecnun::CalendarBot::print_notes_with_date(Notes const& p_notes, Date const& p_date)
{
    Notes notes_with_date;

    for (auto const& note : p_notes) {
        if (utils::contains(note->dates, p_date)) { notes_with_date.push_back(note); }
    }
    utils::print_notes(notes_with_date);
}