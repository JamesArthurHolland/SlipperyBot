//
// Created by jamie on 12/06/18.
//

#include <iostream>
#include "ISMCTS.h"
#include "Node.h"
#include "Board.h"

void print_move(player_move move) {
  int player_number;
  Card card;
  std::tie(player_number, card) = move;
  std::cout << "Player " << player_number << " plays " << card.Card2Str() << std::endl;
}

player_move ISMCTS::run_search(Board root_state, int itermax)
{
    Node* root = new Node();


    for (unsigned int i(0); i < itermax; ++i) {
        Node* node;
        node = root;

        Board state = root_state; // deep clone using copy constructor
        state.randomize(root_state.get_player_to_move()); // create a determination

        // Select
        while(state.get_moves().size() != 0 && node->get_untried_moves(state.get_moves()).size() == 0) {
            Node* selected_node = node->UCB_select_child(state.get_moves());
            if(selected_node != NULL) {
                player_move* move = selected_node->get_move();
                print_move(*move);
                state.do_move(*move);
                node = selected_node;
            }
        }

        // Expand
        std::vector<Card> all_moves = state.get_moves();
        std::vector<Card> untried_moves = node->get_untried_moves(all_moves);
        if(untried_moves.size() != 0) { // non-terminal, we can expand.
            int randomIndex = rand() % untried_moves.size();
            Card card = untried_moves.at(randomIndex);
            player_move p_move = std::make_tuple(state.get_player_to_move(), card);
            print_move(p_move);
            state.do_move(p_move);
            node = node->add_child(p_move);
        }

        // Simulate
        while(state.get_moves().size() != 0) {
            int randomIndex = rand() % state.get_moves().size();
            std::cout << "-------" << std::endl;
            Card card = state.get_moves().at(randomIndex);
            player_move p_move = std::make_tuple(state.get_player_to_move(), card);
            print_move(p_move);
            state.do_move(p_move);
        }

        // Backpropagate
        while(node != NULL) {
            node->update(state);
            node = node->m_parent_node;
        }


        std::cout << "----" << std::endl;
    }


}