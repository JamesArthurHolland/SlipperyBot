#include <iostream>
#include "Deck.h"
#include "Card.h"
#include <algorithm>
#include <random>
#include <chrono>

Deck::Deck()
{
    for (unsigned int i(0); i < SUIT_MAX; ++i)
    {
        for (unsigned int j(0); j < RANK_MAX; ++j)
        {
            Card card(i, j);
            m_deck.push_back(card);
        }
    }
}


void Deck::print_Deck() const
{
    unsigned int count(1);

    for (unsigned int i(0); i < m_deck.size(); ++i)
    {
        std::cout << m_deck[i].Card2Str() << " ";
        if ( count == 13 )
        {
            std::cout << std::endl;
            count = 0;
        }
        ++count;
    }
}

void Deck::shuffle_Deck()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(std::begin(m_deck), std::end(m_deck), e);
}



Card Deck::getOneCard()
{
    Card cd(m_deck.back().get_suit(), m_deck.back().get_rank());
    m_deck.pop_back();
    return cd;
}