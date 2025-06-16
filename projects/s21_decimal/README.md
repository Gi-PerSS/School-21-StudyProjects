# s21_decimal

A C library implementing the `s21_decimal` type for precise decimal arithmetic, suitable for financial calculations.

## Features
- Supports decimal numbers from -79,228,162,514,264,337,593,543,950,335 to +79,228,162,514,264,337,593,543,950,335.
- Binary representation: 96-bit integer, 1-bit sign, scaling factor (10^0 to 10^28) in a 4-element int array.
- Arithmetic operations: addition, subtraction, multiplication, division, modulo (with banker’s rounding for overflow).
- Comparison operations: less, less or equal, greater, greater or equal, equal, not equal.
- Conversions: from/to int, from/to float (with precision limits).
- Other functions: floor, round, truncate, negate.
- Error handling for overflow, underflow, division by zero, and conversion errors.

## Technical Details
- Written in C11 (gcc), following Google Style.
- Code in `src`, developed as a static library (`s21_decimal.a`) with `s21_decimal.h`.
- Structural programming approach, prefix `s21_` for functions.
- Unit tests (Check library) cover ≥80% of each function.
- Makefile targets: all, clean, test, s21_decimal.a, gcov_report (HTML coverage report).
- No `__int128` used; adheres to POSIX.1-2017.

[Русская версия README](README_RUS.md)