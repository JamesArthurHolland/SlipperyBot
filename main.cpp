#include <iostream>
#include "Deck.h"
#include "Board.h"
#include "ISMCTS.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Board board;

    // loop through trumps
    while (board.get_moves().size() != 0) {
        player_move move;
        if(board.get_player_to_move() == 1) {
            move = ISMCTS::run_search(board, 100);
        }
        else {
            move = board.getRandomLegalCard(board.get_player_to_move());
        }
        board.do_move(move);
    }

    return 0;
}