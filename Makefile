# 检测操作系统
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    # Windows下使用MSYS2的路径
    JSON_C_PATH := /mingw64
    EXE_EXT := .exe
    RM_CMD := del /F /Q
else
    DETECTED_OS := $(shell uname -s)
    JSON_C_PATH := /usr/local
    EXE_EXT :=
    RM_CMD := rm -f
endif

CC = gcc
CFLAGS = -Wall -Wextra -O2
INCLUDES = -I./src -I$(JSON_C_PATH)/include
LIBS = -L$(JSON_C_PATH)/lib -ljson-c -lm

# 源文件和目标文件
SRCS = src/main.c src/agent.c src/lux/utils.c src/lux/kit.c
OBJS = $(SRCS:.c=.o)
TARGET = luxbot$(EXE_EXT)

# 默认目标
.PHONY: all clean run
all: $(TARGET)

# 链接
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# 编译
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 清理
clean:
	-$(RM_CMD) $(subst /,\,$(OBJS)) $(TARGET)

# 运行目标(用于测试)
run: $(TARGET)
	./$(TARGET)
