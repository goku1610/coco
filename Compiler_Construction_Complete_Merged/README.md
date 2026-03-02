# Compiler Construction Complete Merged

This repository merges the working logic from:

- `Compiler_Construction_Project_2025`
- `Compiler-Construction`

The codebase has been reorganized and renamed into a new structure while preserving compiler behavior.

## Layout

All files are now at repository root (flat layout).

Core source files:
- `driver.c`
- `lexer.c`
- `parser.c`
- `parse_runtime.c`
- `grammar_sets.c`
- `ascii_text.c`

Core headers:
- `lexer.h`, `lexerDef.h`
- `parser.h`, `parserDef.h`
- `parse_runtime.h`, `grammar_sets.h`
- `token_model.h`, `grammar_model.h`
- `ascii_text.h`

Supporting files:
- `grammar_g13.txt`, `grammar_g43.txt`
- `testcase*.txt`, `t*.txt`, `lexemesandtokens_*.txt`
- `README_g13.md`, `README_g43.md`
- `coding_details_g13.docx`, `coding_details_g43.pdf`, `language_specification_g13.pdf`

## Build

```bash
make
```

## Run

```bash
./stage1exe testcase.txt parsetreeOutFile.txt
```

## Menu

- `0`: Exit
- `1`: Remove comments and write clean code to output file
- `2`: Print lexer token list
- `3`: Parse code and write parse tree to output file
- `4`: Parse code and print execution time
