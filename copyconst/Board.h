//
// Created by jamie on 15/06/18.
//

#ifndef COPYCONST_BOARD_H
#define COPYCONST_BOARD_H


#include <vector>
#include "Node.h"

class Board {
public:
    Board();
    Board(std::map<int, Node*> nodes) : m_nodes(nodes) {};
    Board( const Board &obj);
    std::map<int, Node*> m_nodes;
};


#endif //COPYCONST_BOARD_H
