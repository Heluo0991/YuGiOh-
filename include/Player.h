#pragma once
#include <vector>
#include <memory>
#include "Card.h"

class Player {
public:
    Player(const std::string& name, int lifePoints = 8000);
    ~Player() = default;
    
    // Player info
    const std::string& getName() const { return name_; }
    int getLifePoints() const { return lifePoints_; }
    void setLifePoints(int lifePoints) { lifePoints_ = lifePoints; }
    void takeDamage(int damage);
    void heal(int amount);
    
    // Hand management
    void addCardToHand(std::unique_ptr<Card> card);
    std::unique_ptr<Card> playCard(int index);
    const std::vector<std::unique_ptr<Card>>& getHand() const { return hand_; }
    size_t getHandSize() const { return hand_.size(); }
    
    // Field management
    void summonMonster(std::unique_ptr<MonsterCard> monster, int position);
    void setSpellTrap(std::unique_ptr<Card> card, int position);
    const std::vector<std::unique_ptr<MonsterCard>>& getField() const { return field_; }
    const std::vector<std::unique_ptr<Card>>& getSpellTrapZone() const { return spellTrapZone_; }
    
    // Game state
    bool isDefeated() const { return lifePoints_ <= 0; }
    
private:
    std::string name_;
    int lifePoints_;
    std::vector<std::unique_ptr<Card>> hand_;
    std::vector<std::unique_ptr<MonsterCard>> field_;
    std::vector<std::unique_ptr<Card>> spellTrapZone_;
    
    static const int MAX_HAND_SIZE = 7;
    static const int MAX_FIELD_SIZE = 5;
    static const int MAX_SPELL_TRAP_SIZE = 5;
};
