# Definir códigos de color
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
CYAN := \033[36m
RESET := \033[0m

CC = clang
CFLAGS = -Wall -g -I. $(shell llvm-config --cflags) -O0
LDFLAGS = $(shell llvm-config --ldflags --libs core) -lm
LEXFLAGS = -w
YFLAGS = -d -y -v
LEX = flex
YACC = bison

SRC_DIR = .
AST_DIR = $(SRC_DIR)/ast
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
SEMANTIC_DIR = $(SRC_DIR)/semantic_check
TYPE_DIR = $(SRC_DIR)/type
VISITOR_DIR = $(SRC_DIR)/visitor
SCOPE_DIR = $(SRC_DIR)/scope
UTILS_DIR = $(SRC_DIR)/utils
CODEGEN_DIR = $(SRC_DIR)/codegen

BUILD_DIR = $(SRC_DIR)/build
EXEC = $(BUILD_DIR)/HULK

.PHONY: all compile execute clean debug

all: compile

compile: $(EXEC)
	@$(SRC_DIR)/$(EXEC)
	
# Creamos el directorio build si no existe
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# El directorio build se pone como dependencia order-only (con el símbolo |)
$(EXEC): $(LEXER_DIR)/lex.yy.o $(PARSER_DIR)/y.tab.o $(AST_DIR)/ast.o $(SRC_DIR)/main.o \
	$(VISITOR_DIR)/llvm_visitor.o  $(SCOPE_DIR)/llvm_scope.o $(UTILS_DIR)/utils.o \
    $(SEMANTIC_DIR)/unification.o $(SEMANTIC_DIR)/type_op_checking.o $(SEMANTIC_DIR)/type_checking.o \
	$(SEMANTIC_DIR)/cond_loop_checking.o $(SEMANTIC_DIR)/function_checking.o $(SEMANTIC_DIR)/variable_checking.o \
	$(SEMANTIC_DIR)/basic_checking.o $(SEMANTIC_DIR)/semantic.o $(SCOPE_DIR)/scope.o $(SCOPE_DIR)/context.o \
	$(VISITOR_DIR)/visitor.o \
	$(CODEGEN_DIR)/basic.o $(CODEGEN_DIR)/codegen.o $(CODEGEN_DIR)/control.o $(CODEGEN_DIR)/function.o $(CODEGEN_DIR)/getter.o \
	$(CODEGEN_DIR)/init_codegen.o $(CODEGEN_DIR)/instance.o $(CODEGEN_DIR)/op.o $(CODEGEN_DIR)/visitor_llvm.o $(CODEGEN_DIR)/types.o\
	$(CODEGEN_DIR)/setter.o $(CODEGEN_DIR)/cast.o\
	$(TYPE_DIR)/type.o | $(BUILD_DIR)

	@printf "$(CYAN)🔗 Getting ready...$(RESET)\n";
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@printf "$(CYAN)🔄 Compiling...$(RESET)\n";


# Reglas para generar el parser y lexer
$(PARSER_DIR)/y.tab.c $(PARSER_DIR)/y.tab.h: $(PARSER_DIR)/parser.y
	@printf "$(CYAN)🔄 Generating parser...$(RESET)\n";
	@cd $(PARSER_DIR) && $(YACC) $(YFLAGS) parser.y || (echo "Bison failed to process parser.y"; exit 1)
	@mv $(PARSER_DIR)/y.tab.c $(PARSER_DIR)/y.tab.c 2>/dev/null || true
	@mv $(PARSER_DIR)/y.tab.h $(PARSER_DIR)/y.tab.h 2>/dev/null || true
	@mv $(PARSER_DIR)/y.output $(PARSER_DIR)/y.output 2>/dev/null || true

$(LEXER_DIR)/lex.yy.c: $(LEXER_DIR)/lexer.l $(PARSER_DIR)/y.tab.h
	@printf "$(CYAN)🔄 Generating lexer...$(RESET)\n";
	@cd $(LEXER_DIR) && $(LEX) $(LEXFLAGS) lexer.l || (echo "Flex failed to process lexer.l"; exit 1)
	@mv $(LEXER_DIR)/lex.yy.c $(LEXER_DIR)/lex.yy.c 2>/dev/null || true

$(LEXER_DIR)/lex.yy.o: $(LEXER_DIR)/lex.yy.c
	@printf "$(CYAN)🔨 Compiling lex.yy.c...$(RESET)\n";
	@$(CC) $(CFLAGS) -c $< -o $@

$(PARSER_DIR)/y.tab.o: $(PARSER_DIR)/y.tab.c
	@printf "$(CYAN)🔨 Compiling y.tab.c...$(RESET)\n";
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/codegen.o: $(CODEGEN_DIR)/codegen.c $(CODEGEN_DIR)/codegen.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/types.o: $(CODEGEN_DIR)/types.c $(CODEGEN_DIR)/types.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/init_codegen.o: $(CODEGEN_DIR)/init_codegen.c $(CODEGEN_DIR)/init_codegen.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/visitor_llvm.o: $(CODEGEN_DIR)/visitor_llvm.c $(CODEGEN_DIR)/visitor_llvm.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/basic.o: $(CODEGEN_DIR)/basic.c 
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/control.o: $(CODEGEN_DIR)/control.c 
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/function.o: $(CODEGEN_DIR)/function.c 
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/getter.o: $(CODEGEN_DIR)/getter.c 
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/instance.o: $(CODEGEN_DIR)/instance.c 
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/op.o: $(CODEGEN_DIR)/op.c 
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/setter.o: $(CODEGEN_DIR)/setter.c 
	@$(CC) $(CFLAGS) -c $< -o $@

$(CODEGEN_DIR)/cast.o: $(CODEGEN_DIR)/cast.c 
	@$(CC) $(CFLAGS) -c $< -o $@

# AST
$(AST_DIR)/ast.o: $(AST_DIR)/ast.c $(AST_DIR)/ast.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(UTILS_DIR)/utils.o: $(UTILS_DIR)/utils.c $(UTILS_DIR)/utils.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(SEMANTIC_DIR)/semantic.o: $(SEMANTIC_DIR)/semantic.c $(SEMANTIC_DIR)/semantic.h $(AST_DIR)/ast.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(SCOPE_DIR)/scope.o: $(SCOPE_DIR)/scope.c $(SCOPE_DIR)/scope.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(SCOPE_DIR)/context.o: $(SCOPE_DIR)/context.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(VISITOR_DIR)/visitor.o: $(VISITOR_DIR)/visitor.c $(VISITOR_DIR)/visitor.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(TYPE_DIR)/type.o: $(TYPE_DIR)/type.c $(TYPE_DIR)/type.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(SEMANTIC_DIR)/basic_checking.o: $(SEMANTIC_DIR)/basic_checking.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(SEMANTIC_DIR)/variable_checking.o: $(SEMANTIC_DIR)/variable_checking.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(SEMANTIC_DIR)/function_checking.o: $(SEMANTIC_DIR)/function_checking.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(SEMANTIC_DIR)/unification.o: $(SEMANTIC_DIR)/unification.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(SEMANTIC_DIR)/cond_loop_checking.o: $(SEMANTIC_DIR)/cond_loop_checking.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(SEMANTIC_DIR)/type_checking.o: $(SEMANTIC_DIR)/type_checking.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(SEMANTIC_DIR)/type_op_checking.o: $(SEMANTIC_DIR)/type_op_checking.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Regla genérica para compilar cualquier archivo .c en .o
%.o: %.c
	@printf "$(CYAN)🔨 Compiling $<...$(RESET)\n";
	@$(CC) $(CFLAGS) -c $< -o $@

# Objetivo para compilar y ejecutar output.ll, si existe
execute: compile
	@if [ -s $(BUILD_DIR)/output.ll ]; then \
		printf "$(CYAN)🔄 Compiling output.ll...$(RESET)\n"; \
		clang $(BUILD_DIR)/output.ll -o $(BUILD_DIR)/program -lm || { printf "$(RED)❌ clang failed when compiling output.ll$(RESET)\n"; exit 0; }; \
		printf "\n$(BLUE)------------💻 Executing compiled program------------$(RESET)\n"; \
		$(BUILD_DIR)/program; \
	else \
		printf "$(YELLOW)⚠️  output.ll does not exist or is empty - nothing to be executed$(RESET)\n"; \
	fi

# Debugging con gdb
debug:
	@gdb $(BUILD_DIR)/HULK

# Regla para limpiar todos los archivos generados
clean:
	@echo "$(CYAN)🧹 Cleaning project...$(RESET)"
	@rm -rf $(BUILD_DIR)
	@rm -f *.o $(EXEC) y.tab.* lex.yy.c *.output y.* output.ll program
	@rm -f $(AST_DIR)/*.o
	@rm -f $(SEMANTIC_DIR)/*.o
	@rm -f $(VISITOR_DIR)/*.o
	@rm -f $(TYPE_DIR)/*.o
	@rm -f $(SCOPE_DIR)/*.o
	@rm -f $(UTILS_DIR)/*.o
	@rm -f $(CODEGEN_DIR)/*.o
	@rm -f $(LEXER_DIR)/*.o $(LEXER_DIR)/lex.yy.c
	@rm -f $(PARSER_DIR)/*.o $(PARSER_DIR)/y.tab.c $(PARSER_DIR)/y.tab.h $(PARSER_DIR)/y.output