//
// Created by jamie on 11/06/18.
//

#include <iostream>
#include "Trick.h"

void Trick::print_trick()
{
    std::cout << "Printing trick...." << std::endl;
    for(std::vector<player_move>::iterator it = m_trick_pile.begin(); it != m_trick_pile.end(); ++it) {
        Card card = std::get<1>(*it);
        std::cout << "Card is " << card.Card2Str() << std::endl;
    }
    std::cout << "...." << std::endl;
}


trick_result Trick::player_plays_card(player_move given_move)
{
    m_trick_pile.push_back(given_move);
    print_trick();

    if(m_trick_pile.size() == 4) {
        std::vector<player_move> suited_plays;
        std::vector<player_move> trump_plays;

        for (unsigned int i(0); i < m_trick_pile.size(); ++i) {
            player_move play = m_trick_pile.at(i);
            if(std::get<1>(play).get_suit() == m_suit_asked) {
                suited_plays.push_back(play);
            }
            if(std::get<1>(play).get_suit() == m_trump_suit) {
                trump_plays.push_back(play);
            }
        }
        std::vector<player_move> concatenated_plays;
        suited_plays.insert(suited_plays.end(), trump_plays.begin(), trump_plays.end());
        concatenated_plays = suited_plays;

        int result_code = Trick::TRICK_RESULT_CODE_FINISHED;
        trick_result result = std::make_tuple(
                result_code,
                std::get<0>(concatenated_plays.back()),
                100 // TODO get score for trick
        );

        return result;
    }

    int result_code = Trick::TRICK_RESULT_CODE_STILL_IN_PLAY;
    return std::make_tuple(
            result_code,
            -1,
            -1
    );
}

bool Trick::isEmpty()
{
    return m_trick_pile.size() == 0;
}

int Trick::getSuitAsked()
{
    return m_suit_asked;
}