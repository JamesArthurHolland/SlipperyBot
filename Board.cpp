//
// Created by jamie on 05/06/18.
//

#include <algorithm>
#include <chrono>
#include <random>
#include "Board.h"
#include "Deck.h"
#include "Node.h"


Board::Board() : m_current_trick(NULL)
{
    Deck deck;
    deck.shuffle_Deck();

    Hand* hand1 = new Hand();
    Card card = deck.getOneCard();
    hand1->push_back(card);
    m_player_hands.insert(std::pair<int, Hand*>(1, hand1));

    Hand* hand2 = new Hand();
    hand2->push_back(deck.getOneCard());
    m_player_hands.insert(std::pair<int, Hand*>(2, hand2));

    Hand* hand3 = new Hand();
    hand3->push_back(deck.getOneCard());
    m_player_hands.insert(std::pair<int, Hand*>(3, hand3));

    Hand* hand4 = new Hand();
    hand4->push_back(deck.getOneCard());
    m_player_hands.insert(std::pair<int, Hand*>(4, hand4));

    for (unsigned int i(0); i < 12; ++i)
    {
        m_player_hands[1]->push_back(deck.getOneCard());
        m_player_hands[2]->push_back(deck.getOneCard());
        m_player_hands[3]->push_back(deck.getOneCard());
        m_player_hands[4]->push_back(deck.getOneCard());
    }

    for (unsigned int i(1); i < 5; ++i)
    {
        m_player_scores[i] = 0;
    }

    SuitPlayCapability player1_suit_capability;
    m_player_suited_capabilities.insert(std::pair<int, SuitPlayCapability>(1, player1_suit_capability));

    SuitPlayCapability player2_suit_capability;
    m_player_suited_capabilities.insert(std::pair<int, SuitPlayCapability>(2, player2_suit_capability));

    SuitPlayCapability player3_suit_capability;
    m_player_suited_capabilities.insert(std::pair<int, SuitPlayCapability>(3, player3_suit_capability));

    SuitPlayCapability player4_suit_capability;
    m_player_suited_capabilities.insert(std::pair<int, SuitPlayCapability>(4, player4_suit_capability));

    m_player_to_move = rand() % 4 + 1; // TODO
}

Board::Board(const Board &obj)
{
    m_player_to_move = obj.m_player_to_move;
    m_discard_pile = obj.m_discard_pile;
    m_player_scores = obj.m_player_scores;
    m_player_suited_capabilities = obj.m_player_suited_capabilities;
    m_current_trump_suit = obj.m_current_trump_suit;
    if(obj.m_current_trick == NULL) {
        m_current_trick = NULL;
    }
    else{
        Trick trick = *obj.m_current_trick;
        m_current_trick = new Trick();
        *m_current_trick = trick;
    }
    for(auto const &pair : obj.m_player_hands) {
        Hand* newHandPointer = new Hand();
        *newHandPointer = *pair.second;
        m_player_hands.insert(std::pair<int, Hand*>(pair.first, newHandPointer));
    }
}

player_move Board::getRandomLegalCard(int player_number)
{
    Hand* players_Hand = m_player_hands[player_number];

    // First loop for asked suit
    if(m_current_trick != NULL) {
      for(std::vector<Card>::iterator it = players_Hand->begin(); it != players_Hand->end(); ++it) {
        if (it->get_suit() == m_current_trick->getSuitAsked()) {
          Card card(it->get_suit(), it->get_rank());
          return std::make_tuple(player_number, card);
        }
      }
    }

    //Return first legal card - already shuffled so already random
    Card card(players_Hand->back().get_suit(), players_Hand->back().get_rank());
    return std::make_tuple(player_number, card);
}

int Board::get_result(int player_number) // TODO implement draw - 2 people have same score
{
    int lowest_score = INT32_MAX;

    for (unsigned int i(1); i < 5; ++i) {
        int current_score = m_player_scores[i];
        if(current_score < lowest_score) {
            lowest_score = current_score;
        }
    }

    if(lowest_score == m_player_scores[player_number]) {
        return 1;
    }
    return 0;
}

void Board::print_hand(Hand hand)
{
  std::cout << "Printing hand...." << std::endl;
  for(std::vector<Card>::iterator it = hand.begin(); it != hand.end(); ++it) {
    std::cout << "Card is " << it->Card2Str() << std::endl;
  }
  std::cout << "...." << std::endl;
}

void Board::remove_card_from_cards(Hand* hand, Card card)
{
    for(std::vector<Card>::iterator it = hand->begin(); it != hand->end(); ++it) {
        if(it->get_suit() == card.get_suit() && it->get_rank() == card.get_rank()) {
            hand->erase(it);
            return;
        }
    }
}

int Board::get_next_player(int player_number)
{
    return (player_number % 4) + 1; // TODO fix 4 magic
}

