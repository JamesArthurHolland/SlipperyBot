//
// Created by jamie on 15/06/18.
//

#include <map>
#include <iostream>
#include "Board.h"

Board::Board()
{

}

Board::Board(const Board &obj)
{
    std::map<int, Node*> nodes2;
    for(auto const &pair : obj.m_nodes) {
        Node* newNodePtr = new Node();
        *newNodePtr = *pair.second;
        m_nodes.insert(std::pair<int, Node*>(pair.first, newNodePtr));

    }
}