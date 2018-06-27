//
// Created by jamie on 05/06/18.
//

#ifndef SLIPPERYBOT_BOARD_H
#define SLIPPERYBOT_BOARD_H

#include <vector>
#include <map>
#include "Card.h"
#include "Trick.h"
#include "SuitPlayCapability.h"

using namespace std;

const int MAX_PLAYERS(4);

class Board {
public:
    static const int MAX_NUMBER_OF_TRICKS = 7; // 52cards / 4players = 7 whole tricks

    Board();
    Board( const Board &obj);
    ~Board() {
      delete m_current_trick;
//      for(std::map<int, Hand*>::iterator it = m_player_hands.begin(); it != m_player_hands.end(); ++it) {
//        delete(it->second);
//      }
    }

    std::vector<Card> get_moves();
    std::map<int, Hand*> m_player_hands;
    int get_next_player(int player_number);
    int get_player_to_move();
    int get_result(int player_number);

    void print_scores();

    void do_move(player_move move);
    void randomize(int player_number);
    void print_hand(Hand hand);

    int get_winner();

    int discard_pile_size();


    player_move getRandomLegalCard(int player_number);

    Trick *m_current_trick;
private:
    int m_player_to_move;
    std::vector<Card> m_discard_pile;
    bool suited_capabilities_met();

    std::map<int, int>  m_player_scores;
    std::map<int, SuitPlayCapability>  m_player_suited_capabilities;

    void remove_card_from_cards(Hand* hand, Card card); // TODO move to utility class, change hand param to be cards or similar

    int m_current_trump_suit = 3; // TODO pass without magic.
};


#endif //SLIPPERYBOT_BOARD_H
