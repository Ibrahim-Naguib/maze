
SDL_CFLAGS := $(shell pkg-config --cflags sdl2)
SDL_LIBS := $(shell pkg-config --libs sdl2)
INCLUDES := -I/usr/include -I./src

CFLAGS := $(SDL_CFLAGS) $(INCLUDES) -Wall -Werror -Wextra -ggdb
LIBS := $(SDL_LIBS) -lm

FILES := $(shell find src/ -name *.c)

OUT_BIN := Maze

all: compile run

compile:
	gcc $(FILES) $(CFLAGS) $(LIBS) -o $(OUT_DIR)$(OUT_BIN)

run:
	./$(OUT_BIN)
