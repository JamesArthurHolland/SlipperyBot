//
// Created by jamie on 15/06/18.
//

#include "Node.h"

Node::Node(const Node &obj)
{
    m_name = obj.get_name();
}

std::string Node::get_name() const
{
    return m_name;
}

void Node::set_name(std::string name)
{
    m_name = name;
}