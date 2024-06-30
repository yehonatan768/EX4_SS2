# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Source files
SRCS = main.cpp Tree.cpp Iterator.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
HDRS = Tree.hpp TreeNode.hpp Iterator.hpp

# Output executable
EXEC = main

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Rule to build object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean
