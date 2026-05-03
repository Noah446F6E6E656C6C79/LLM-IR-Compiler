# LLM-IR Compiler

A custom programming language and compiler built entirely from scratch in pure C. 

LLM-IR (Large Language Model - Intermediate Representation) is designed with a specific architectural philosophy: **to optimize and facilitate code generation by Large Language Models, rather than reasoning about existing code.** By enforcing strict syntactic rules—such as requiring space separation for all tokens and utilizing highly verbose keywords—the language eliminates the need for complex regular expressions, making it highly predictable for AI generation.

This compiler is currently in active development as part of a 15-week independent study project for the Spring 2026 semester within the Towson University Computer Science department.

## Architecture

The compiler is written in strictly standard C99, with a focus on high-performance execution and precise memory management. It currently implements the entire Front-End of the compilation pipeline:

* **Lexical Analysis (Scanner/Lexer):** * Implements a custom dynamic array (`TokenList`) to manage memory safely.
  * Processes raw text into a categorized token stream.
  * Includes robust file I/O handling, automatically stripping invisible Windows BOM (Byte Order Mark) characters and handling cross-platform Carriage Returns (`\r\n`).
* **Syntax Analysis (Recursive Descent Parser):** * Parses the token stream into a hierarchical Abstract Syntax Tree (AST).
  * Uses memory-efficient C `union` structures for AST nodes.
  * Currently supports grammatical parsing for:
    * `DEFINE_FUNCTION` blocks
    * `DECLARE` variable statements

## Getting Started

### Prerequisites
* A C compiler (GCC, Clang, or MSVC)
* CMake (Version 3.20 or higher)

### Building the Compiler
This project uses CMake for its build system, keeping the root directory clean by isolating build artifacts.

1. Clone the repository:
   ```bash
   git clone [https://github.com/yourusername/LLM-IR.git](https://github.com/yourusername/LLM-IR.git)
   cd LLM-IR
   ```
2. Generate the build files:
   ```bash
   cmake -S . -B cmake-build-debug
   ```
3. Compile the executable:
   ```bash
   cmake --build cmake-build-debug
   ```

### Running a Test
You can test the compiler by passing a source file written in LLM-IR syntax directly via the command line:

```bash
./cmake-build-debug/compiler test.txt
```

**Example `test.txt` Input:**
```text
DEFINE_FUNCTION main ( ) RETURNING VOID 
BEGIN_FUNCTION 
DECLARE x AS INTEGER INITIALIZED_TO 5 ; 
END_FUNCTION
```

**Output:**
```text
Compiling test.txt...

--- Abstract Syntax Tree ---
FunctionDef(name='main', returns='VOID')
  VarDecl(name='x', type='INTEGER', value='5')

Compilation successful!
```

## Directory Structure

```text
LLM-IR/
├── src/                 # C implementation files (Lexer, Parser, Main)
├── include/             # C header files (Public API and Data Structures)
├── cmake-build-debug/   # Generated executables (Ignored by Git)
├── CMakeLists.txt       # Build system configuration
└── README.md            # Project documentation
```

## Roadmap

- [x] Lexical Analyzer (Tokenization)
- [x] Syntax Analyzer (AST Generation)
- [ ] Semantic Analyzer (Symbol Table & Type Checking)
- [ ] Code Generation (Targeting C or LLVM)
