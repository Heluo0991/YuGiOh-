# 构建说明

## 编译器安装

### Windows 用户

#### 选项 1: Visual Studio Community (推荐)
1. 下载 Visual Studio Community (免费): https://visualstudio.microsoft.com/vs/community/
2. 安装时选择 "C++ 桌面开发" 工作负载
3. 打开 "Developer Command Prompt for VS"
4. 运行: `build_vs.bat`

#### 选项 2: MinGW-w64
1. 下载 MinGW-w64: https://www.mingw-w64.org/downloads/
2. 或者使用 MSYS2: https://www.msys2.org/
3. 安装后将 bin 目录添加到 PATH
4. 运行: `build.bat`

#### 选项 3: Clang/LLVM
1. 下载 LLVM: https://releases.llvm.org/download.html
2. 安装后将 bin 目录添加到 PATH
3. 修改 build.bat 中的 g++ 为 clang++

### Linux 用户

#### Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential g++ cmake
```

#### CentOS/RHEL
```bash
sudo yum install gcc-c++ make cmake
```

#### Arch Linux
```bash
sudo pacman -S base-devel cmake
```

### Mac 用户

#### 使用 Homebrew
```bash
brew install gcc cmake
```

#### 使用 Xcode
```bash
xcode-select --install
```

## 构建命令

### 使用 CMake (推荐)
```bash
mkdir build
cd build
cmake ..
make                    # Linux/Mac
cmake --build .         # Windows
```

### 使用 Makefile
```bash
make
```

### 手动编译
```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o bin/YuGiOh
```

## 运行游戏

### Windows
```cmd
bin\YuGiOh.exe
```

### Linux/Mac
```bash
./bin/YuGiOh
```

## 编译测试

### 编译并运行测试
```bash
g++ -std=c++17 -Iinclude tests/test_main.cpp src/Card.cpp src/Deck.cpp src/Player.cpp src/CardDatabase.cpp -o bin/test
./bin/test
```

## 故障排除

### 常见错误

1. **命令未找到**: 确保编译器在 PATH 中
2. **C++17 不支持**: 使用较新版本的编译器
3. **链接错误**: 确保所有源文件都被包含
4. **头文件错误**: 检查 include 路径

### 获得帮助

如果遇到问题，请：
1. 检查编译器版本: `g++ --version`
2. 验证 C++17 支持
3. 查看错误信息
4. 提交 Issue 到 GitHub
