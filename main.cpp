#include <iostream>
#include <algorithm>
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
  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;

    for (unsigned int i(0); i < 1000; i++) {
        Board board;

    // loop through trumps
        while (board.get_moves().size() != 0) {
            player_move move;
            if(board.get_player_to_move() == 1) {
                move = ISMCTS::run_search(board, 1000); // TODO change to deeper iteration number - pass in from commandline?
            }
            else {
                move = board.getRandomLegalCard(board.get_player_to_move());
            }
//            print_1_move(move);
            board.do_move(move);

//            std::cout << "Discard pile size: " << board.discard_pile_size() << std::endl;
//            if(board.m_current_trick != NULL) {
//                board.m_current_trick->print_trick();
//            }
//            else {
//                std::cout << "Card amounts: " << board.m_player_hands[1]->size();
//                std::cout << " " << board.m_player_hands[2]->size();
//                std::cout << " " << board.m_player_hands[3]->size();
//                std::cout << " " << board.m_player_hands[4]->size() << std::endl;
//            }
        }
//        board.print_scores();


        switch (board.get_winner()) {
          case 1:
              a++;
              break;
          case 2:
              b++;
              break;
          case 3:
              c++;
              break;
          case 4:
              d++;
              break;
        }
        std::cout << "Winner: " << board.get_winner() << " " << a << " " << b << " " << c << " " << d << " " << std::endl;
    }
    return 0;
}