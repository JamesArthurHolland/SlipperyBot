#ifndef CARD_H
#define CARD_H

#include <string>
#include <tuple>
#include <vector>

const int SUIT_MAX(4);
const int RANK_MAX(13);
const int CARDS_MAX(13);

class Card
{
    friend class Deck; // Deck Class needs to access to Card Class but not vice versa
public:
    explicit Card();
    explicit Card(const int &suit, const int &rank);

    bool operator<( const Card& other_card ) const {
        return m_rank > other_card.get_rank();
    }

    std::string Card2Str() const;

    int get_suit() const;

    int get_rank() const;

    static bool compare_cards(Card a, Card b);

private:
    int generate_suit();
    int generate_rank();

    int m_suit;
    int m_rank;
};

typedef std::vector<Card> Hand; // playernumber, card

#endif