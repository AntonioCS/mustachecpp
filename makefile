BIN=mustachecpp
BUILD_DIR=./build
OBJ_DIR=./obj
TARGET=$(BUILD_DIR)/$(BIN)
CFLAGS=-std=c++14 -Wall -g -Werror
LDFLAGS=
LDLIBS=
CC=g++
SRC_DIR=./src
SRC=$(shell find $(SRC_DIR) -name '*.cpp')
HEADERS=$(shell find $(SRC_DIR) -name '*.h')
#https://www.gnu.org/software/make/manual/html_node/Text-Functions.html
OBJ=$(addprefix $(OBJ_DIR)/,$(notdir $(patsubst %.cpp, %.o, $(SRC))))

#http://stackoverflow.com/a/1951111/8715
dir_guard=@mkdir -p $(@D)

.PHONY: clean

all: $(TARGET)

test_lexer: src/Lexer.cpp tests/LexerTest.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(TARGET): $(OBJ)
	$(dir_guard)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

#To cause recompile when .h files are change
$(OBJ):	$(SRC) $(HEADERS)
	$(dir_guard)
	$(CC) $(CFLAGS) -c $? $(LDLIBS)
#Put all the object files in the correct directory
	@mv *.o $(OBJ_DIR)

clean:
	rm -rf $(TARGET) $(OBJ_DIR)/*
