#include "../include/Player.h"
#include <iostream>
#include <algorithm>

Player::Player(const std::string& name, int lifePoints)
    : name_(name), lifePoints_(lifePoints) {
    field_.resize(MAX_FIELD_SIZE);
    spellTrapZone_.resize(MAX_SPELL_TRAP_SIZE);
}

void Player::takeDamage(int damage) {
    lifePoints_ -= damage;
    if (lifePoints_ < 0) {
        lifePoints_ = 0;
    }
    std::cout << name_ << " 受到 " << damage << " 点伤害! 剩余生命值: " << lifePoints_ << std::endl;
}

void Player::heal(int amount) {
    lifePoints_ += amount;
    std::cout << name_ << " 恢复 " << amount << " 点生命值! 当前生命值: " << lifePoints_ << std::endl;
}

void Player::addCardToHand(std::unique_ptr<Card> card) {
    if (card && hand_.size() < MAX_HAND_SIZE) {
        hand_.push_back(std::move(card));
    }
}

std::unique_ptr<Card> Player::playCard(int index) {
    if (index >= 0 && index < hand_.size()) {
        auto card = std::move(hand_[index]);
        hand_.erase(hand_.begin() + index);
        return card;
    }
    return nullptr;
}

void Player::summonMonster(std::unique_ptr<MonsterCard> monster, int position) {
    if (position >= 0 && position < MAX_FIELD_SIZE && !field_[position] && monster) {
        std::cout << name_ << " 召唤了 " << monster->getName() << std::endl;
        field_[position] = std::move(monster);
    }
}

void Player::setSpellTrap(std::unique_ptr<Card> card, int position) {
    if (position >= 0 && position < MAX_SPELL_TRAP_SIZE && !spellTrapZone_[position] && card) {
        if (card->getType() == CardType::TRAP) {
            auto trapCard = static_cast<TrapCard*>(card.get());
            trapCard->setTrap();
            std::cout << name_ << " 盖放了一张陷阱卡" << std::endl;
        } else {
            std::cout << name_ << " 发动了魔法卡: " << card->getName() << std::endl;
            card->activate();
        }
        spellTrapZone_[position] = std::move(card);
    }
}