int Board::get_player_to_move()
{
    return m_player_to_move;
}

std::vector<Card> Board::get_moves()
{
    if(m_player_hands.count(m_player_to_move) == 1) { // hand exists still (cards left)
        Hand* hand = m_player_hands[m_player_to_move];
        if(hand->size() == 1) {
            return *hand;
        }

        if(m_current_trick == NULL) {
            return *hand;
        }
        else{
            Hand legalMovesFromHand;
            bool has_cards_of_asked_suit = false;
            for(Hand::iterator it = hand->begin(); it != hand->end(); ++it) {
                if(it->get_suit() == m_current_trick->getSuitAsked()) {
                    has_cards_of_asked_suit = true;
                    Card card(it->get_suit(), it->get_rank());
                    legalMovesFromHand.push_back(card);
                }
            }
            if(has_cards_of_asked_suit) {
                return legalMovesFromHand;
            }
            return *hand;
        }
    }
    return std::vector<Card>();
}

void Board::print_scores()
{
    std::cout << m_player_scores[1];
    std::cout << " " << m_player_scores[2];
    std::cout << " " << m_player_scores[3];
    std::cout << " " << m_player_scores[4] << std::endl;
}

int Board::get_winner()
{
    int winner = 0;
    int lowest_score = INT16_MAX;

    for (unsigned int i(1); i < 5; ++i) {
        int current_score = m_player_scores[i];
        if (current_score < lowest_score) {
            lowest_score = current_score;
            winner = i;
        }
    }

    return  winner;
}

void Board::do_move(player_move move)
{
    int player_number;
    Card card;
    std::tie(player_number, card) = move;

    if(m_current_trick == NULL) {
        int suit_asked = card.get_suit();
        m_current_trick = new Trick(m_current_trump_suit, suit_asked);
    }
    if(card.get_suit() != m_current_trick->getSuitAsked()) {
//        std::cout << "Player " << player_number  << " can no longer play: " << m_current_trick->getSuitAsked() << std::endl;
        m_player_suited_capabilities[player_number].can_play_suit(m_current_trick->getSuitAsked(), false);
    }

    trick_result result = m_current_trick->player_plays_card(move);
    int trick_result_code = std::get<0>(result);
    int trick_winning_player_number;
    int score;
    std::tie(trick_result_code, trick_winning_player_number, score) = result;

    Hand* hand = m_player_hands[player_number];
    remove_card_from_cards(hand, card);
    if(trick_result_code == Trick::TRICK_RESULT_CODE_FINISHED) {
        m_player_scores[trick_winning_player_number] = m_player_scores[trick_winning_player_number] + score;
        m_player_to_move = std::get<1>(result);
        m_current_trick = NULL;
    }

    m_discard_pile.push_back(card);
    m_player_to_move = get_next_player(m_player_to_move);
}

int Board::discard_pile_size()
{
    return m_discard_pile.size();
}

std::vector<Card> shuffle_cards(std::vector<Card> cards) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(std::begin(cards), std::end(cards), e);
    return cards;
}

bool Board::suited_capabilities_met()
{
    for(auto const &pair : m_player_suited_capabilities) {
        int player_number = pair.first;
        SuitPlayCapability capability = pair.second;
        Hand hand = *m_player_hands[player_number];
        if(capability.are_capabilities_broken(hand)) {
            return false;
        }
    }
    return true;
}

void Board::randomize(int player_number)
{
    std::vector<Card> deck;
    do {
        for (unsigned int i(1); i < 5; ++i) // get all the unknown cards, ie the players hands
        {
            if(i != player_number) {
                Hand hand = *m_player_hands[i];
                m_player_hands.erase(i);
                deck.insert(deck.end(), hand.begin(), hand.end());
            }
        }
        deck = shuffle_cards(deck);

        unsigned int current_player_number = 1; // TODO better nomenclature, conflicts with param
        if(m_current_trick != NULL) {
            // People who've already played in trick will be down cards.
            // Dealing from this player means always have same number of cards after trick
            current_player_number = m_player_to_move;
        }
        while ( deck.size() != 0 )
        {
            if(current_player_number != player_number) {
                // TODO get subset of deck that is equal to cards that player_number could possibly have -> suit caps
                // Shuffle and return random card
                Card card(deck.back().get_suit(), deck.back().get_rank());
                deck.pop_back();

                if (m_player_hands.count(current_player_number) == 1) { // if value exists for key
                    m_player_hands[current_player_number]->push_back(card);
                }
                else{
                    Hand* newHand = new Hand();
                    newHand->push_back(card);
                    m_player_hands.insert(std::pair<int, Hand*>(current_player_number, newHand));
                }
            }
            current_player_number = get_next_player(current_player_number);
        }
    }
    while( suited_capabilities_met() == false );
}