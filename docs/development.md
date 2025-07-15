# 开发指南

## 环境要求
- C++17 兼容的编译器 (GCC 7+, Clang 6+, MSVC 2019+)
- CMake 3.10+ (可选)
- Git

## 构建方法

### 方法1: 使用 CMake (推荐)
```bash
mkdir build
cd build
cmake ..
make
```

### 方法2: 使用 Makefile
```bash
make
```

### 方法3: 使用 Windows 批处理文件
```cmd
build.bat
```

### 方法4: 手动编译
```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o bin/YuGiOh
```

## 开发规范

### 代码风格
- 使用 4 空格缩进
- 类名使用 PascalCase
- 函数名使用 camelCase
- 变量名使用 camelCase，私有成员变量以 `_` 结尾
- 常量使用 UPPER_CASE

### 文件组织
- 头文件放在 `include/` 目录
- 源文件放在 `src/` 目录
- 测试文件放在 `tests/` 目录

### 提交规范
- 使用清晰的提交消息
- 每个提交只做一件事
- 提交前确保代码能够编译通过

## 添加新卡片

1. 在 `CardDatabase.cpp` 的 `initializeDatabase()` 函数中添加新卡片
2. 如果需要特殊效果，可以创建新的卡片子类
3. 更新相关的枚举类型（如 MonsterType, Attribute）

## 测试
```bash
# 运行游戏
./bin/YuGiOh

# 或者使用 make
make run
```

## 调试
- 使用 GDB 或 Visual Studio 调试器
- 编译时添加 `-g` 标志获取调试信息
- 使用 Valgrind 检查内存泄漏 (Linux/Mac)

## 常见问题

### 编译错误
- 确保编译器支持 C++17
- 检查包含路径是否正确
- 确保所有依赖项都已安装

### 运行时错误
- 检查卡片数据库是否正确初始化
- 确保输入验证逻辑正确
- 检查指针和内存管理
