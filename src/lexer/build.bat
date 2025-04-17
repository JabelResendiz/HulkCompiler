@echo off
set CXX=g++
set SRC=main.cpp scanner.cpp
set OBJ=main.o scanner.o
set TARGET=lexer
set CXXFLAGS=-std=c++17

echo Compiling main.cpp...
%CXX% %CXXFLAGS% -c main.cpp -o main.o

echo Compiling scanner.cpp...
%CXX% %CXXFLAGS% -c scanner.cpp -o scanner.o

echo Linking...
%CXX% %OBJ% -o %TARGET%.exe

echo Done.
echo To run: %TARGET%.exe
