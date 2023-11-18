CXX := g++
CC := gcc
CFLAGS := -Wall -Wextra -std=c99
CXXFLAGS := -Wall -Wextra -std=c++11

# Source files
C_SRCS := main.c
CPP_SRCS := example.cpp example_wrapper.cpp

# Object files
C_OBJS := $(C_SRCS:.c=.o)
CPP_OBJS := $(CPP_SRCS:.cpp=.o)

# Executable
TARGET := example

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(C_OBJS) $(CPP_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(C_OBJS) $(CPP_OBJS)
