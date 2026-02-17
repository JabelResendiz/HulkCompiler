# HULK Compiler

Un compilador completo para el lenguaje **HULK** escrito en **C**, que genera código intermedio en **LLVM IR** y lo ejecuta compilándolo con Clang.

## 📋 Tabla de Contenidos

- [Instalación](#instalación)
- [Herramientas Utilizadas](#herramientas-utilizadas)
- [Estructura del Proyecto](#estructura-del-proyecto)
- [Uso del Makefile](#uso-del-makefile)
- [Características del Lenguaje HULK](#características-del-lenguaje-hulk)
- [Ejemplos](#ejemplos)

## 🔧 Instalación

### Dependencias del Sistema

Antes de compilar, asegúrate de tener instaladas todas las herramientas necesarias:

```bash
sudo apt-get update && sudo apt-get install -y bison flex llvm clang
```

Donde:
- **bison**: Generador de parsers (convierte grammar en código C)
- **flex**: Generador léxico (crea analizadores léxicos)
- **llvm**: Infraestructura de compilación de código intermedio
- **clang**: Compilador de C/C++ que también compila LLVM IR

### Compilar el Proyecto

```bash
make compile
```

Esto generará el ejecutable `build/HULK`.

## ⚙️ Herramientas Utilizadas

### 1. **Flex (Lexical Analyzer Generator)**
- **¿Qué hace?**: Convierte un archivo de especificación léxica (`.l`) en un analizador léxico en C
- **Entrada**: `lexer/lexer.l` (define tokens y palabras clave)
- **Salida**: `lexer/lex.yy.c` (código C que reconoce tokens)
- **Uso en nuestro proyecto**: Reconoce identificadores, números, operadores y palabras clave del lenguaje HULK

### 2. **Bison (Parser Generator)**
- **¿Qué hace?**: Convierte una gramática BNF/YACC (`.y`) en un analizador sintáctico (parser) en C
- **Entrada**: `parser/parser.y` (define la gramática del lenguaje)
- **Salida**: `parser/y.tab.c` y `parser/y.tab.h` (parser que valida la sintaxis)
- **Uso en nuestro proyecto**: Analiza la estructura sintáctica y construye el AST (Abstract Syntax Tree)

### 3. **LLVM (Low Level Virtual Machine)**
- **¿Qué hace?**: Framework para crear compiladores con código intermedio optimizado
- **Entrada**: C code que genera instrucciones LLVM
- **Salida**: `build/output.ll` (código intermedio LLVM)
- **Uso en nuestro proyecto**: Generamos LLVM IR para representación intermedia de código

### 4. **Clang (C Language Family Frontend)**
- **¿Qué hace?**: Compilador de LLVM IR a código ejecutable
- **Entrada**: `build/output.ll` (código intermedio)
- **Salida**: `build/program` (ejecutable)
- **Uso en nuestro proyecto**: Compila el LLVM IR final a binario ejecutable

## 📁 Estructura del Proyecto

```
HulkCompiler/
├── lexer/
│   ├── lexer.l              # Especificación léxica (Flex)
│   ├── lex.yy.c             # Generado: analizador léxico
│   └── lex.yy.o             # Generado: objeto compilado
├── parser/
│   ├── parser.y             # Especificación sintáctica (Bison)
│   ├── y.tab.c              # Generado: parser
│   ├── y.tab.h              # Generado: header del parser
│   ├── y.tab.o              # Generado: objeto compilado
│   └── y.output             # Generado: análisis del parser
├── ast/                     # Abstract Syntax Tree
│   ├── ast.c
│   ├── ast.h
│   └── ast.o                # Generado: objeto compilado
├── semantic_check/          # Análisis semántico
├── type/                    # Sistema de tipos
├── visitor/                 # Patrón Visitor para AST
├── scope/                   # Gestión de scopes/contextos
├── codegen/                 # Generación de código LLVM
├── utils/                   # Utilidades generales
├── build/                   # Directorio de salida
│   ├── HULK                 # Ejecutable principal
│   ├── output.ll            # Código LLVM IR generado
│   └── program              # Programa ejecutable compilado
├── makefile                 # Script de compilación
└── README.md                # Este archivo
```

## 🛠️ Uso del Makefile

### Comandos Disponibles

#### 1. **make compile** (o simplemente `make`)
Compila el proyecto completo:
```bash
make compile
```

**Pasos que ejecuta:**
1. Genera `lexer/lex.yy.c` desde `lexer/lexer.l` usando Flex
2. Genera `parser/y.tab.c` y `parser/y.tab.h` desde `parser/parser.y` usando Bison
3. Compila todos los archivos `.c` a objetos `.o`
4. Enlaza todos los objetos para crear `build/HULK`

#### 2. **make execute**
Compila y ejecuta el proyecto:
```bash
make execute
```

**Pasos que ejecuta:**
1. Ejecuta `make compile`
2. Compila el LLVM IR generado (`build/output.ll`) con Clang
3. Ejecuta el programa resultante

#### 3. **make clean**
Elimina todos los archivos generados:
```bash
make clean
```

Limpia:
- Directorio `build/`
- Archivos `.o` en todas las carpetas
- Archivos generados: `lex.yy.c`, `y.tab.c`, `y.tab.h`, `y.output`, `output.ll`, `program`

#### 4. **make debug**
Abre el compilador en GDB para debugging:
```bash
make debug
```

### Cómo Funciona el Makefile

El makefile implementa un **sistema de compilación en capas**:

**Capa 1: Generación Léxica**
```
lexer/lexer.l → [Flex] → lexer/lex.yy.c → [Clang] → lexer/lex.yy.o
```

**Capa 2: Generación Sintáctica**
```
parser/parser.y → [Bison] → parser/y.tab.c, parser/y.tab.h → [Clang] → parser/y.tab.o
```

**Capa 3: Compilación de Módulos**
```
*.c files → [Clang] → *.o files
```

**Capa 4: Enlazado**
```
*.o files → [Clang + LLVM] → build/HULK
```

**Capa 5: Generación de Código Intermedio**
```
build/HULK → (procesa archivo HULK) → build/output.ll
```

**Capa 6: Compilación Final**
```
build/output.ll → [Clang] → build/program
```

### Organización de Archivos Generados

Con esta configuración del makefile:
- Los archivos generados por **Flex** se guardan en `lexer/`
- Los archivos generados por **Bison** se guardan en `parser/`
- Los objetos compilados (`.o`) se guardan en su carpeta correspondiente
- El ejecutable final se guarda en `build/`

Esto mantiene el proyecto limpio y organizado.

---

## 🚀 Características del Lenguaje HULK

### Tipos de Datos Soportados
- **Primitivos**: `number`, `string`, `bool`
- **Objetos**: Clases con herencia

### Características Principales
- Funciones con tipado estático
- Clases e herencia
- Pattern matching
- Inferencia de tipos
- Manejo de excepciones

[**Documentación completa del lenguaje HULK**](https://matcom.github.io/hulk)

### Funcionalidades Implementadas
- ✅ Análisis léxico (Flex)
- ✅ Análisis sintáctico (Bison)
- ✅ Análisis semántico y verificación de tipos
- ✅ Construcción de AST
- ✅ Generación de LLVM IR
- ✅ Compilación a código ejecutable
- ✅ Manejo de funciones y clases
- ✅ Scopes y contextos

## 📝 Ejemplos

### Ejemplo 1: Función Simple
```hulk
function hello(name: string): string => "Hello, " + name;

hello("World");
```

### Ejemplo 2: Clase
```hulk
class Point {
    x: number;
    y: number;
};

let p = new Point();
```

Más ejemplos disponibles en `script.hulk`

---

**Última actualización**: Febrero 2026
