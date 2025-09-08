LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
INCLUDES = keyboard.c player.c game.c tiles.c utils.c

SRC_DIR = src 
TARGET = bin/main.exe

SRC = $(wildcard src/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(OBJ) $(LINKER_FLAGS) -o $@

%.o: $(SRC_DIR)/%.c
	gcc -c $< -o $@

run: $(TARGET)
	./$(TARGET)


