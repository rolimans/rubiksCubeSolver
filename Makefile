CC=g++
LD=g++

CFLAGS= -std=c++11 -Wall -Wextra -Werror -pedantic -g -O2
LDLIBS=-lm -lstdc++
DLDFLAGS=-g
LDFLAGS=

VFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes

SRCS    := $(wildcard ./*.cpp)
OBJS    := $(patsubst ./%.cpp,./%.o,$(SRCS))

TARGET=main

./%.o: ./%.cpp ./%.hpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $(TARGET) $(LDLIBS)

debug: $(OBJS)
	$(LD) $(DLDFLAGS) $(OBJS) -o $(TARGET) $(LDLIBS)

clean:
	rm -rf $(OBJS) $(TARGET) vgcore*

run: all
	./$(TARGET)

valgrind: debug
		valgrind $(VFLAGS) ./$(TARGET)

zip:
	zip -r main.zip LICENSE README.md Makefile *.hpp *.cpp