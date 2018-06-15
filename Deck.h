#ifndef DECK_H
#define DECK_H

#include <vector>
#include <iostream>
#include <fstream>
#include "Card.h"

using namespace std;

class Deck
{ 
public:
      Deck();
      void print_Deck() const;
      void shuffle_Deck();
      Card getOneCard();
private:
    std::vector<Card> m_deck;
};

#endif