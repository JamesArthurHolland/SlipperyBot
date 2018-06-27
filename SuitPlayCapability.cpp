//
// Created by jamie on 21/06/18.
//

#include "SuitPlayCapability.h"

SuitPlayCapability::SuitPlayCapability()
    : m_can_play_spades(true),
    m_can_play_hearts(true),
    m_can_play_diamonds(true),
    m_can_play_clubs(true) {}

SuitPlayCapability::SuitPlayCapability(bool m_can_play_spades, bool m_can_play_hearts, bool m_can_play_diamonds,
                                       bool m_can_play_clubs) : m_can_play_spades(m_can_play_spades),
                                                                m_can_play_hearts(m_can_play_hearts),
                                                                m_can_play_diamonds(m_can_play_diamonds),
                                                                m_can_play_clubs(m_can_play_clubs)
{}

bool SuitPlayCapability::are_capabilities_broken(std::vector<Card> players_hand)
{
    for(auto const &card : players_hand) {
        if( ! m_can_play_spades && card.get_suit() == 0) {
            return true;
        }
        if( ! m_can_play_hearts && card.get_suit() == 1) {
            return true;
        }
        if( ! m_can_play_diamonds && card.get_suit() == 2) {
            return true;
        }
        if( ! m_can_play_clubs && card.get_suit() == 3) {
            return true;
        }
    }
    return false;
}

std::vector<Card> SuitPlayCapability::get_possible_player_cards(std::vector<Card> unknown_cards)
{
    std::vector<Card> possible_cards;

    for(auto const &card : unknown_cards) {
        if(m_can_play_spades && card.get_suit() == 0) {
            possible_cards.push_back(card);
        }
        if(m_can_play_hearts && card.get_suit() == 1) {
            possible_cards.push_back(card);
        }
        if(m_can_play_diamonds && card.get_suit() == 2) {
            possible_cards.push_back(card);
        }
        if(m_can_play_clubs && card.get_suit() == 3) {
            possible_cards.push_back(card);
        }
    }

    return possible_cards;
}

void SuitPlayCapability::can_play_suit(int suit, bool can_play_suit)
{
    switch (suit) {
        case 0:
            m_can_play_spades = can_play_suit;
            break;
        case 1:
            m_can_play_hearts = can_play_suit;
            break;
        case 2:
            m_can_play_diamonds = can_play_suit;
            break;
        case 3:
            m_can_play_clubs = can_play_suit;
            break;
    }
}