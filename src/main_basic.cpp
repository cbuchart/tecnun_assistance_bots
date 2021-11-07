#include "Date.h"
#include "Note.h"

#include "BotWorker.h"
#include "CalendarBot.h"
#include "ClassificationBot.h"

#include "utils.h"

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

int main()
{
    tecnun::Notes notes;
    std::vector<tecnun::BotWorker> running_bots;

    std::string line;
    while (getline(std::cin, line)) {
        auto const [command, argument] = tecnun::utils::parse_line(line);

        if (command == "create") {
            auto note = std::make_shared<tecnun::Note>(argument);
            notes.push_back(note);

            if (argument.front() != '?') { // if non-private, run bots
                auto classification_bot = std::make_shared<tecnun::ClassificationBot>(note);
                running_bots.emplace_back(std::static_pointer_cast<tecnun::IBot>(classification_bot));
                auto calendar_bot = std::make_shared<tecnun::CalendarBot>(note);
                running_bots.emplace_back(std::static_pointer_cast<tecnun::IBot>(calendar_bot));
            }

            std::cout << "CREATED\n";
        } else {
            // Barrier: wait for all boths to finish
            running_bots.clear();

            if (command == "tag") {
                tecnun::ClassificationBot::print_notes_with_tag(notes, argument);
            } else if (command == "mention") {
                tecnun::ClassificationBot::print_notes_with_mention(notes, argument);
            } else if (command == "agenda") {
                tecnun::CalendarBot::print_notes_with_date(notes, tecnun::Date{argument});
            } else if (command == "bot") {
            }
        }
    }

    running_bots.clear();
}
