//
// Created by jamie on 15/06/18.
//

#ifndef COPYCONST_NODE_H
#define COPYCONST_NODE_H


#include <string>

class Node {
public:
    Node() {};
    Node(std::string name) : m_name(name) {}
    Node( const Node &obj);

    std::string get_name() const;
    void set_name(std::string name);

private:
    std::string m_name;
};


#endif //COPYCONST_NODE_H
