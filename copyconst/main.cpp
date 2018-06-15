#include <iostream>
#include <map>
#include "Node.h"
#include "Board.h"

int main() {

//
//    std::map<int, Node*> nodes;
//    Node* A = new Node("it's A");
//    Node* B = new Node("it's B");
//    Node* C = new Node("it's C");
//    Node* D = new Node("it's D");
//    nodes.insert(std::pair<int, Node*>(0, A));
//    nodes.insert(std::pair<int, Node*>(1, B));
//    nodes.insert(std::pair<int, Node*>(2, C));
//    nodes.insert(std::pair<int, Node*>(3, D));
//
//    std::cout << A->get_name() << std::endl;
//    std::cout << B->get_name() << std::endl;
//    std::cout << C->get_name() << std::endl;
//    std::cout << D->get_name() << std::endl;
//    std::cout << "-----loop------" << std::endl;
//
//    std::map<int, Node*> nodes2;
//    for(auto const &pair : nodes) {
//        std::cout << pair.second->get_name() << std::endl;
//        Node* newNodePtr = new Node();
//        *newNodePtr = *pair.second;
//        nodes2.insert(std::pair<int, Node*>(pair.first, newNodePtr));
//
//    }
//    std::cout << "-----nodes2------" << std::endl;
//    std::cout << nodes2[0]->get_name() << std::endl;
//    std::cout << nodes2[1]->get_name() << std::endl;
//    std::cout << nodes2[2]->get_name() << std::endl;
//    std::cout << nodes2[3]->get_name() << std::endl;
//    nodes2[0]->set_name("2-0");
//    nodes2[1]->set_name("2-1");
//    nodes2[2]->set_name("2-2");
//    nodes2[3]->set_name("2-3");
//
//    std::cout << "-----nodes2------" << std::endl;
//    std::cout << nodes2[0]->get_name() << std::endl;
//    std::cout << nodes2[1]->get_name() << std::endl;
//    std::cout << nodes2[2]->get_name() << std::endl;
//    std::cout << nodes2[3]->get_name() << std::endl;
//
//    std::cout << "-------orginal letter pointers----" << std::endl;
//
//    std::cout << A->get_name() << std::endl;
//    std::cout << B->get_name() << std::endl;
//    std::cout << C->get_name() << std::endl;
//    std::cout << D->get_name() << std::endl;
//    std::cout << "-----------" << std::endl;


    std::map<int, Node*> nodes;
    Node* A = new Node("it's A");
    Node* B = new Node("it's B");
    Node* C = new Node("it's C");
    Node* D = new Node("it's D");
    std::cout << A->get_name() << std::endl;
    std::cout << B->get_name() << std::endl;
    std::cout << C->get_name() << std::endl;
    std::cout << D->get_name() << std::endl;
    nodes.insert(std::pair<int, Node*>(0, A));
    nodes.insert(std::pair<int, Node*>(1, B));
    nodes.insert(std::pair<int, Node*>(2, C));
    nodes.insert(std::pair<int, Node*>(3, D));


    Board board(nodes);
    Board board2 = board;
    board.m_nodes[0]->set_name("A FUCKED");

    std::cout << "-----------" << std::endl;
    std::cout << A->get_name() << std::endl;
    std::cout << B->get_name() << std::endl;
    std::cout << C->get_name() << std::endl;
    std::cout << D->get_name() << std::endl;

    std::cout << "-----nodes2------" << std::endl;
    std::cout << board2.m_nodes[0]->get_name() << std::endl;
    std::cout << board2.m_nodes[1]->get_name() << std::endl;
    std::cout << board2.m_nodes[2]->get_name() << std::endl;
    std::cout << board2.m_nodes[3]->get_name() << std::endl;

    return 0;
}