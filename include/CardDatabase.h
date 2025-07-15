#pragma once
#include <memory>
#include <vector>
#include "Card.h"

class CardDatabase {
public:
    static CardDatabase& getInstance();
    
    // Card creation
    std::unique_ptr<Card> createCard(int cardId);
    std::unique_ptr<MonsterCard> createMonsterCard(int cardId);
    std::unique_ptr<SpellCard> createSpellCard(int cardId);
    std::unique_ptr<TrapCard> createTrapCard(int cardId);
    
    // Database queries
    bool cardExists(int cardId) const;
    std::vector<int> getAllCardIds() const;
    std::vector<int> getCardsByType(CardType type) const;
    
    // Initialize database
    void initializeDatabase();
    
private:
    CardDatabase() = default;
    ~CardDatabase() = default;
    CardDatabase(const CardDatabase&) = delete;
    CardDatabase& operator=(const CardDatabase&) = delete;
    
    struct CardData {
        int id;
        std::string name;
        CardType type;
        std::string description;
        // Monster-specific data
        int attack = 0;
        int defense = 0;
        int level = 0;
        MonsterType monsterType = MonsterType::WARRIOR;
        Attribute attribute = Attribute::LIGHT;
    };
    
    std::vector<CardData> cardDatabase_;
    
    void addMonsterCard(int id, const std::string& name, const std::string& description,
                       int attack, int defense, int level, MonsterType monsterType, Attribute attribute);
    void addSpellCard(int id, const std::string& name, const std::string& description);
    void addTrapCard(int id, const std::string& name, const std::string& description);
};
