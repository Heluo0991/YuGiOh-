#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Player.h"
#include "Deck.h"

enum class GamePhase {
    DRAW,
    MAIN1,
    BATTLE,
    MAIN2,
    END
};

enum class GameState {
    WAITING,
    PLAYING,
    FINISHED
};

class Game {
public:
    Game(std::unique_ptr<Player> player1, std::unique_ptr<Player> player2);
    ~Game() = default;
    
    // Game control
    void startGame();
    void endTurn();
    void nextPhase();
    
    // Game state
    GameState getState() const { return state_; }
    GamePhase getCurrentPhase() const { return currentPhase_; }
    Player* getCurrentPlayer() const { return currentPlayer_; }
    Player* getOpponent() const { return opponent_; }
    int getTurnCount() const { return turnCount_; }
    
    // Game actions
    bool summonMonster(int handIndex, int fieldPosition);
    bool activateSpell(int handIndex);
    bool setTrap(int handIndex, int position);
    bool attackMonster(int attackerIndex, int targetIndex);
    bool directAttack(int attackerIndex);
    
    // Game queries
    bool canSummon(int handIndex) const;
    bool canActivateSpell(int handIndex) const;
    bool canSetTrap(int handIndex) const;
    bool canAttack(int monsterIndex) const;
    
    // Game end conditions
    bool isGameOver() const;
    Player* getWinner() const;
    
private:
    std::unique_ptr<Player> player1_;
    std::unique_ptr<Player> player2_;
    std::unique_ptr<Deck> deck1_;
    std::unique_ptr<Deck> deck2_;
    
    Player* currentPlayer_;
    Player* opponent_;
    GameState state_;
    GamePhase currentPhase_;
    int turnCount_;
    
    void switchPlayer();
    void drawPhase();
    void checkGameEnd();
    void dealDamage(Player* target, int damage);
    
    static const int STARTING_HAND_SIZE = 5;
};
