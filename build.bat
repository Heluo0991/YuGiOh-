@echo off
echo 正在构建 YuGiOh 卡牌游戏...

REM 创建构建目录
if not exist build mkdir build
if not exist bin mkdir bin

REM 编译所有源文件
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o bin/YuGiOh.exe

if %errorlevel% == 0 (
    echo 构建成功!
    echo 可执行文件位于: bin/YuGiOh.exe
    echo.
    echo 是否立即运行游戏? (Y/N)
    set /p choice=
    if /i "%choice%"=="Y" (
        cd bin
        YuGiOh.exe
    )
) else (
    echo 构建失败!
)

pause
