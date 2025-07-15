@echo off
echo 正在使用 Visual Studio 构建 YuGiOh 卡牌游戏...

REM 创建构建目录
if not exist build mkdir build
if not exist bin mkdir bin

REM 尝试使用 cl.exe (Visual Studio 编译器)
cl /EHsc /std:c++17 /I include src\*.cpp /Fe:bin\YuGiOh.exe

if %errorlevel% == 0 (
    echo 构建成功!
    echo 可执行文件位于: bin\YuGiOh.exe
    echo.
    echo 是否立即运行游戏? (Y/N)
    set /p choice=
    if /i "%choice%"=="Y" (
        cd bin
        YuGiOh.exe
    )
) else (
    echo 构建失败! 请确保已安装 Visual Studio 或 MinGW
    echo.
    echo 或者尝试手动安装编译器:
    echo 1. 安装 Visual Studio Community (免费)
    echo 2. 安装 MinGW-w64
    echo 3. 安装 Clang/LLVM
)

pause
