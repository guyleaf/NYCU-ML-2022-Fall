standard = c++14
SUB_FOLDERS = algebra
TARGET = main.out

# folders
SRC_FOLDER = src
OBJ_FOLDER = obj

# compiler
CXX = g++

# flags
DEBUG_LEVEL = -g
CXXFLAGS = -std=$(standard) -Wall -Wextra -Wno-deprecated-declarations -pedantic-errors -m64

# others
SRCS = $(wildcard $(SRC_FOLDER)/*.cpp $(foreach fd, $(SUB_FOLDERS), $(SRC_FOLDER)/$(fd)/*.cpp))
OBJS = $(addprefix $(OBJ_FOLDER)/, $(SRCS:$(SRC_FOLDER)/%.cpp=%.o))

all: CXXFLAGS += -Werror
all: $(TARGET)

debug: CXXFLAGS += $(DEBUG_LEVEL) -fsanitize=address -fdiagnostics-color=always
debug: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	mkdir -p $(@D)
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJ_FOLDER)