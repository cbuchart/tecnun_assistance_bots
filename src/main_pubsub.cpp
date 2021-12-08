#include "Date.h"
#include "Note.h"

#include "Broker.h"
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
    tecnun::Broker broker;

    broker.subscribe("notes", [](std::shared_ptr<tecnun::Note> p_msg) {
        tecnun::ClassificationBot bot{p_msg};
        bot.run();
    });
    broker.subscribe("notes", [](std::shared_ptr<tecnun::Note> p_msg) {
        tecnun::CalendarBot bot{p_msg};
        bot.run();
    });

    std::string line;
    while (getline(std::cin, line)) {
        auto const [command, argument] = tecnun::utils::parse_line(line);

        if (command == "create") {
            auto note = std::make_shared<tecnun::Note>(argument);
            notes.push_back(note);

            if (argument.front() != '?') { // if non-private, publish message with note
                broker.publish("notes", note);
            }

            std::cout << "CREATED\n";
        } else {
            // Barrier: wait for all boths to finish
            broker.join_all();

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
}
