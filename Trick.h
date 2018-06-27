//
// Created by jamie on 11/06/18.
//

#ifndef SLIPPERYBOT_TRICK_H
#define SLIPPERYBOT_TRICK_H


#include <tuple>
#include <vector>
#include "Card.h"

typedef std::tuple<int, Card> player_move; // playernumber, card
typedef std::tuple<int, int, int> trick_result; // resultcode, playernumber of winner, points won

class Trick
{
public:
    static const int TRICK_RESULT_CODE_FINISHED = 0;
    static const int TRICK_RESULT_CODE_STILL_IN_PLAY = 1;

    Trick(){};
    Trick( const Trick &obj);
    Trick(int trump_suit, int suit_asked) : m_trump_suit(trump_suit), m_suit_asked(suit_asked) {}

    trick_result player_plays_card(player_move given_move);
    bool isEmpty();
    int getSuitAsked();
    std::vector<player_move> m_trick_pile;
    void print_trick();
private:
    int m_suit_asked = 3; // Change to not magic
    int m_trump_suit;

    bool compare_cards_in_trick_pile();
    int get_score_for_trick();
};


#endif //SLIPPERYBOT_TRICK_H
