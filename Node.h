//
// Created by jamie on 12/06/18.
//

#ifndef SLIPPERYBOT_NODE_H
#define SLIPPERYBOT_NODE_H


#include "Trick.h"
#include "Board.h"
#include <vector>

class Node {
public:
    Node* m_parent_node;

    Node() : m_move(NULL), m_parent_node(NULL) {}
    Node(player_move* move, Node* parent) :
        m_move(move),
        m_parent_node(parent)
    {
    }

    Node*               UCB_select_child(std::vector<Card> legalMoves);
    Node*               add_child(player_move playerMove);

    std::vector<Card>   get_untried_moves(std::vector<Card> legalMoves);
    player_move*        get_move();
    float               get_UCB_score();
    void                update(Board state);

private:
    const double exploration = 0.7;
    player_move* m_move; // move that got us here
    std::vector<Node*> m_children;
    int m_wins = 0;
    int m_visits = 0;
    int m_avails = 1;
};

#endif //SLIPPERYBOT_NODE_H