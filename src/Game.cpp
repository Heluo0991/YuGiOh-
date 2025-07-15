#include "../include/Game.h"
#include "../include/CardDatabase.h"
#include <iostream>
#include <algorithm>

Game::Game(std::unique_ptr<Player> player1, std::unique_ptr<Player> player2)
    : player1_(std::move(player1)), player2_(std::move(player2)), 
      currentPlayer_(player1_.get()), opponent_(player2_.get()),
      state_(GameState::WAITING), currentPhase_(GamePhase::DRAW), turnCount_(0) {
    
    // 初始化卡组
    deck1_ = std::make_unique<Deck>();
    deck2_ = std::make_unique<Deck>();
    
    // 创建简单的测试卡组
    CardDatabase& db = CardDatabase::getInstance();
    db.initializeDatabase();
    
    // 为玩家1创建卡组
    for (int i = 0; i < 40; ++i) {
        int cardId = (i % 10) + 1;  // 循环使用前10张卡
        auto card = db.createCard(cardId);
        if (card) {
            deck1_->addCard(std::move(card));
        }
    }
    
    // 为玩家2创建卡组
    for (int i = 0; i < 40; ++i) {
        int cardId = (i % 10) + 1;
        auto card = db.createCard(cardId);
        if (card) {
            deck2_->addCard(std::move(card));
        }
    }
    
    deck1_->shuffle();
    deck2_->shuffle();
}

void Game::startGame() {
    if (state_ != GameState::WAITING) {
        return;
    }
    
    state_ = GameState::PLAYING;
    
    // 抽起始手牌
    auto startingHand1 = deck1_->drawCards(STARTING_HAND_SIZE);
    for (auto& card : startingHand1) {
        player1_->addCardToHand(std::move(card));
    }
    
    auto startingHand2 = deck2_->drawCards(STARTING_HAND_SIZE);
    for (auto& card : startingHand2) {
        player2_->addCardToHand(std::move(card));
    }
    
    std::cout << "游戏开始!" << std::endl;
    std::cout << player1_->getName() << " vs " << player2_->getName() << std::endl;
    
    // 开始第一回合
    currentPhase_ = GamePhase::DRAW;
    drawPhase();
}

void Game::endTurn() {
    if (state_ != GameState::PLAYING) {
        return;
    }
    
    currentPhase_ = GamePhase::END;
    std::cout << currentPlayer_->getName() << " 的回合结束" << std::endl;
    
    switchPlayer();
    turnCount_++;
    
    // 开始新回合
    currentPhase_ = GamePhase::DRAW;
    drawPhase();
}

void Game::nextPhase() {
    if (state_ != GameState::PLAYING) {
        return;
    }
    
    switch (currentPhase_) {
        case GamePhase::DRAW:
            currentPhase_ = GamePhase::MAIN1;
            std::cout << "进入主要阶段1" << std::endl;
            break;
        case GamePhase::MAIN1:
            currentPhase_ = GamePhase::BATTLE;
            std::cout << "进入战斗阶段" << std::endl;
            break;
        case GamePhase::BATTLE:
            currentPhase_ = GamePhase::MAIN2;
            std::cout << "进入主要阶段2" << std::endl;
            break;
        case GamePhase::MAIN2:
            endTurn();
            break;
        case GamePhase::END:
            // 自动处理，不需要手动调用
            break;
    }
}

void Game::switchPlayer() {
    std::swap(currentPlayer_, opponent_);
}

void Game::drawPhase() {
    std::cout << currentPlayer_->getName() << " 的回合开始" << std::endl;
    
    // 抽卡
    auto deck = (currentPlayer_ == player1_.get()) ? deck1_.get() : deck2_.get();
    auto card = deck->drawCard();
    
    if (card) {
        currentPlayer_->addCardToHand(std::move(card));
        std::cout << currentPlayer_->getName() << " 抽了一张卡" << std::endl;
    } else {
        std::cout << currentPlayer_->getName() << " 的卡组已空，败北!" << std::endl;
        state_ = GameState::FINISHED;
        return;
    }
    
    checkGameEnd();
}

void Game::checkGameEnd() {
    if (player1_->isDefeated() || player2_->isDefeated()) {
        state_ = GameState::FINISHED;
        std::cout << "游戏结束!" << std::endl;
        auto winner = getWinner();
        if (winner) {
            std::cout << winner->getName() << " 获胜!" << std::endl;
        }
    }
}

bool Game::isGameOver() const {
    return state_ == GameState::FINISHED;
}

Player* Game::getWinner() const {
    if (player1_->isDefeated()) {
        return player2_.get();
    } else if (player2_->isDefeated()) {
        return player1_.get();
    }
    return nullptr;
}

bool Game::summonMonster(int handIndex, int fieldPosition) {
    if (currentPhase_ != GamePhase::MAIN1 && currentPhase_ != GamePhase::MAIN2) {
        return false;
    }
    
    auto card = currentPlayer_->playCard(handIndex);
    if (!card || card->getType() != CardType::MONSTER) {
        return false;
    }
    
    auto monster = std::unique_ptr<MonsterCard>(static_cast<MonsterCard*>(card.release()));
    if (monster->canActivate()) {
        currentPlayer_->summonMonster(std::move(monster), fieldPosition);
        return true;
    }
    
    return false;
}

// 其他游戏操作的简化实现
bool Game::activateSpell(int handIndex) {
    if (currentPhase_ != GamePhase::MAIN1 && currentPhase_ != GamePhase::MAIN2) {
        return false;
    }
    
    auto card = currentPlayer_->playCard(handIndex);
    if (!card || card->getType() != CardType::SPELL) {
        return false;
    }
    
    card->activate();
    return true;
}

bool Game::setTrap(int handIndex, int position) {
    if (currentPhase_ != GamePhase::MAIN1 && currentPhase_ != GamePhase::MAIN2) {
        return false;
    }
    
    auto card = currentPlayer_->playCard(handIndex);
    if (!card || card->getType() != CardType::TRAP) {
        return false;
    }
    
    currentPlayer_->setSpellTrap(std::move(card), position);
    return true;
}

bool Game::canSummon(int handIndex) const {
    // 简化实现
    return currentPhase_ == GamePhase::MAIN1 || currentPhase_ == GamePhase::MAIN2;
}

bool Game::canActivateSpell(int handIndex) const {
    return currentPhase_ == GamePhase::MAIN1 || currentPhase_ == GamePhase::MAIN2;
}

bool Game::canSetTrap(int handIndex) const {
    return currentPhase_ == GamePhase::MAIN1 || currentPhase_ == GamePhase::MAIN2;
}

bool Game::canAttack(int monsterIndex) const {
    return currentPhase_ == GamePhase::BATTLE;
}

bool Game::attackMonster(int attackerIndex, int targetIndex) {
    // 简化的战斗实现
    return currentPhase_ == GamePhase::BATTLE;
}

bool Game::directAttack(int attackerIndex) {
    // 简化的直接攻击实现
    return currentPhase_ == GamePhase::BATTLE;
}

void Game::dealDamage(Player* target, int damage) {
    target->takeDamage(damage);
    checkGameEnd();
}
