all: parser

parser: parser.tab.o lex.yy.o
	g++ -o parser parser.tab.o lex.yy.o -std=c++11

parser.tab.o: parser.tab.c
	g++ -c parser.tab.c -std=c++11

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c -std=c++11

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l
	flex lexer.l

clean:
	rm -f parser *.o parser.tab.* lex.yy.c
