# 编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall

# 源代码和头文件目录
SRCDIR = src
LIBDIR = include

# 目标文件和可执行文件目录
BINDIR = bin

# MySQL Connector/C++库的路径
MYSQLCPPCONN_LIB = /usr/lib/x86_64-linux-gnu/libmysqlcppconn.so

# 目标文件的生成规则
# 将每个.cpp文件编译为一个.o文件
# 目标文件存放在$(BINDIR)目录中
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

# 可执行文件的生成规则
# 依赖于所有目标文件和MySQL Connector/C++库
# 可执行文件存放在$(BINDIR)目录中
TARGET = $(BINDIR)/main
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(MYSQLCPPCONN_LIB) -o $(TARGET)

# 目标文件的生成规则
# 将每个.cpp文件编译为一个.o文件
# 目标文件存放在$(BINDIR)目录中
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(LIBDIR) -c $< -o $@

# 清理生成的目标文件和可执行文件
clean:
	rm -f $(BINDIR)/*.o $(TARGET)

