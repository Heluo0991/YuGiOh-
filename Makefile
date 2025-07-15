# 简单的 Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude
SRCDIR = src
BUILDDIR = build
BINDIR = bin

# 源文件
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
TARGET = $(BINDIR)/YuGiOh

# 默认目标
all: $(TARGET)

# 创建可执行文件
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@

# 编译源文件
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 创建目录
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# 清理
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# 运行
run: $(TARGET)
	./$(TARGET)

# 标记为虚拟目标
.PHONY: all clean run
