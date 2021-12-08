#ifndef TECNUN_ARQUI_2021_2022_CLASSIFICATIONBOT_H
#define TECNUN_ARQUI_2021_2022_CLASSIFICATIONBOT_H

#include "IBot.h"

namespace tecnun
{
    /**
     * Bot for classification (tags and mentions).
     */
    struct ClassificationBot : IBot
    {
        using IBot::IBot;

        void run() override;

        static void print_notes_with_tag(Notes const& p_notes, std::string const& p_tag);
        static void print_notes_with_mention(Notes const& p_notes, std::string const& p_mention);
    };
}

#endif
