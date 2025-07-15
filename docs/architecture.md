# 项目架构文档

## 项目概述
这是一个基于 C++ 的卡牌游戏项目，模拟游戏王卡牌游戏的核心机制。

## 项目结构
```
YuGiOh-/
├── src/                    # 源代码文件
│   ├── main.cpp           # 主程序入口
│   ├── Card.cpp           # 卡片类实现
│   ├── Deck.cpp           # 卡组类实现
│   ├── Player.cpp         # 玩家类实现
│   ├── Game.cpp           # 游戏逻辑实现
│   └── CardDatabase.cpp   # 卡片数据库实现
├── include/                # 头文件
│   ├── Card.h             # 卡片类声明
│   ├── Deck.h             # 卡组类声明
│   ├── Player.h           # 玩家类声明
│   ├── Game.h             # 游戏类声明
│   └── CardDatabase.h     # 卡片数据库声明
├── build/                  # 构建输出目录
├── bin/                    # 可执行文件目录
├── tests/                  # 测试文件
├── assets/                 # 游戏资源
├── docs/                   # 文档
├── CMakeLists.txt          # CMake 构建配置
├── Makefile               # Make 构建配置
├── build.bat              # Windows 构建脚本
└── README.md              # 项目说明
```

## 核心类设计

### Card 类层次结构
- `Card` (抽象基类)
  - `MonsterCard` (怪兽卡)
  - `SpellCard` (魔法卡)
  - `TrapCard` (陷阱卡)

### 游戏组件
- `Player` - 玩家类，管理生命值、手牌、场地
- `Deck` - 卡组类，管理卡片抽取和洗牌
- `Game` - 游戏类，控制游戏流程和规则
- `CardDatabase` - 卡片数据库，管理所有卡片信息

## 游戏流程
1. 游戏初始化
2. 玩家抽取起始手牌
3. 回合循环：
   - 抽卡阶段
   - 主要阶段1
   - 战斗阶段
   - 主要阶段2
   - 结束阶段

## 扩展点
- 卡片效果系统
- 更复杂的战斗机制
- 图形界面
- 网络对战
- AI 玩家
- 卡片动画效果
