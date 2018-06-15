//
// Created by jamie on 05/06/18.
//

#include <algorithm>
#include <chrono>
#include "Board.h"
#include "Deck.h"


Board::Board() : m_current_trick(NULL)
{
    Deck deck;
    deck.shuffle_Deck();
    for (unsigned int i(0); i < 13; ++i)
    {
        m_player_hands[1].push_back(deck.getOneCard());
        m_player_hands[2].push_back(deck.getOneCard());
        m_player_hands[3].push_back(deck.getOneCard());
        m_player_hands[4].push_back(deck.getOneCard());
    }
}

player_move Board::getRandomLegalCard(int player_number)
{
    Hand *players_Hand = &m_player_hands[player_number];

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

void Board::remove_card_from_hand(Hand* hand, Card card)
{
    for(std::vector<Card>::iterator it = hand->begin(); it != hand->end(); ++it) {
        if(it->get_suit() == card.get_suit() && it->get_rank() == card.get_rank()) {
            it = hand->erase(it);
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
    Hand hand = m_player_hands.find(m_player_to_move)->second;

    if(m_current_trick == NULL) {
        return hand;
    }
    else{
        Hand legalMovesFromHand;
        bool has_cards_of_asked_suit = false;
        for(Hand::iterator it = hand.begin(); it != hand.end(); ++it) {
            if(it->get_suit() == m_current_trick->getSuitAsked()) {
                has_cards_of_asked_suit = true;
                Card card(it->get_suit(), it->get_rank());
                legalMovesFromHand.push_back(card);
            }
        }
        if(has_cards_of_asked_suit) {
            return legalMovesFromHand;
        }
        return hand;
    }
}

void Board::do_move(player_move move)
{
    Card card = std::get<1>(move);
    if(m_current_trick == NULL) {
        int suit_asked = card.get_suit();
        m_current_trick = new Trick(m_current_trump_suit, suit_asked);
    }

    m_player_to_move = get_next_player(m_player_to_move);

    m_discard_pile.push_back(card);

    trick_result result = m_current_trick->player_plays_card(move);
    int trick_result_code;
    int player_number;
    int score;
    std::tie(trick_result_code, player_number, score) = result;

    if(trick_result_code != Trick::TRICK_RESULT_CODE_STILL_IN_PLAY) {
        Hand* hand = m_player_hands.find(player_number)->second;
        remove_card_from_hand(hand, card);
        m_player_scores[player_number] = m_player_scores[player_number] + score;
        m_player_to_move = std::get<1>(result);
    }
}

Board Board::clone_and_randomize(int player_number)
{
    if(m_current_trick != NULL) {
        exit(0);
    }
    Board board(
        m_player_to_move,
        m_discard_pile,
        m_player_hands,
        m_player_scores,
        m_current_trump_suit
    );
    board.randomize(player_number);

    return board;
}

void Board::randomize(int player_number)
{
    std::vector<Card> deck;
    for (unsigned int i(1); i < 5; ++i)
    {
        if(i != player_number) {
            Hand hand = m_player_hands.find(i)->second;
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
                m_player_hands[i].push_back(card);
            }
        }
    }
}