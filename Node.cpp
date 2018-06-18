//
// Created by jamie on 12/06/18.
//

#include "Node.h"
#include "Board.h"
#include <cmath>
#include <algorithm>

std::vector<Card> Node::get_untried_moves(std::vector<Card> legalMoves)
{
    std::vector<Card> tried_cards;
    for (std::vector<Node*>::iterator childIterator = m_children.begin();
         childIterator != m_children.end(); ++childIterator)
    {
        player_move* tried_move = (*childIterator)->get_move();
        Card triedCard = std::get<1>(*tried_move);
        tried_cards.push_back(triedCard);
    }

    std::sort(legalMoves.begin(), legalMoves.end());
    std::sort(tried_cards.begin(), tried_cards.end());

    std::vector<Card> untried_moves;
    std::set_difference (legalMoves.begin(), legalMoves.end(), tried_cards.begin(), tried_cards.end(), back_inserter(untried_moves));

    return untried_moves;
}

player_move Node::get_move_from_most_visited_child_node()
{
    int largest_visit_number = -1;
    player_move player_move_of_most_visited_node;
    for (std::vector<Node*>::iterator childIterator = m_children.begin();
         childIterator != m_children.end(); ++childIterator)
    {
        if((*childIterator)->m_visits > largest_visit_number) {
            largest_visit_number = (*childIterator)->m_visits;
            player_move_of_most_visited_node = *((*childIterator)->get_move());
        }
    }
    return player_move_of_most_visited_node;
}

void Node::update(Board terminal_state)
{
    m_visits++;

    if(m_move != NULL) {
        int player_just_moved = std::get<0>(*m_move);
        m_wins += terminal_state.get_result(player_just_moved);
    }
}

Node* Node::UCB_select_child(std::vector<Card> legalMoves)
{
    std::vector<Node*> legal_children;

    for (std::vector<Node*>::iterator childIterator = m_children.begin();
         childIterator != m_children.end(); ++childIterator)
    {
        for (std::vector<Card>::iterator legalMoveIterator = legalMoves.begin(); legalMoveIterator != legalMoves.end();
             ++legalMoveIterator)
        {
            player_move* tried_move = (*childIterator)->get_move();
            Card triedCard = std::get<1>(*tried_move);
            Card legalMove = (*legalMoveIterator);
            if(Card::compare_cards(legalMove, triedCard) == true) {
                legal_children.push_back(*childIterator);
            }
        }
    }

    Node* max_score_node = new Node();
    int max_score = -1;
    for (std::vector<Node*>::iterator childIterator = legal_children.begin();
        childIterator != legal_children.end(); ++childIterator) {
        int current_score = (*childIterator)->get_UCB_score();
        if(current_score > max_score) {
            max_score = current_score;
            max_score_node = (*childIterator);
        }

        (*childIterator)->m_avails++;
    }
    if(max_score == -1) {
        return NULL;
    }
    return max_score_node;
}

Node* Node::add_child(player_move playerMove)
{
    Node* node = new Node(&playerMove, this);
    this->m_children.push_back(node);
    return node;
}

float Node::get_UCB_score()
{
    return (m_wins / m_visits) + exploration * sqrt(log(m_avails)/float(m_avails));
}

player_move* Node::get_move()
{
    return m_move;
}