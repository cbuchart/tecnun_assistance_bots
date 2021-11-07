#include "ClassificationBot.h"

#include "utils.h"

namespace
{
    std::pair<std::string, size_t> extract_token(std::string const& str, size_t pos)
    {
        static constexpr auto const valid_characters = "abcedfghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

        auto const end = str.find_first_not_of(valid_characters, pos + 1);
        auto const token = str.substr(pos + 1, end - pos - 1);

        return {token, end};
    }
}

void tecnun::ClassificationBot::run()
{
    auto pos = note->text.find_first_of("#@");
    while (pos < note->text.size()) {
        if (note->text[pos] == '#') {
            auto const [tag, next] = extract_token(note->text, pos);
            note->tags.push_back(tag);
            pos = next;
        } else if (note->text[pos] == '@') {
            auto const [mention, next] = extract_token(note->text, pos);
            note->mentions.push_back(mention);
            pos = next;
        } else {
            ++pos;
        }

        if (pos < note->text.size()) pos = note->text.find_first_of("#@", pos);
    }
}

void tecnun::ClassificationBot::print_notes_with_tag(Notes const& p_notes, std::string const& p_tag)
{
    Notes notes_with_tag;

    for (auto const& note : p_notes) {
        if (utils::contains(note->tags, p_tag)) { notes_with_tag.push_back(note); }
    }
    utils::print_notes(notes_with_tag);
}

void tecnun::ClassificationBot::print_notes_with_mention(Notes const& p_notes, std::string const& p_mention)
{
    Notes notes_with_mention;

    for (auto const& note : p_notes) {
        if (utils::contains(note->mentions, p_mention)) { notes_with_mention.push_back(note); }
    }
    utils::print_notes(notes_with_mention);
}
