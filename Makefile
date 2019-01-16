#CC		:= g++
# for each .cpp file we will create the .o file, an object file
# the object files are linked together later
CPP		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra

ROOT	:= Pong1
BINDIR	:= $(ROOT)/bin
LIBDIR	:= $(ROOT)/lib
INCDIR	:= $(ROOT)/include
SRCDIR	:= $(ROOT)/src
OBJDIR	:= $(ROOT)/obj

SRC		= $(notdir $(wildcard Pong1/src/*.cpp ))
OBJ		:= $(addprefix Pong1/obj/, $(patsubst %.cpp, %.o, $(SRC)))
LIBRARIES	:= -lm -lSDL2main
# https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
# read this lib values from somewhere else maybe from c_cpp_properties.json
# read what is a common practice for that ???
ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
SDL_INCLUDE	:= D:/Programacion/SDL/SDL2-devel-2.0.8-VC/SDL2-2.0.8/include
SDL_LIB		:= D:/Programacion/SDL/SDL2-devel-2.0.8-VC/SDL2-2.0.8/lib/x64
libsdl		:= $(SDL_LIB)/SDL2.dll
#LIBRARIES	:= $(LIBRARIES)
else
EXECUTABLE	:= main
SDL_INCLUDE	:= /usr/local/include/SDL2
SDL_LIB		:= /usr/local/Cellar/sdl2/2.0.8/lib
libsdl		:= $(SDL_LIB)/libSDL2.so
endif
.PHONY : clean veryclean directories link all
directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)
	@mkdir -p $(LIBDIR)

clean:
	$(RM) -r $(OBJDIR)

veryclean: clean
	$(RM) -r $(BINDIR)

Pong1/obj/%.o : Pong1/src/%.cpp
	$(CPP) $(C_FLAGS) -I$(INCDIR) -I$(SDL_INCLUDE) -L$(SDL_LIB) -c -o $@ $<

link: $(OBJ)
	$(CPP) $(C_FLAGS) -I$(INCDIR) -I$(SDL_INCLUDE) -L$(SDL_LIB) $^ -o $(BINDIR)/$(EXECUTABLE) $(LIBRARIES) -lSDL2
	@cp $(libsdl) $(BINDIR)/

all: directories link

	

#$(BIN)/$(EXECUTABLE): $(SRC)/*
	#$(CPP) $(C_FLAGS) -I$(INCLUDE) -I$(SDL_INCLUDE) -L$(SDL_LIB)  $^ -o $@ $(LIBRARIES) -lSDL2

#run: all # all not defined
	#./$(BIN)/$(EXECUTABLE)
