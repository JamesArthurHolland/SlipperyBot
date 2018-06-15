//
// Created by jamie on 12/06/18.
//

#include "ISMCTS.h"
#include "Node.h"
#include "Board.h"

player_move ISMCTS::run_search(Board root_state, int itermax)
{
    Node* root = new Node();


    for (unsigned int i(0); i < itermax; ++i) {
        Node* node;
        node = root;

        Board state = root_state.clone_and_randomize(root_state.get_player_to_move());

        // Select

        while(state.get_moves().size() != 0 && node->get_untried_moves(state.get_moves()).size() != 0) {
            node = node->UCB_select_child(state.get_moves());
            if(node != NULL) {
                player_move* move = node->get_move();
                state.do_move(*move);
            }
        }

        // Expand
        std::vector<Card> untried_moves = node->get_untried_moves(state.get_moves());
        if(untried_moves.size() != 0) { // non-terminal, we can expand.
            int randomIndex = rand() % untried_moves.size();
            Card card = untried_moves.at(randomIndex);
            player_move p_move = std::make_tuple(state.get_player_to_move(), card);
            state.do_move(p_move);
            node = node->add_child(p_move);
        }

        // Simulate
        while(state.get_moves().size() != 0) {
            int randomIndex = rand() % state.get_moves().size();
            Card card = state.get_moves().at(randomIndex);
            player_move p_move = std::make_tuple(state.get_player_to_move(), card);
            state.do_move(p_move);
        }

        // Backpropagate
        while(node != NULL) {
            node->update(state);
            node = node->m_parent_node;
        }
    }


}