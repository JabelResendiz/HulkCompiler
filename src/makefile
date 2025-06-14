
GREEN := \033[32m
BLUE := \033[34m
RED := \033[31m
YELLOW := \033[33m
CYAN := \033[36m
RESET := \033[0m

# Mensajes de estado
define MSG_COMPILING
$(CYAN)🛠️  Compilando $< a $@...$(RESET)
endef

define MSG_LINKING
$(BLUE)🔗 Enlazando $@...$(RESET)
endef

define MSG_SUCCESS
$(GREEN)✅ Éxito: Build completado$(RESET)
endef

define MSG_CLEANING
$(YELLOW)🧹 Limpiando archivos generados...$(RESET)
endef

define MSG_ERROR
$(RED)❌ Error:
endef


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
ERROR_DIR = error
TYPE_DIR = type_value

.PHONY: all compile execute clean debug

all: compile

compile: $(EXEC)
	@printf "$(GREEN)✅ Compilación completada con éxito$(RESET)\n"
	@printf "$(CYAN)🚀 Ejecutando el compilador HULK...$(RESET)\n\n"
	@./$(EXEC)
	
# Build the directoru build
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(EXEC): lex.yy.o y.tab.o $(AST_DIR)/ast.o $(AST_DIR)/keyword.o \
	$(AST_DIR)/basic.o $(AST_DIR)/cond_while.o $(AST_DIR)/function.o $(AST_DIR)/op.o $(AST_DIR)/oop.o  \
	$(TYPE_DIR)/type.o $(TYPE_DIR)/operators.o \
	$(SRC_DIR)/main.o \
    $(LLVM_DIR)/init_codegen.o $(LLVM_DIR)/visitor_llvm.o \
	$(LLVM_DIR)/codegen.o $(LLVM_DIR)/codegen_basic.o $(LLVM_DIR)/codegen_function.o\
	$(LLVM_DIR)/codegen_control.o $(LLVM_DIR)/codegen_op.o \
	$(LLVM_SCOPE_DIR)/llvm_scope.o \
    $(CHECK_DIR)/typecheck.o  $(CHECK_DIR)/variable_semantic.o $(CHECK_DIR)/function.o $(CHECK_DIR)/cond_while.o\
	$(CHECK_DIR)/check_semantic.o $(CHECK_DIR)/type_semantic.o \
	$(SCOPE_DIR)/scope.o $(SCOPE_DIR)/inheritance.o \
	$(SCOPE_DIR)/env.o $(SCOPE_DIR)/function.o $(SCOPE_DIR)/unifiedIndex.o $(SCOPE_DIR)/usage.o \
	$(VISITOR_DIR)/visitor.o \
	$(UTILS_DIR)/print_utils.o  $(ERROR_DIR)/error.o\
	|$(BUILD_DIR)

	@printf "$(BLUE)🔗 Enlazando objetos...$(RESET)\n"
	@printf "$(CYAN)🛠️  Construyendo ejecutable final...$(RESET)\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@printf "$(GREEN)✨ Ejecutable $(BUILD_DIR)/HULK creado$(RESET)\n\n"

# Reglas para generar el parser y lexer
y.tab.c y.tab.h: $(PARSER_DIR)/parser.y
	@printf "$(CYAN)📖 Generando parser con Bison...$(RESET)\n"
	@$(YACC) $(YFLAGS) $< || { printf "$(RED)❌ Error en parser.y$(RESET)\n"; exit 1; }

lex.yy.c: $(LEXER_DIR)/lexer.l y.tab.h
	@printf "$(CYAN)🔤 Generando lexer con Flex...$(RESET)\n"
	@$(LEX) $(LEXFLAGS) $< || { printf "$(RED)❌ Error en lexer.l$(RESET)\n"; exit 1; }

## AQUI LOS DE CODEGEN
$(LLVM_DIR)/visitor_llvm.o: $(LLVM_DIR)/visitor_llvm.c $(LLVM_DIR)/visitor_llvm.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(LLVM_DIR)/codegen.o: $(LLVM_DIR)/codegen.c $(LLVM_DIR)/codegen.h $(AST_DIR)/ast.h $(LLVM_DIR)/visitor_llvm.h
	@echo "⚡ Compilando module LLVM..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LLVM_SCOPE_DIR)/llvm_scope.o: $(LLVM_SCOPE_DIR)/llvm_scope.c $(LLVM_SCOPE_DIR)/llvm_scope.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(LLVM_DIR)codegen_basic/.o: $(LLVM_DIR)/codegen_basic.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LLVM_DIR)codegen_control/.o: $(LLVM_DIR)/codegen_control.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LLVM_DIR)codegen_function/.o: $(LLVM_DIR)/codegen_function.c
	@$(CC) $(CFLAGS) -c $< -o $@

# $(LLVM_DIR)codegen_oop/.o: $(LLVM_DIR)/codegen_oop.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

$(LLVM_DIR)codegen_op/.o: $(LLVM_DIR)/codegen_op.c
	@$(CC) $(CFLAGS) -c $< -o $@



# AST
$(AST_DIR)/ast.o: $(AST_DIR)/ast.c $(AST_DIR)/ast.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(UTILS_DIR)/print_utils.o: $(UTILS_DIR)/print_utils.c $(UTILS_DIR)/print_utils.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(ERROR_DIR)/error.o: $(ERROR_DIR)/error.c $(ERROR_DIR)/error.h
	@$(CC) $(CFLAGS) -c $< -o $@

# AQUI VAN LAS DEL DIRECTORIO SE SCOPE
$(SCOPE_DIR)/scope.o: $(SCOPE_DIR)/scope.c $(SCOPE_DIR)/scope.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(SCOPE_DIR)/inheritance.o: $(SCOPE_DIR)/inheritance.c $(SCOPE_DIR)/inheritance.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(SCOPE_DIR)/env.o: $(SCOPE_DIR)/env.c $(SCOPE_DIR)/env.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(SCOPE_DIR)/function.o: $(SCOPE_DIR)/function.c $(SCOPE_DIR)/function.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(SCOPE_DIR)/unifiedIndex.o: $(SCOPE_DIR)/unifiedIndex.c $(SCOPE_DIR)/unifiedIndex.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(SCOPE_DIR)/usage.o: $(SCOPE_DIR)/usage.c $(SCOPE_DIR)/usage.h
	@$(CC) $(CFLAGS) -c $< -o $@



# AQUI VAN LAS DIRECTORIO DE VISITOR
$(VISITOR_DIR)/visitor.o: $(VISITOR_DIR)/visitor.c $(VISITOR_DIR)/visitor.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(TYPE_DIR)/type.o: $(TYPE_DIR)/type.c $(TYPE_DIR)/type.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(TYPE_DIR)/operators.o: $(TYPE_DIR)/operators.c $(TYPE_DIR)/operators.h
	@$(CC) $(CFLAGS) -c $< -o $@


# AQUI VAN LAS DIRECTORIO DE AST


$(AST_DIR)/keyword.o: $(AST_DIR)/keyword.c $(AST_DIR)/keyword.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(AST_DIR)/function.o: $(AST_DIR)/function.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(AST_DIR)/basic.o: $(AST_DIR)/basic.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(AST_DIR)/cond_while.o: $(AST_DIR)/cond_while.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(AST_DIR)/op.o: $(AST_DIR)/op.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(AST_DIR)/poo.o: $(AST_DIR)/poo.c
	@$(CC) $(CFLAGS) -c $< -o $@


# AQUI VAN LAS DIRECTORIO DE CHECK

$(CHECK_DIR)/typecheck.o: $(CHECK_DIR)/typecheck.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(CHECK_DIR)/variable_semantic.o: $(CHECK_DIR)/variable_semantic.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(CHECK_DIR)/function.o: $(CHECK_DIR)/function.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(CHECK_DIR)/cond_while.o: $(CHECK_DIR)/cond_while.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(CHECK_DIR)/type_semantic.o: $(CHECK_DIR)/type_semantic.c
	@$(CC) $(CFLAGS) -c $< -o $@


%.o: %.c
	@printf "$(CYAN)🔨 Compilando $<...$(RESET)\n";
	@$(CC) $(CFLAGS) -c $< -o $@


execute: compile
	@if [ -s $(BUILD_DIR)/output.ll ]; then \
		printf "$(CYAN)⚙️  Compilando IR (output.ll) a binario...$(RESET)\n"; \
		clang $(BUILD_DIR)/output.ll -o $(BUILD_DIR)/program -lm || { \
			printf "$(RED)❌ Error: Fallo en la compilación del IR. Posibles causas:\n   - Errores en el código generado\n   - Falta vincular bibliotecas$(RESET)\n"; \
			exit 1; \
		}; \
		printf "\n$(GREEN)═══════════ [ EJECUTANDO PROGRAMA ] ═══════════$(RESET)\n"; \
		$(BUILD_DIR)/program; \
	else \
		printf "$(YELLOW)⚠️  Advertencia: No hay código para ejecutar.$(RESET)\n"; \
		printf "$(YELLOW)   Archivo output.ll no existe o está vacío.$(RESET)\n"; \
		printf "$(YELLOW)   Posibles causas:\n"; \
		printf "$(YELLOW)   - El programa no generó código LLVM\n"; \
		printf "$(YELLOW)   - Hubo errores en la compilación$(RESET)\n\n"; \
	fi

clean:
	@printf "$(YELLOW)🧹 Limpiando proyecto...$(RESET)\n"
	@printf "$(BLUE)   Eliminando:\n"
	@printf "   - Objetos y ejecutables\n"
	@printf "   - Archivos temporales$(RESET)\n"
	@rm -rf $(BUILD_DIR) *.o $(EXEC) y.tab.* lex.yy.c *.output y.* output.ll program
	@rm -f $(AST_DIR)/*.o $(LLVM_DIR)/*.o $(CHECK_DIR)/*.o $(LLVM_SCOPE_DIR)/*.o \
	       $(VISITOR_DIR)/*.o $(SCOPE_DIR)/*.o $(UTILS_DIR)/*.o
	@printf "$(GREEN)✔️  Proyecto limpio$(RESET)\n"