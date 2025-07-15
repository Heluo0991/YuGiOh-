#include <iostream>
#include <memory>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "Game.h"
#include "Player.h"
#include "CardDatabase.h"

void printGameState(const Game& game) {
    std::cout << "\n=== 游戏状态 ===" << std::endl;
    std::cout << "当前回合: " << game.getTurnCount() << std::endl;
    std::cout << "当前玩家: " << game.getCurrentPlayer()->getName() << std::endl;
    std::cout << "当前阶段: ";
    
    switch (game.getCurrentPhase()) {
        case GamePhase::DRAW:
            std::cout << "抽卡阶段";
            break;
        case GamePhase::MAIN1:
            std::cout << "主要阶段1";
            break;
        case GamePhase::BATTLE:
            std::cout << "战斗阶段";
            break;
        case GamePhase::MAIN2:
            std::cout << "主要阶段2";
            break;
        case GamePhase::END:
            std::cout << "结束阶段";
            break;
    }
    std::cout << std::endl;
    
    std::cout << game.getCurrentPlayer()->getName() << " - 生命值: " 
              << game.getCurrentPlayer()->getLifePoints() 
              << ", 手牌数: " << game.getCurrentPlayer()->getHandSize() << std::endl;
    std::cout << game.getOpponent()->getName() << " - 生命值: " 
              << game.getOpponent()->getLifePoints() 
              << ", 手牌数: " << game.getOpponent()->getHandSize() << std::endl;
    std::cout << "==================\n" << std::endl;
}

void showMenu() {
    std::cout << "\n=== 游戏菜单 ===" << std::endl;
    std::cout << "1. 查看手牌" << std::endl;
    std::cout << "2. 召唤怪兽" << std::endl;
    std::cout << "3. 发动魔法" << std::endl;
    std::cout << "4. 设置陷阱" << std::endl;
    std::cout << "5. 进入下一阶段" << std::endl;
    std::cout << "6. 结束回合" << std::endl;
    std::cout << "7. 退出游戏" << std::endl;
    std::cout << "请选择操作: ";
}

void showHand(const Player* player) {
    std::cout << "\n=== " << player->getName() << " 的手牌 ===" << std::endl;
    const auto& hand = player->getHand();
    for (size_t i = 0; i < hand.size(); ++i) {
        std::cout << i + 1 << ". " << hand[i]->getName();
        if (hand[i]->getType() == CardType::MONSTER) {
            auto monster = static_cast<const MonsterCard*>(hand[i].get());
            std::cout << " (攻击: " << monster->getAttack() 
                      << ", 守备: " << monster->getDefense() 
                      << ", 等级: " << monster->getLevel() << ")";
        }
        std::cout << std::endl;
    }
    std::cout << "==================\n" << std::endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);
    std::wcout << L"欢迎来到游戏王卡牌游戏!" << std::endl;
    
    // 创建玩家
    auto player1 = std::make_unique<Player>("玩家1");
    auto player2 = std::make_unique<Player>("玩家2");
    
    // 创建游戏
    Game game(std::move(player1), std::move(player2));
    
    // 开始游戏
    game.startGame();
    
    // 游戏主循环
    while (!game.isGameOver()) {
        printGameState(game);
        showMenu();
        
        int choice;
        std::wcin >> choice;
        
        switch (choice) {
            case 1: {
                showHand(game.getCurrentPlayer());
                break;
            }
            case 2: {
                showHand(game.getCurrentPlayer());
                std::wcout << L"选择要召唤的怪兽 (输入手牌编号): ";
                int handIndex;
                std::wcin >> handIndex;
                
                std::wcout << L"选择场地位置 (1-5): ";
                int fieldPos;
                std::wcin >> fieldPos;
                
                if (game.summonMonster(handIndex - 1, fieldPos - 1)) {
                    std::wcout << L"召唤成功!" << std::endl;
                } else {
                    std::wcout << L"召唤失败!" << std::endl;
                }
                break;
            }
            case 3: {
                showHand(game.getCurrentPlayer());
                std::wcout << L"选择要发动的魔法卡 (输入手牌编号): ";
                int handIndex;
                std::wcin >> handIndex;
                
                if (game.activateSpell(handIndex - 1)) {
                    std::wcout << L"魔法卡发动成功!" << std::endl;
                } else {
                    std::wcout << L"魔法卡发动失败!" << std::endl;
                }
                break;
            }
            case 4: {
                showHand(game.getCurrentPlayer());
                std::wcout << L"选择要设置的陷阱卡 (输入手牌编号): ";
                int handIndex;
                std::wcin >> handIndex;
                
                std::wcout << L"选择魔法陷阱区位置 (1-5): ";
                int trapPos;
                std::wcin >> trapPos;
                
                if (game.setTrap(handIndex - 1, trapPos - 1)) {
                    std::wcout << L"陷阱卡设置成功!" << std::endl;
                } else {
                    std::wcout << L"陷阱卡设置失败!" << std::endl;
                }
                break;
            }
            case 5: {
                game.nextPhase();
                break;
            }
            case 6: {
                game.endTurn();
                break;
            }
            case 7: {
                std::wcout << L"感谢游戏!" << std::endl;
                return 0;
            }
            default: {
                std::wcout << L"无效选择，请重新选择。" << std::endl;
                break;
            }
        }
        
        // 暂停一下让用户看到结果
        std::wcout << L"按回车键继续...";
        std::wcin.ignore();
        std::wcin.get();
    }
    
    std::wcout << L"游戏结束!" << std::endl;
    auto winner = game.getWinner();
    if (winner) {
        std::wcout << L"恭喜 " << winner->getName().c_str() << L" 获胜!" << std::endl;
    }
    
    return 0;
}
