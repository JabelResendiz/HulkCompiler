# Variables
BISON = bison
FLEX = flex
CC = gcc
CFLAGS = -Wall -g
LFLAGS = -lfl

# Archivos fuente
SRC_FILES = parser.y lexer.l ast.c env.c eval.c main.c
OBJ_FILES = parser.tab.c lex.yy.c ast.o env.o eval.o main.o
EXEC = compilador

# Regla principal: construir el ejecutable
all: $(EXEC)

# Regla para generar el ejecutable
$(EXEC): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ_FILES) $(LFLAGS)

# Regla para generar el archivo parser.tab.c con Bison
parser.tab.c parser.tab.h : parser.y
	$(BISON) -d parser.y

# Regla para generar el archivo lex.yy.c con Flex
lex.yy.c: lexer.l
	$(FLEX) lexer.l

# Reglas para compilar los archivos fuente C
ast.o: ast.c
	$(CC) $(CFLAGS) -c ast.c

env.o: env.c 
	$(CC) $(CFLAGS) -c env.c

eval.o: eval.c 
	$(CC) $(CFLAGS) -c eval.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Limpiar los archivos generados
clean:
	rm -f $(EXEC) $(OBJ_FILES) parser.tab.h

# Regla para ejecutar el compilador
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
