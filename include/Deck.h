#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include "Card.h"

class Deck {
public:
    Deck();
    ~Deck() = default;
    
    // Deck management
    void addCard(std::unique_ptr<Card> card);
    void removeCard(int cardId);
    void shuffle();
    
    // Drawing cards
    std::unique_ptr<Card> drawCard();
    std::vector<std::unique_ptr<Card>> drawCards(int count);
    
    // Deck info
    size_t size() const { return cards_.size(); }
    bool isEmpty() const { return cards_.empty(); }
    
    // Deck validation
    bool isValidDeck() const;
    
private:
    std::vector<std::unique_ptr<Card>> cards_;
    std::random_device rd_;
    std::mt19937 gen_;
    
    static const int MIN_DECK_SIZE = 40;
    static const int MAX_DECK_SIZE = 60;
};
