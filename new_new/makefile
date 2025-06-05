# Variables
BISON = bison
FLEX = flex
CC = g++
CFLAGS = -Wall -g
LFLAGS = -lfl

# Archivos fuente
SRC_FILES = parser.ypp lexer.lpp ast.cpp main.cpp 
OBJ_FILES = parser.tab.cpp lex.yy.cpp ast.o  main.o
EXEC = compilador

# Regla principal: construir el ejecutable
all: $(EXEC)

# Regla para generar el ejecutable
$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ_FILES) $(LFLAGS)

# Regla para generar el archivo parser.tab.c con Bison
parser.tab.cpp parser.tab.h : parser.ypp
	$(BISON) -d parser.ypp

# Regla para generar el archivo lex.yy.c con Flex
lex.yy.cpp: lexer.lpp
	$(FLEX) lexer.lpp

# Reglas para compilar los archivos fuente C
ast.o: ast.cpp
	$(CC) $(CFLAGS) -c ast.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

# Limpiar los archivos generados
clean:
	rm -f $(EXEC) $(OBJ_FILES) parser.tab.h

# Regla para ejecutar el compilador
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
