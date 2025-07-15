#include "../include/Deck.h"
#include <chrono>
#include <algorithm>
#include <iostream>

Deck::Deck() : gen_(rd_()) {}

void Deck::addCard(std::unique_ptr<Card> card) {
    if (card && cards_.size() < MAX_DECK_SIZE) {
        cards_.push_back(std::move(card));
    }
}

void Deck::removeCard(int cardId) {
    auto it = std::find_if(cards_.begin(), cards_.end(),
        [cardId](const std::unique_ptr<Card>& card) {
            return card->getId() == cardId;
        });
    
    if (it != cards_.end()) {
        cards_.erase(it);
    }
}

void Deck::shuffle() {
    std::shuffle(cards_.begin(), cards_.end(), gen_);
    std::cout << "卡组已洗牌" << std::endl;
}

std::unique_ptr<Card> Deck::drawCard() {
    if (cards_.empty()) {
        return nullptr;
    }
    
    auto card = std::move(cards_.back());
    cards_.pop_back();
    return card;
}

std::vector<std::unique_ptr<Card>> Deck::drawCards(int count) {
    std::vector<std::unique_ptr<Card>> drawnCards;
    
    for (int i = 0; i < count && !cards_.empty(); ++i) {
        drawnCards.push_back(drawCard());
    }
    
    return drawnCards;
}

bool Deck::isValidDeck() const {
    return cards_.size() >= MIN_DECK_SIZE && cards_.size() <= MAX_DECK_SIZE;
}
