#include "../include/CardDatabase.h"
#include <iostream>
#include <algorithm>

CardDatabase& CardDatabase::getInstance() {
    static CardDatabase instance;
    return instance;
}

void CardDatabase::initializeDatabase() {
    cardDatabase_.clear();
    
    // 添加一些示例怪兽卡
    addMonsterCard(1, "青眼白龙", "传说中的龙族，攻击力和守备力都很高", 
                   3000, 2500, 8, MonsterType::DRAGON, Attribute::LIGHT);
    
    addMonsterCard(2, "黑魔导", "究极的魔法师", 
                   2500, 2100, 7, MonsterType::SPELLCASTER, Attribute::DARK);
    
    addMonsterCard(3, "库里波", "毛茸茸的小怪兽", 
                   300, 200, 1, MonsterType::FIEND, Attribute::DARK);
    
    addMonsterCard(4, "元素英雄·闪光侠", "正义的英雄", 
                   1600, 1300, 4, MonsterType::WARRIOR, Attribute::LIGHT);
    
    addMonsterCard(5, "红眼黑龙", "黑暗中的龙族", 
                   2400, 2000, 7, MonsterType::DRAGON, Attribute::DARK);
    
    // 添加一些示例魔法卡
    addSpellCard(6, "黑洞", "破坏场上所有怪兽");
    addSpellCard(7, "死者苏生", "从墓地特殊召唤一只怪兽");
    addSpellCard(8, "雷击", "破坏一只怪兽");
    
    // 添加一些示例陷阱卡
    addTrapCard(9, "神圣防护罩-反射镜力", "破坏所有攻击表示的怪兽");
    addTrapCard(10, "激流葬", "破坏场上所有怪兽");
    
    std::cout << "卡片数据库初始化完成，共载入 " << cardDatabase_.size() << " 张卡片" << std::endl;
}

std::unique_ptr<Card> CardDatabase::createCard(int cardId) {
    auto it = std::find_if(cardDatabase_.begin(), cardDatabase_.end(),
        [cardId](const CardData& data) { return data.id == cardId; });
    
    if (it == cardDatabase_.end()) {
        return nullptr;
    }
    
    const CardData& data = *it;
    
    switch (data.type) {
        case CardType::MONSTER:
            return std::make_unique<MonsterCard>(data.id, data.name, data.description,
                                               data.attack, data.defense, data.level,
                                               data.monsterType, data.attribute);
        case CardType::SPELL:
            return std::make_unique<SpellCard>(data.id, data.name, data.description);
        case CardType::TRAP:
            return std::make_unique<TrapCard>(data.id, data.name, data.description);
        default:
            return nullptr;
    }
}

std::unique_ptr<MonsterCard> CardDatabase::createMonsterCard(int cardId) {
    auto card = createCard(cardId);
    if (card && card->getType() == CardType::MONSTER) {
        return std::unique_ptr<MonsterCard>(static_cast<MonsterCard*>(card.release()));
    }
    return nullptr;
}

std::unique_ptr<SpellCard> CardDatabase::createSpellCard(int cardId) {
    auto card = createCard(cardId);
    if (card && card->getType() == CardType::SPELL) {
        return std::unique_ptr<SpellCard>(static_cast<SpellCard*>(card.release()));
    }
    return nullptr;
}

std::unique_ptr<TrapCard> CardDatabase::createTrapCard(int cardId) {
    auto card = createCard(cardId);
    if (card && card->getType() == CardType::TRAP) {
        return std::unique_ptr<TrapCard>(static_cast<TrapCard*>(card.release()));
    }
    return nullptr;
}

bool CardDatabase::cardExists(int cardId) const {
    return std::find_if(cardDatabase_.begin(), cardDatabase_.end(),
        [cardId](const CardData& data) { return data.id == cardId; }) != cardDatabase_.end();
}

std::vector<int> CardDatabase::getAllCardIds() const {
    std::vector<int> ids;
    for (const auto& data : cardDatabase_) {
        ids.push_back(data.id);
    }
    return ids;
}

std::vector<int> CardDatabase::getCardsByType(CardType type) const {
    std::vector<int> ids;
    for (const auto& data : cardDatabase_) {
        if (data.type == type) {
            ids.push_back(data.id);
        }
    }
    return ids;
}

void CardDatabase::addMonsterCard(int id, const std::string& name, const std::string& description,
                                 int attack, int defense, int level, MonsterType monsterType, Attribute attribute) {
    CardData data;
    data.id = id;
    data.name = name;
    data.type = CardType::MONSTER;
    data.description = description;
    data.attack = attack;
    data.defense = defense;
    data.level = level;
    data.monsterType = monsterType;
    data.attribute = attribute;
    cardDatabase_.push_back(data);
}

void CardDatabase::addSpellCard(int id, const std::string& name, const std::string& description) {
    CardData data;
    data.id = id;
    data.name = name;
    data.type = CardType::SPELL;
    data.description = description;
    cardDatabase_.push_back(data);
}

void CardDatabase::addTrapCard(int id, const std::string& name, const std::string& description) {
    CardData data;
    data.id = id;
    data.name = name;
    data.type = CardType::TRAP;
    data.description = description;
    cardDatabase_.push_back(data);
}
