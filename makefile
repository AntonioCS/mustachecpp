BIN=mustachecpp
BUILD_DIR=./build
OBJ_DIR=./obj
TARGET=$(BUILD_DIR)/$(BIN)
CXXFLAGS=-std=c++14 -Wall -g -Werror
LDFLAGS=
LDLIBS=
CXX=g++
SRC_DIR=./src
SRC=$(shell find $(SRC_DIR) -name '*.cpp')
HEADERS=$(shell find $(SRC_DIR) -name '*.h')
#https://www.gnu.org/software/make/manual/html_node/Text-Functions.html
OBJ=$(addprefix $(OBJ_DIR)/,$(notdir $(patsubst %.cpp, %.o, $(SRC))))
TEST_MAIN=$(OBJ_DIR)/tests-main.o

#http://stackoverflow.com/a/1951111/8715
dir_guard=@mkdir -p $(@D)


.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(dir_guard)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

tests: $(TEST_MAIN) $(OBJ) tests/LexerTest.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/$@ $^ $(LDLIBS)


#To cause recompile when .h files are change
$(OBJ):	$(SRC) 
#$(HEADERS)
	$(dir_guard)
	$(CXX) $(CXXFLAGS) -c $? $(LDLIBS)
#Put all the object files in the correct directory
	@mv *.o $(OBJ_DIR)


$(TEST_MAIN): tests/tests-main.cpp
	$(CXX) $(CXXFLAGS) -c -o $(TEST_MAIN) $^


clean:
	rm -rf $(BUILD_DIR)/* $(OBJ_DIR)/*
