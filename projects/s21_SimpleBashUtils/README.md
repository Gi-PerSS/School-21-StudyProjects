# Simple Bash Utils

Development of `cat` and `grep` utilities in C (C11 standard) for text processing in a Linux terminal.

## Tasks
1. **Cat Utility**:
   - Implement support for flags: `-b`, `-e`, `-n`, `-s`, `-t` (including GNU versions).
   - Source files and build in `src/cat/`, executable: `s21_cat`.
2. **Grep Utility**:
   - Implement support for flags: `-e`, `-i`, `-v`, `-c`, `-l`, `-n`.
   - Additional (optional): flags `-h`, `-s`, `-f`, `-o` and their pairwise combinations (e.g., `-iv`, `-in`).
   - Use `pcre` or `regex` libraries for regular expressions.
   - Source files and build in `src/grep/`, executable: `s21_grep`.
3. **General Requirements**:
   - Build via Makefile, targets: `s21_cat`, `s21_grep`.
   - Structured programming, no code duplication, shared modules in `src/common/`.
   - Coverage with integration tests based on real Bash utilities' behavior.

[Русская версия этого README](README_RUS.md)