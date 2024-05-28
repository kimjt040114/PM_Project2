CC = g++

# C++ compiler options
# CXXFLAGS = -W -Wall -O3 -I . -std=c++14  # for release
CXXFLAGS = -W -Wall -Og -I . -g -std=c++14  # for debug

# C/C++ preprocessor options
CPPFLAGS =

# Linker options
LDFLAGS = -lncurses

# Directory of source files
SRC_DIR = .

# Directory of object files
OBJ_DIR = .

SRCS = $(filter-out $(wildcard $(SRC_DIR)/curses_test/*), $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp))

OBJS = $(SRCS:.cpp=.o)
OBJECTS = $(OBJS)

OUT = game


.PHONY: all clean

all: game

game: $(OBJECTS)
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o $(OUT) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $< $(LDFLAGS)

curses_test: curses_test/curses_test.cpp utils/Terminal.o
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o curses_test/curses_test curses_test/curses_test.cpp utils/Terminal.o -I curses_test $(LDFLAGS)

clean:
	rm -f game curses_test/curses_test curses_test/curses_test.o $(OBJECTS)
