CC=gcc
CFLAGS=-lSDL_image `sdl-config --cflags --libs`
LDFLAGS=-lSDL_image `sdl-config --libs `
EXEC=stetrisme
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

stetrisme: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
