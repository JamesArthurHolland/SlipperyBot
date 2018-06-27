//
// Created by jamie on 21/06/18.
//

#ifndef SLIPPERYBOT_SUITPLAYCAPABILITY_H
#define SLIPPERYBOT_SUITPLAYCAPABILITY_H


#include <vector>
#include "Card.h"

class SuitPlayCapability {
public:
    SuitPlayCapability();
    SuitPlayCapability(bool m_can_play_spades, bool m_can_play_hearts, bool m_can_play_diamonds, bool m_can_play_clubs);

    void can_play_suit(int suit_asked, bool can_play_suit);

    bool are_capabilities_broken(std::vector<Card> players_hand);

    std::vector<Card> get_possible_player_cards(std::vector<Card> unknown_cards);

private:
    bool m_can_play_spades;
    bool m_can_play_hearts;
    bool m_can_play_diamonds;
    bool m_can_play_clubs;
};


#endif //SLIPPERYBOT_SUITPLAYCAPABILITY_H
