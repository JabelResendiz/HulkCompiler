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

BUILD_DIR = build
EXEC = $(BUILD_DIR)/HULK

SRC_DIR = .
AST_DIR = ast
CHECK_DIR = check
LLVM_DIR = llvm
LEXER_DIR = lexer
PARSER_DIR = parser
LLVM_SCOPE_DIR = llvm_scope
VISITOR_DIR = visitor
SCOPE_DIR = scope
UTILS_DIR = utils

.PHONY: all compile execute clean debug

all: compile

compile: $(EXEC)
	@./$(EXEC)
	
# Creamos el directorio build si no existe
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# El directorio build se pone como dependencia order-only (con el símbolo |)
$(EXEC): lex.yy.o y.tab.o $(AST_DIR)/ast.o $(AST_DIR)/keyword.o $(SRC_DIR)/main.o \
    $(LLVM_DIR)/init_codegen.o $(LLVM_DIR)/visitor_llvm.o \
	$(LLVM_DIR)/codegen.o $(LLVM_SCOPE_DIR)/llvm_scope.o  $(LLVM_DIR)/visitor_llvm.o\
	$(LLVM_DIR)/llvm_op.o $(LLVM_DIR)/visitor_llvm.o \
    $(CHECK_DIR)/typecheck.o  $(CHECK_DIR)/variable_semantic.o $(CHECK_DIR)/function.o\
	$(CHECK_DIR)/check_semantic.o $(SCOPE_DIR)/scope.o $(VISITOR_DIR)/visitor.o \
	$(UTILS_DIR)/print_utils.o \
	$(AST_DIR)/type.o |$(BUILD_DIR)

	@printf "$(CYAN)🔗 Getting ready...$(RESET)\n";
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@printf "$(CYAN)🔄 Compiling...$(RESET)\n";


# Reglas para generar el parser y lexer
y.tab.c y.tab.h: $(PARSER_DIR)/parser.y
	@printf "$(CYAN)🔄 Generating parser...$(RESET)\n";
	@$(YACC) $(YFLAGS) $< || (echo "Bison failed to process parser.y"; exit 1)

lex.yy.c: $(LEXER_DIR)/lexer.l y.tab.h
	@printf "$(CYAN)🔄 Generating lexer...$(RESET)\n";
	@$(LEX) $(LEXFLAGS) $< || (echo "Flex failed to process lexer.l"; exit 1)

$(LLVM_DIR)/visitor_llvm.o: $(LLVM_DIR)/visitor_llvm.c $(LLVM_DIR)/visitor_llvm.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(LLVM_DIR)/codegen.o: $(LLVM_DIR)/codegen.c $(LLVM_DIR)/codegen.h $(AST_DIR)/ast.h $(LLVM_DIR)/visitor_llvm.h
	@echo "⚡ Compiling module LLVM..."
	@$(CC) $(CFLAGS) -c $< -o $@

# $(LLVM_DIR)/llvm_builtins.o: $(LLVM_DIR)/llvm_builtins.c $(LLVM_DIR)/llvm_builtins.h $(VISITOR_DIR)/llvm_visitor.h
# 	@$(CC) $(CFLAGS) -c $< -o $@

$(LLVM_SCOPE_DIR)/llvm_scope.o: $(LLVM_SCOPE_DIR)/llvm_scope.c $(LLVM_SCOPE_DIR)/llvm_scope.h
	@$(CC) $(CFLAGS) -c $< -o $@

# $(LLVM_DIR)/llvm_string.o: $(LLVM_DIR)/llvm_string.c $(LLVM_DIR)/llvm_string.h
# 	@$(CC) $(CFLAGS) -c $< -o $@

$(LLVM_DIR)/llvm_op.o: $(LLVM_DIR)/llvm_op.c $(LLVM_DIR)/llvm_op.h $(LLVM_DIR)/visitor_llvm.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(AST_DIR)/ast.o: $(AST_DIR)/ast.c $(AST_DIR)/ast.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(UTILS_DIR)/print_utils.o: $(UTILS_DIR)/print_utils.c $(UTILS_DIR)/print_utils.h
	@$(CC) $(CFLAGS) -c $< -o $@

# $(CHECK_DIR)/check_semantic.o: $(CHECK_DIR)/check_semantic.c $(CHECK_DIR)/check_semantic.h $(AST_DIR)/ast.h
# 	@$(CC) $(CFLAGS) -c $< -o $@



$(SCOPE_DIR)/scope.o: $(SCOPE_DIR)/scope.c $(SCOPE_DIR)/scope.h
	@$(CC) $(CFLAGS) -c $< -o $@

# $(SCOPE_DIR)/context.o: $(SCOPE_DIR)/context.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

$(VISITOR_DIR)/visitor.o: $(VISITOR_DIR)/visitor.c $(VISITOR_DIR)/visitor.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(AST_DIR)/type.o: $(AST_DIR)/type.c $(AST_DIR)/type.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(AST_DIR)/keyword.o: $(AST_DIR)/keyword.c $(AST_DIR)/keyword.h
	@$(CC) $(CFLAGS) -c $< -o $@



# $(CHECK_DIR)/basic_checking.o: $(CHECK_DIR)/basic_checking.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

# $(CHECK_DIR)/variable_checking.o: $(CHECK_DIR)/variable_checking.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

# $(CHECK_DIR)/function_checking.o: $(CHECK_DIR)/function_checking.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

# $(CHECK_DIR)/unification.o: $(CHECK_DIR)/unification.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

# $(CHECK_DIR)/cond_loop_checking.o: $(CHECK_DIR)/cond_loop_checking.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

$(CHECK_DIR)/typecheck.o: $(CHECK_DIR)/typecheck.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(CHECK_DIR)/variable_semantic.o: $(CHECK_DIR)/variable_semantic.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(CHECK_DIR)/function.o: $(CHECK_DIR)/function.c
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
    # run, backtrace

# Regla para limpiar todos los archivos generados
clean:
	@echo "$(CYAN)🧹 Cleaning project...$(RESET)"
	@rm -rf $(BUILD_DIR)
	@rm -f *.o $(EXEC) y.tab.* lex.yy.c *.output y.* output.ll program
	@rm -f $(AST_DIR)/*.o
	@rm -f $(LLVM_DIR)/*.o
	@rm -f $(CHECK_DIR)/*.o
	@rm -f $(LLVM_SCOPE_DIR)/*.o
	@rm -f $(VISITOR_DIR)/*.o
	@rm -f $(SCOPE_DIR)/*.o
	
