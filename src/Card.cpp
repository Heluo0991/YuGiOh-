#include "../include/Card.h"
#include <iostream>

// Card 基类实现
Card::Card(int id, const std::string& name, CardType type, const std::string& description)
    : id_(id), name_(name), type_(type), description_(description) {}

// MonsterCard 实现
MonsterCard::MonsterCard(int id, const std::string& name, const std::string& description,
                        int attack, int defense, int level, MonsterType monsterType, Attribute attribute)
    : Card(id, name, CardType::MONSTER, description), attack_(attack), defense_(defense), 
      level_(level), monsterType_(monsterType), attribute_(attribute) {}

void MonsterCard::activate() {
    std::cout << "召唤怪兽: " << name_ << " (攻击力: " << attack_ << ", 守备力: " << defense_ << ")" << std::endl;
}

bool MonsterCard::canActivate() const {
    // 简化版本：等级4以下可以直接召唤
    return level_ <= 4;
}

Card* MonsterCard::clone() const {
    return new MonsterCard(*this);
}

// SpellCard 实现
SpellCard::SpellCard(int id, const std::string& name, const std::string& description)
    : Card(id, name, CardType::SPELL, description) {}

void SpellCard::activate() {
    std::cout << "发动魔法卡: " << name_ << std::endl;
}

bool SpellCard::canActivate() const {
    return true;  // 简化版本：魔法卡总是可以发动
}

Card* SpellCard::clone() const {
    return new SpellCard(*this);
}

// TrapCard 实现
TrapCard::TrapCard(int id, const std::string& name, const std::string& description)
    : Card(id, name, CardType::TRAP, description), isSet_(false) {}

void TrapCard::activate() {
    if (isSet_) {
        std::cout << "发动陷阱卡: " << name_ << std::endl;
    } else {
        std::cout << "陷阱卡必须先盖放才能发动!" << std::endl;
    }
}

bool TrapCard::canActivate() const {
    return isSet_;
}

Card* TrapCard::clone() const {
    return new TrapCard(*this);
}
