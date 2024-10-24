# 定义编译器
CXX = g++
# 编译选项，添加 -I 指定头文件所在的 include 目录
CXXFLAGS = -std=c++11 -Wall -Iinclude
# 目标文件目录
BINDIR = bin
# 对象文件目录
OBJDIR = obj
# 源文件目录
SRCDIR = src
# 源文件
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/game2048.cpp
# 生成的对象文件，将 src/ 中的源文件映射到 obj/ 中的对象文件
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
# 目标文件
TARGET = $(BINDIR)/game2048

# 默认目标
all: $(TARGET)

# 创建目标文件目录并链接生成可执行文件
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 编译源文件为对象文件，存放在 obj 目录
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp include/game2048.h
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# 运行游戏
run: $(TARGET)
	./$(TARGET)

# 测试代码
test:
	@echo "No tests defined"

# 依赖生成的对象文件和可执行文件
.PHONY: all clean run test
