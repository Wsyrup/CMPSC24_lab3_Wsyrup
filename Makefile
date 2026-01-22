# Makefile for lab03-Wsyrup

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

TARGET = testbst
SRCS = intbst.cpp testbst.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = intbst.h

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
