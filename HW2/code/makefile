CC = g++
CFLAGS = -O2 -Wall -Wextra -std=c++14
OBJS = main.o kitchen.o customer.o player.o maker.o tool.o
EXE = main

all: $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CFLAGS)

%.o: %.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)

.PHONY: clean
clean:
	${RM} -r $(EXE) $(OBJS)