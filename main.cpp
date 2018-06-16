#include <iostream>
#include "Deck.h"
#include "Board.h"
#include "ISMCTS.h"

void print_1_move(player_move move) {
  int player_number;
  Card card;
  std::tie(player_number, card) = move;
  std::cout << "Player: " << player_number << " plays " << card.Card2Str() << std::endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Board board;

    // loop through trumps
    while (board.get_moves().size() != 0) {
        player_move move;
        if(board.get_player_to_move() == 1) {
            move = ISMCTS::run_search(board, 10);
        }
        else {
            move = board.getRandomLegalCard(board.get_player_to_move());
        }
        board.do_move(move);
        print_1_move(move);
        std::cout << "next trick:" << std::endl;
    }

    return 0;
}