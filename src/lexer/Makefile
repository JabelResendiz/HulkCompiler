
CXX = g++

SRC = main.cpp scanner.cpp
OBJ = main.o scanner.o

TARGET = lexer

CXXFLAGS = -std=c++17

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

main.o: main.cpp scanner.h token.h tokenType.h
	$(CXX) $(CXXFLAGS) -c main.cpp

scanner.o: scanner.cpp scanner.h token.h tokenType.h
	$(CXX) $(CXXFLAGS) -c scanner.cpp

run:
	./$(TARGET)

runwin:
	$(TARGET).exe


