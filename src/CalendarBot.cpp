#include "CalendarBot.h"

#include "utils.h"

#include <regex>

using namespace std::string_literals;

namespace
{
    auto const DATE_CHARACTERS{"0123456789/"s};
    constexpr auto END{std::string::npos};

    void extract_dates_using_regex(std::shared_ptr<tecnun::Note> p_note, std::regex const& p_regex,
                                   size_t p_group_index, size_t p_group_count)
    {
        std::smatch match{};
        std::regex_search(p_note->text, match, p_regex);
        for (size_t ii = p_group_index; ii < match.size(); ii += p_group_count) {
            p_note->dates.emplace_back(match[ii]);
        }
    }

    size_t find_next(std::vector<std::string> const& p_format, std::string const& p_str, size_t p_pos)
    {
        if (p_format.empty()) { return END; }

        auto const start = p_str.find_first_of(p_format.front(), p_pos);

        auto next = start;
        for (size_t ii = 1; ii < p_format.size(); ++ii) {
            next = p_str.find_first_of(p_format[ii], next);
            if (next == END) { return END; }
        }

        return start;
    }

    size_t find_next_date(std::vector<std::string> const& p_format, std::string const& p_str, size_t p_pos)
    {
        auto const next = find_next(p_format, p_str, p_pos);
        if (next == END) { return END; }

        if (next > p_pos && DATE_CHARACTERS.find(p_str[next - 1]) != END) { return END; }
        if (next + p_format.size() < p_str.size() && DATE_CHARACTERS.find(p_str[next + p_format.size()]) != END) {
            return END;
        }

        return next;
    }

    void extract_dates_with_format(std::shared_ptr<tecnun::Note> p_note, std::vector<std::string> const& p_format)
    {
        size_t pos{0};

        while (pos < p_note->text.size()) {
            auto const next = find_next_date(p_format, p_note->text, pos);
            if (next == END) { return; }

            auto const date = p_note->text.substr(next, next + p_format.size());
            p_note->dates.emplace_back(date);
            pos = next + p_format.size() + 1;
        }
    }
}

void tecnun::CalendarBot::run()
{
#ifdef FIND_DATES_USING_REGEX
    run_using_regex();
#else
    run_with_manual_search();
#endif
}

void tecnun::CalendarBot::run_using_regex()
{
    // \d => digit
    // \d{4} => 4 digits
    // \D => not a digit
    // ^ => start of string
    // $ => end of string
    // () => capture group
    // Logic for first format (similar on second):
    //   2 digits, a slash, 2 digits, a slash, 4 digits, with no digits neither before nor after, allowing string limits
    // Total 4 capture groups: the whole expression plus 3 explicit groups
    // We are interested in the third group (the one with the date)
    extract_dates_using_regex(note, std::regex{"(\\D{1}|^)(\\d{2}/\\d{2}/\\d{4})(\\D{1}|$)"}, 2, 4);
    extract_dates_using_regex(note, std::regex{"(\\D{1}|^)(\\d{4}/\\d{2}/\\d{2})(\\D{1}|$)"}, 2, 4);
}

void tecnun::CalendarBot::run_with_manual_search()
{
    auto const DIGIT{"0123456789"s};
    extract_dates_with_format(note, {DIGIT, DIGIT, "/", DIGIT, DIGIT, "/", DIGIT, DIGIT, DIGIT, DIGIT});
    extract_dates_with_format(note, {DIGIT, DIGIT, DIGIT, DIGIT, "/", DIGIT, DIGIT, "/", DIGIT, DIGIT});
}

void tecnun::CalendarBot::print_notes_with_date(Notes const& p_notes, Date const& p_date)
{
    Notes notes_with_date;

    for (auto const& note : p_notes) {
        if (utils::contains(note->dates, p_date)) { notes_with_date.push_back(note); }
    }
    utils::print_notes(notes_with_date);
}