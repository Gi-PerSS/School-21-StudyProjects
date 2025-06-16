# s21_matrix+

A C++ library for matrix operations using an object-oriented approach, designed for numerical computations.

## Features
- Implements `S21Matrix` class with private fields: `double** matrix_`, `int rows_`, `int cols_`.
- Operations: equality check, addition, subtraction, multiplication (by number/matrix), transpose, determinant, complements, inverse matrix.
- Overloaded operators: +, -, *, ==, =, +=, -=, *=, (i,j) for indexing.
- Constructors: default, parameterized, copy, move; destructor for cleanup.
- Accessors/mutators for `rows_` and `cols_` with resizing (adds zeros or trims excess).
- Exception handling for mismatched dimensions, non-square matrices, zero determinant, or invalid indices.

## Technical Details
- Written in C++17 (gcc), following Google Style.
- Code in `src`, developed as a static library (`s21_matrix_oop.a`) with `s21_matrix_oop.h`.
- Unit tests (GTest) cover all functions.
- Makefile targets: all, clean, test, s21_matrix_oop.a.

[Русская версия README](README_RUS.md)