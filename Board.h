//
// Created by jamie on 05/06/18.
//

#ifndef SLIPPERYBOT_BOARD_H
#define SLIPPERYBOT_BOARD_H

#include <vector>
#include <map>
#include "Card.h"
#include "Trick.h"

using namespace std;

const int MAX_PLAYERS(4);

class Board {
public:
    static const int MAX_NUMBER_OF_TRICKS = 7; // 52cards / 4players = 7 whole tricks

    Board();
    Board(
      int player_to_move,
      std::vector<Card> discard_pile,
      std::map<int, Hand> player_hands,
      std::map<int, int> player_scores,
      int current_trump_suit
    ) : m_player_to_move(player_to_move),
        m_discard_pile(discard_pile),
        m_player_hands(player_hands),
        m_player_scores(player_scores),
        m_current_trump_suit(current_trump_suit),
        m_current_trick(NULL)
    {}

    ~Board() { delete m_current_trick; }

    Board clone_and_randomize(int player_number);
    std::vector<Card> get_moves();
    int get_next_player(int player_number);
    int get_player_to_move();
    void do_move(player_move move);

    int get_result(int player_number);

    player_move getRandomLegalCard(int player_number);
private:
    int m_player_to_move = 1;
    std::vector<Card> m_discard_pile;

    std::map<int, Hand*> m_player_hands;
    std::map<int, int>  m_player_scores;

    void randomize(int player_number);
    void remove_card_from_hand(Hand* hand, Card card);

    Trick *m_current_trick;
    int m_current_trump_suit = 3; // TODO pass without magic.
};


#endif //SLIPPERYBOT_BOARD_H
