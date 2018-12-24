CC		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra

ROOT	:= Pong1
BIN		:= ${ROOT}/bin
SRC		:= ${ROOT}/src
INCLUDE	:= ${ROOT}/include

LIBRARIES	:= 

# read this lib values from somewhere else maybe from c_cpp_properties.json
# read what is a common practice for that ???
ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
SDL_INCLUDE	:= D:/Programacion/SDL/SDL2-devel-2.0.8-VC/SDL2-2.0.8/include
SDL_LIB		:= #specify
else
EXECUTABLE	:= main
SDL_INCLUDE	:= /usr/local/include/SDL2
SDL_LIB		:= /usr/local/Cellar/sdl2/2.0.8/lib
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*
	$(CC) $(C_FLAGS) -I$(INCLUDE) -I$(SDL_INCLUDE) -L$(SDL_LIB) -lSDL2 $^ -o $@ $(LIBRARIES)