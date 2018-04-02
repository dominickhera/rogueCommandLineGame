CFLAGS = -std=c99 -Wall
EXE = rogue

all: $(EXE)

$(EXE): main.o parse.o draw.o BIN OBJ
		gcc main.o draw.o parse.o -lncurses -o ./bin/$(EXE)

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;


main.o: ./src/main.c
	gcc -c $(CFLAGS) ./src/main.c -Iinclude

draw.o: ./src/draw.c
	gcc -c $(CFLAGS) ./src/draw.c -Iinclude

parse.o: ./src/parse.c
	gcc -c $(CFLAGS) ./src/parse.c -Iinclude

clean:
	rm *.o
