#include <iostream>
#include <cassert>
#include <memory>
#include "../include/Card.h"
#include "../include/Deck.h"
#include "../include/Player.h"
#include "../include/CardDatabase.h"

void testCardCreation() {
    std::cout << "测试卡片创建..." << std::endl;
    
    // 测试怪兽卡
    auto monster = std::make_unique<MonsterCard>(1, "青眼白龙", "传说中的龙", 
                                                3000, 2500, 8, MonsterType::DRAGON, Attribute::LIGHT);
    assert(monster->getName() == "青眼白龙");
    assert(monster->getAttack() == 3000);
    assert(monster->getDefense() == 2500);
    assert(monster->getLevel() == 8);
    
    // 测试魔法卡
    auto spell = std::make_unique<SpellCard>(2, "黑洞", "破坏所有怪兽");
    assert(spell->getName() == "黑洞");
    assert(spell->getType() == CardType::SPELL);
    
    // 测试陷阱卡
    auto trap = std::make_unique<TrapCard>(3, "神圣防护罩", "反射攻击");
    assert(trap->getName() == "神圣防护罩");
    assert(trap->getType() == CardType::TRAP);
    
    std::cout << "卡片创建测试通过!" << std::endl;
}

void testDeckOperations() {
    std::cout << "测试卡组操作..." << std::endl;
    
    Deck deck;
    assert(deck.isEmpty());
    assert(deck.size() == 0);
    
    // 添加卡片
    auto card1 = std::make_unique<MonsterCard>(1, "怪兽1", "测试怪兽", 
                                              1000, 1000, 4, MonsterType::WARRIOR, Attribute::LIGHT);
    auto card2 = std::make_unique<SpellCard>(2, "魔法1", "测试魔法");
    
    deck.addCard(std::move(card1));
    deck.addCard(std::move(card2));
    
    assert(deck.size() == 2);
    assert(!deck.isEmpty());
    
    // 抽卡
    auto drawnCard = deck.drawCard();
    assert(drawnCard != nullptr);
    assert(deck.size() == 1);
    
    std::cout << "卡组操作测试通过!" << std::endl;
}

void testPlayerOperations() {
    std::cout << "测试玩家操作..." << std::endl;
    
    Player player("测试玩家", 8000);
    assert(player.getName() == "测试玩家");
    assert(player.getLifePoints() == 8000);
    assert(player.getHandSize() == 0);
    assert(!player.isDefeated());
    
    // 测试伤害
    player.takeDamage(2000);
    assert(player.getLifePoints() == 6000);
    
    // 测试治疗
    player.heal(1000);
    assert(player.getLifePoints() == 7000);
    
    // 测试手牌
    auto card = std::make_unique<MonsterCard>(1, "怪兽", "测试", 
                                             1000, 1000, 4, MonsterType::WARRIOR, Attribute::LIGHT);
    player.addCardToHand(std::move(card));
    assert(player.getHandSize() == 1);
    
    std::cout << "玩家操作测试通过!" << std::endl;
}

void testCardDatabase() {
    std::cout << "测试卡片数据库..." << std::endl;
    
    CardDatabase& db = CardDatabase::getInstance();
    db.initializeDatabase();
    
    // 测试卡片存在性
    assert(db.cardExists(1));
    assert(db.cardExists(2));
    assert(!db.cardExists(999));
    
    // 测试卡片创建
    auto card = db.createCard(1);
    assert(card != nullptr);
    assert(card->getType() == CardType::MONSTER);
    
    auto monster = db.createMonsterCard(1);
    assert(monster != nullptr);
    assert(monster->getName() == "青眼白龙");
    
    std::cout << "卡片数据库测试通过!" << std::endl;
}

int main() {
    std::cout << "开始运行测试..." << std::endl;
    
    try {
        testCardCreation();
        testDeckOperations();
        testPlayerOperations();
        testCardDatabase();
        
        std::cout << "\n所有测试通过!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "测试失败: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
