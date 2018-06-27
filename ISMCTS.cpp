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

void print_all_hands(Board board) {
    std::cout << "============== " << std::endl;
    for(auto const &pair : board.m_player_hands) {
        board.print_hand(*pair.second);
    }
}

player_move ISMCTS::run_search(Board root_state, int itermax)
{
    Node* root = new Node();

    for (unsigned int i(0); i < itermax; ++i) {
        int number_of_moves = root_state.get_moves().size();
        if(number_of_moves == 1) {
            return std::make_tuple(root_state.get_player_to_move(), root_state.get_moves().front());
        }
        Node* node;
        node = root;

        Board state = root_state; // deep clone using copy constructor
//        print_all_hands(state);
        state.randomize(root_state.get_player_to_move()); // create a determination
//        print_all_hands(state);

        // Select
        int number_of_untried_moves = node->get_untried_moves(state.get_moves()).size();

        while(number_of_moves != 0 && number_of_untried_moves == 0) {
            Node* selected_node = node->UCB_select_child(state.get_moves());
            if(selected_node != NULL) {
                player_move* move = selected_node->get_move();
//                print_move(*move);
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
//            print_move(p_move);
            state.do_move(p_move);
            node = node->add_child(p_move);
        }

        // Simulate
        number_of_moves = state.get_moves().size();
        std::vector<Card> test_get_moves = state.get_moves();
        while( ! state.get_moves().empty() ) {
            int randomIndex = rand() % state.get_moves().size();
            Card card = state.get_moves().at(randomIndex);
            player_move p_move = std::make_tuple(state.get_player_to_move(), card);
//            print_move(p_move);
            state.do_move(p_move);
        }

//        print_all_hands(state);

        // Backpropagate
        while(node->m_parent_node != NULL) {
            node->update(state);
            node = node->m_parent_node;
        }
    }

    return root->get_move_from_most_visited_child_node();
}