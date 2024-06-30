# 定义编译器和编译选项
CC = gcc
CFLAGS = -Wall -g

# 定义目标文件和源文件
TARGET = test
SRC = test.c

# 默认目标
all: $(TARGET)

# 编译目标
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# 清理目标
clean:
	rm -f $(TARGET)

# 伪目标（不生成文件，只是为了方便）
.PHONY: all clean

