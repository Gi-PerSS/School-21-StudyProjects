# s21_matrix

A C library for matrix operations, designed for numerical computations in applications like computer graphics.

## Features
- Matrix operations: create, remove, compare (up to 7 decimal places), add, subtract, multiply by number, multiply matrices, transpose, determinant, calculate complements, inverse matrix.
- Supports rectangular, square, diagonal, and triangular matrices.
- Error codes: 0 (OK), 1 (invalid matrix), 2 (operation error, e.g., mismatched sizes).
- Matrix structure: `matrix_t` with `double** matrix`, `rows`, and `columns`.

## Technical Details
- Written in C11 (gcc), following Google Style.
- Code in `src`, developed as a static library (`s21_matrix.a`) with `s21_matrix.h`.
- Structural programming, functions prefixed with `s21_`.
- Unit tests (Check library) cover ≥80% of each function.
- Makefile targets: all, clean, test, s21_matrix.a, gcov_report (HTML coverage report).
- Adheres to POSIX.1-2017, avoids legacy/obsolete constructs.
- Fractional precision up to 6 decimal places.

[Русская версия README](README_RUS.md)