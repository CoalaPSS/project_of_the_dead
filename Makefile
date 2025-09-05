LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
INCLUDES = keyboard.c player.c game.c tiles.c utils.c

game:
	gcc main.c $(INCLUDES) $(LINKER_FLAGS) -o main.exe