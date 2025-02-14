CC=gcc
INC=-I./include/ -I/usr/include -I/usr/local/include/
LIB=-lcsfml-system -lcsfml-window -lcsfml-graphics -lm

CFLAGS=-ansi -pedantic

SRC=main.c int2.c cell.c
OBJ=main.o int2.o cell.o

BIN=game-of-life

all: release

release: $(BIN)
release: CFLAGS += -O2

debug: $(BIN)
debug: CFLAGS += -Og -g3 -Wall -Werror

run: release
	clear
	./$(BIN)

gdb: debug
	clear
	gdb ./$(BIN) --tui

valgrind: debug
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --gen-suppressions=all ./$(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $(BIN) $(LIB)
	rm -rf *.o
	@echo "COMPILED SUCCESSFULLY"

%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ $(INC)

clean:
	rm -rf $(BIN) *.o src/*.orig include/*.orig
	clear

format:
	astyle -A3 -s -f -xg -k3 -xj -v src/*.c
	astyle -A3 -s -f -xg -k3 -xj -v include/*.h
