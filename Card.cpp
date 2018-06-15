#include <stdlib.h>     /* srand, rand */
#include "Card.h"
#include <iostream>

const std::string SUIT[SUIT_MAX]  = {"S", "H", "D", "C"};
const std::string RANK[RANK_MAX]  = {"A", "2","3","4","5","6","7","8","9","10","J","Q","K"};


Card::Card()
{
}

Card::Card(const int &suit, const int &rank) : m_suit(suit), m_rank(rank)
{

}

bool Card::compare_cards(Card a, Card b)
{
    return a.m_rank == b.m_rank && a.m_suit == b.m_suit;
}

int Card::generate_suit()
{
    return rand() % (SUIT_MAX-1) + 0;
}

int Card::generate_rank()
{
    return rand() % (RANK_MAX-1) + 0;
}

std::string Card::Card2Str() const
{
    return RANK[get_rank()] + SUIT[get_suit()];
}

int Card::get_suit() const
{
    return m_suit;
}

int Card::get_rank() const
{
    return m_rank;
}