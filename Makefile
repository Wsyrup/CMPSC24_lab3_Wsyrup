# Makefile for lab03-Wsyrup

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

TARGET = testbst
SRCS = intbst.cpp testbst.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = intbst.h

.PHONY: all clean run tests run_test_intbst

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) test_intbst test_intbst.o

run: $(TARGET)
	./$(TARGET)

tests: $(TARGET)
	printf "0\n" | ./$(TARGET)

# build and run the small test program test_intbst.cpp
test_intbst: intbst.o test_intbst.o
	$(CXX) $(CXXFLAGS) -o $@ intbst.o test_intbst.o

test_intbst.o: test_intbst.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run_test_intbst: test_intbst
	./test_intbst
