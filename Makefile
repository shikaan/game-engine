CXX = clang++
CFLAGS:= $(CFLAGS) -std=c++11 -fPIC
SMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = src
INC_DIR = include
TEST_DIR = test
LIB_DIR = lib

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

SRC_OBJ_FILES = $(SRC_FILES:.cpp=.o)
OBJ_FILES = $(SRC_FILES:.cpp=.o) $(TEST_FILES:.cpp=.o)

LIB_NAME = dragonfly
LIB_FILE = $(LIB_DIR)/lib$(LIB_NAME).a

TEST_EXECUTABLE = test.out

.PHONY: all clean test game

all: $(TEST_EXECUTABLE) $(LIB_FILE)

%.o: %.cpp
	$(CXX) $(CFLAGS) -I$(INC_DIR) -c -o $@ $<

$(TEST_EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CFLAGS) -I$(INC_DIR) $(SMLFLAGS) -o $@ $(OBJ_FILES)

$(LIB_FILE): $(SRC_OBJ_FILES)
	ar rcs $@ $(SRC_OBJ_FILES)

debug: $(TEST_EXECUTABLE)
	gdb $(TEST_EXECUTABLE)

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

clean:
	rm -f $(OBJ_FILES) $(TEST_EXECUTABLE) $(LIB_FILE)