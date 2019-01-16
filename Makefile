CPP		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra -O3

ROOT	:= Pong1
BINDIR	:= $(ROOT)/bin
LIBDIR	:= $(ROOT)/lib
INCDIR	:= $(ROOT)/include
SRCDIR	:= $(ROOT)/src
OBJDIR	:= $(ROOT)/obj

SRC		= $(notdir $(wildcard $(SRCDIR)/*.cpp ))
OBJ		:= $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(SRC)))
LIBRARIES	:= -lm -lSDL2main

ifeq ($(OS),Windows_NT)
	EXECUTABLE	:= main.exe
	SDL_INCLUDE	:= D:/Programacion/SDL/SDL2-devel-2.0.8-VC/SDL2-2.0.8/include
	SDL_LIB		:= D:/Programacion/SDL/SDL2-devel-2.0.8-VC/SDL2-2.0.8/lib/x64
	libsdl		:= $(SDL_LIB)/SDL2.dll
else
	EXECUTABLE	:= main
	SDL_INCLUDE	:= /usr/local/include/SDL2
	SDL_LIB		:= /usr/local/Cellar/sdl2/2.0.8/lib
	libsdl		:= $(SDL_LIB)/libSDL2.so
endif

.PHONY : clean veryclean directories link build run

build: directories link

run: directories link
	$(BINDIR)/$(EXECUTABLE)

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)
	@mkdir -p $(LIBDIR)

clean:
	$(RM) -r $(OBJDIR)

veryclean: clean
	$(RM) -r $(BINDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CPP) $(C_FLAGS) -I$(INCDIR) -I$(SDL_INCLUDE) -L$(SDL_LIB) -c -o $@ $<

link: $(OBJ)
	$(CPP) $(C_FLAGS) -I$(INCDIR) -I$(SDL_INCLUDE) -L$(SDL_LIB) $^ -o $(BINDIR)/$(EXECUTABLE) $(LIBRARIES) -lSDL2
	@cp $(libsdl) $(BINDIR)/