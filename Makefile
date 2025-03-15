BIN := main
SRC := main.cpp
CC := g++
LIB_PATH := -L/System/Library/Frameworks
LDFLAGS := -framework GLUT -framework OpenGL -framework Cocoa
CFLAGS := -Wno-deprecated-declarations

all:
	clear && $(CC) $(SRC) $(LIB_PATH) $(LDFLAGS) $(CFLAGS) -o $(BIN)
	
clean:
	rm -rf $(BIN)