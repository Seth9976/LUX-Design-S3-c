CC = gcc
CFLAGS = -Wall -Wextra -O2
INCLUDES = -I./src
LIBS = -lm -ljson-c

SRCS = src/main.c src/agent.c src/lux/utils.c src/lux/kit.c
OBJS = $(SRCS:.c=.o)
TARGET = luxbot

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
