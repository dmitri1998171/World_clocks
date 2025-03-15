BIN = world_clocks

SRC := $(wildcard src/imgui/*.cpp) 

OBJS := $(SRC:.cpp=.o)
OBJS := $(patsubst src/imgui/%, %, $(OBJS))
OBJS := $(addprefix obj/, $(OBJS))

UNAME_S := $(shell uname -s)

CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -Iinclude/imgui-headers
CXXFLAGS += -g -Wall -Wformat
LIBS =

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Darwin) #APPLE
    ECHO_MESSAGE = "Mac OS X"
    LIBS += -L/System/Library/Frameworks
    LIBS += -framework OpenGL -framework GLUT

    CXXFLAGS += -I/usr/local/include -I/opt/local/include
    CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

obj/%.o: src/imgui/%.cpp 
	$(CXX) -c $< $(CXXFLAGS) -o $(patsubst src/imgui/%, %, $@)

obj/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o obj/main.o

all: $(BIN)
	@echo Build complete for $(ECHO_MESSAGE)

$(BIN): $(OBJS) obj/main.o
	$(CXX) $(CXXFLAGS) $(OBJS) obj/main.o $(LIBS) -o bin/$(BIN)

clean:
	rm -f $(BIN) $(OBJS)
	rmdir bin

.PHONY: all clean