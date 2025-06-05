# Ruta de llvm-config (ajústala si usas WSL o Mac)
LLVM_CONFIG = llvm-config
LLVM_CFLAGS = $(shell $(LLVM_CONFIG) --cflags)
LLVM_LDFLAGS = $(shell $(LLVM_CONFIG) --libs core)

# Archivos
SRC = codegen.c
BIN = codegen
IR  = output.ll
BC  = output.bc
ASM = output.s
EXE = output

# Regla por defecto
all: run

# Paso 1: Compilar codegen.c
$(BIN): $(SRC)
	clang $(SRC) $(LLVM_CFLAGS) $(LLVM_LDFLAGS) -o $(BIN)

# Paso 2: Ejecutar y generar IR
$(IR): $(BIN)
	./$(BIN)

# Paso 3: IR → Bytecode
$(BC): $(IR)
	llvm-as $(IR) -o $(BC)

# Paso 4: Bytecode → ASM
$(ASM): $(BC)
	llc $(BC) -o $(ASM)

# Paso 5: ASM → binario ejecutable
$(EXE): $(ASM)
	clang $(ASM) -o $(EXE)

# Paso 6: Ejecutar el programa final
run: $(EXE)
	./$(EXE)
	@echo "Retorno del programa: $?"

# Limpiar archivos intermedios
clean:
	rm -f $(BIN) $(IR) $(BC) $(ASM) $(EXE)
