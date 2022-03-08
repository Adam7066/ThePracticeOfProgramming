CC = g++
CFLAGS = -O2 -Wall -Wextra -std=c++14
OBJS = main.o maze.o robot.o
EXE = main

all: $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CFLAGS)

%.o: %.c

.PHONY: clean
clean:
	${RM} -r $(OBJS) $(EXE)