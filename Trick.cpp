//
// Created by jamie on 11/06/18.
//

#include <iostream>
#include "Trick.h"

Trick::Trick(const Trick &obj)
{
    m_suit_asked = obj.m_suit_asked;
    m_trump_suit = obj.m_trump_suit;
    for(auto const &move : obj.m_trick_pile) {
        m_trick_pile.push_back(move);
    }
}

void Trick::print_trick()
{
    std::cout << "Printing trick...." << std::endl;
    for(std::vector<player_move>::iterator it = m_trick_pile.begin(); it != m_trick_pile.end(); ++it) {
        Card card = std::get<1>(*it);
        std::cout << "Card is " << card.Card2Str() << std::endl;
    }
    std::cout << "...." << std::endl;
}

int Trick::get_score_for_trick()
{
    int current_score = 0;
    for (unsigned int i(0); i < m_trick_pile.size(); ++i) {
        player_move play = m_trick_pile.at(i);
        Card current_card = std::get<1>(play);
        if(current_card.get_suit() == 1) { // TODO not magic for heart
            if(current_card.get_rank() == 0 || current_card.get_rank() > 9) {
              current_score += 10; // TODO not magic for points for face cards
            }
            else {
              current_score += 5; // TODO not magic for points for non face cards
            }
        }
        if(current_card.get_suit() == 1 && current_card.get_rank() == 11) { // TODO not magic for spades suit
          current_score += 5; // TODO not magic for points for queen of spades
        }
    }
    return current_score;
}

trick_result Trick::player_plays_card(player_move given_move)
{
    m_trick_pile.push_back(given_move);

    if(m_trick_pile.size() == 4) {
//        print_trick();
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
                get_score_for_trick()
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