# YuGiOh 卡牌游戏

一个基于 C++ 的游戏王卡牌游戏模拟器，实现了核心的卡牌游戏机制。

## 功能特点

- 🎴 完整的卡牌系统（怪兽卡、魔法卡、陷阱卡）
- 👥 双人对战模式
- 🎲 卡组管理和洗牌系统
- ⚔️ 回合制游戏流程
- 🎯 基本的游戏规则实现
- 💾 卡片数据库系统

## 项目结构

```
YuGiOh-/
├── src/                    # 源代码文件
├── include/                # 头文件
├── build/                  # 构建输出目录
├── bin/                    # 可执行文件目录
├── tests/                  # 测试文件
├── docs/                   # 文档
├── CMakeLists.txt          # CMake 构建配置
├── Makefile               # Make 构建配置
└── build.bat              # Windows 构建脚本
```

## 快速开始

### 环境要求
- C++17 兼容的编译器
- CMake 3.10+ (可选)
- Git

### 构建和运行

#### Windows 用户
```cmd
# 使用批处理文件构建
build.bat

# 或者手动构建
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o bin/YuGiOh.exe
```

#### Linux/Mac 用户
```bash
# 使用 Makefile
make
make run

# 或者使用 CMake
mkdir build && cd build
cmake ..
make
./bin/YuGiOh
```

## 游戏玩法

1. 游戏开始时，每位玩家抽取5张起始手牌
2. 每回合包含以下阶段：
   - 抽卡阶段：抽取一张卡片
   - 主要阶段1：可以召唤怪兽、发动魔法
   - 战斗阶段：进行战斗
   - 主要阶段2：再次进行召唤等操作
   - 结束阶段：回合结束

3. 游戏目标：将对手的生命值降至0

## 核心类

- **Card**: 卡片基类，包含 MonsterCard、SpellCard、TrapCard
- **Player**: 玩家类，管理生命值、手牌、场地
- **Deck**: 卡组类，管理卡片抽取和洗牌
- **Game**: 游戏类，控制游戏流程和规则
- **CardDatabase**: 卡片数据库，管理所有卡片信息

## 开发

详细的开发指南请参考 [docs/development.md](docs/development.md)

### 运行测试
```bash
g++ -std=c++17 -Iinclude tests/test_main.cpp src/Card.cpp src/Deck.cpp src/Player.cpp src/CardDatabase.cpp -o bin/test
./bin/test
```

## 贡献

欢迎提交 Pull Request 来改进这个项目！

## 许可证

MIT License
