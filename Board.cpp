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
    std::cout << "Board constructor." << std::endl;
}

Board::Board(const Board &obj)
{
    m_player_to_move = obj.m_player_to_move;
    m_discard_pile = obj.m_discard_pile;
    m_player_scores = obj.m_player_scores;
    m_current_trump_suit = obj.m_current_trump_suit;
    m_current_trick = NULL;
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
    for(std::vector<Card>::iterator it = players_Hand->begin(); it != players_Hand->end(); ++it) {
        if(it->get_suit() == m_current_trick->getSuitAsked()) {
            Card card(it->get_suit(), it->get_rank());
            return std::make_tuple(player_number, card);
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

void Board::remove_card_from_hand(Hand* hand, Card card)
{
    for(std::vector<Card>::iterator it = hand->begin(); it != hand->end(); ++it) {
        if(it->get_suit() == card.get_suit() && it->get_rank() == card.get_rank()) {
            hand->erase(it);
//            print_hand(*hand);
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
    Hand* hand = m_player_hands[m_player_to_move];

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

void Board::do_move(player_move move)
{
    int player_number;
    Card card;
    std::tie(player_number, card) = move;

    if(m_current_trick == NULL) {
        int suit_asked = card.get_suit();
        m_current_trick = new Trick(m_current_trump_suit, suit_asked);
    }

    m_player_to_move = get_next_player(m_player_to_move);

    m_discard_pile.push_back(card);

    trick_result result = m_current_trick->player_plays_card(move);
    int trick_result_code = std::get<0>(result);
    int trick_winning_player_number;
    int score;
    std::tie(trick_result_code, trick_winning_player_number, score) = result;

    Hand* hand = m_player_hands[player_number];
    remove_card_from_hand(hand, card);
    if(trick_result_code == Trick::TRICK_RESULT_CODE_FINISHED) {
        m_player_scores[trick_winning_player_number] = m_player_scores[trick_winning_player_number] + score;
        m_player_to_move = std::get<1>(result);
        m_current_trick = NULL;
    }
}

void Board::randomize(int player_number)
{
    std::vector<Card> deck;
    for (unsigned int i(1); i < 5; ++i)
    {
        if(i != player_number) {
            Hand hand = *m_player_hands[i];
            m_player_hands.erase(i);
            deck.insert(deck.end(), hand.begin(), hand.end());
        }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(std::begin(deck), std::end(deck), e);

    while(deck.size() != 0) {
        for (unsigned int i(1); i < 5; ++i)
        {
            if(i != player_number) {
                Card card(deck.back().get_suit(), deck.back().get_rank());
                deck.pop_back();

                if (m_player_hands.count(i) == 1) { // if value exists for key
                    m_player_hands[i]->push_back(card);
                }
                else{
                    Hand* newHand = new Hand();
                    newHand->push_back(card);
                    m_player_hands.insert(std::pair<int, Hand*>(i, newHand));
                }
            }
        }
    }
}