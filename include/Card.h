#pragma once
#include <string>
#include <vector>
#include <memory>

enum class CardType {
    MONSTER,
    SPELL,
    TRAP
};

enum class MonsterType {
    WARRIOR,
    SPELLCASTER,
    DRAGON,
    BEAST,
    MACHINE,
    FIEND,
    FAIRY,
    AQUA,
    PYRO,
    THUNDER,
    ROCK,
    PLANT,
    INSECT,
    DINOSAUR,
    FISH,
    SEA_SERPENT,
    REPTILE,
    PSYCHIC,
    DIVINE_BEAST,
    CREATOR_GOD,
    WYRM,
    CYBERSE
};

enum class Attribute {
    LIGHT,
    DARK,
    FIRE,
    WATER,
    EARTH,
    WIND,
    DIVINE
};

class Card {
public:
    Card(int id, const std::string& name, CardType type, const std::string& description);
    virtual ~Card() = default;
    
    // Getters
    int getId() const { return id_; }
    const std::string& getName() const { return name_; }
    CardType getType() const { return type_; }
    const std::string& getDescription() const { return description_; }
    
    // Virtual functions for card effects
    virtual void activate() = 0;
    virtual bool canActivate() const = 0;
    virtual Card* clone() const = 0;
    
protected:
    int id_;
    std::string name_;
    CardType type_;
    std::string description_;
};

class MonsterCard : public Card {
public:
    MonsterCard(int id, const std::string& name, const std::string& description,
                int attack, int defense, int level, MonsterType monsterType, Attribute attribute);
    
    // Getters
    int getAttack() const { return attack_; }
    int getDefense() const { return defense_; }
    int getLevel() const { return level_; }
    MonsterType getMonsterType() const { return monsterType_; }
    Attribute getAttribute() const { return attribute_; }
    
    // Setters for game effects
    void setAttack(int attack) { attack_ = attack; }
    void setDefense(int defense) { defense_ = defense; }
    
    // Card interface
    void activate() override;
    bool canActivate() const override;
    Card* clone() const override;
    
private:
    int attack_;
    int defense_;
    int level_;
    MonsterType monsterType_;
    Attribute attribute_;
};

class SpellCard : public Card {
public:
    SpellCard(int id, const std::string& name, const std::string& description);
    
    void activate() override;
    bool canActivate() const override;
    Card* clone() const override;
};

class TrapCard : public Card {
public:
    TrapCard(int id, const std::string& name, const std::string& description);
    
    void activate() override;
    bool canActivate() const override;
    Card* clone() const override;
    
private:
    bool isSet_ = false;
    
public:
    void setTrap() { isSet_ = true; }
    bool isSet() const { return isSet_; }
};
