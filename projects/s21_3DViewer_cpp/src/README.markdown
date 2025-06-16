# 3DViewer v2.0

A C++ application for viewing 3D wireframe models in obj format using the MVC pattern and at least three design patterns (e.g., Facade, Strategy, Command).

## Features
- Load obj files (vertices and surfaces only).
- Translate, rotate, and scale models along X, Y, Z axes.
- GUI (using Qt, GTK+, CEF, JUCE, SFML, Nanogui, or Nngui) with:
  - File selection button and name display.
  - Model visualization area.
  - Input fields/buttons for translation, rotation, and scaling.
  - Model info (file name, vertex/edge count).
- Handle models up to 1M vertices without lag (>0.5s).
- Additional features:
  - Projection type (parallel/central), edge type/color/thickness, vertex display/color/size, background color settings, saved between sessions.
  - Save rendered images as BMP/JPEG.
  - Record 5s GIF animations (640x480, 10fps) of transformations.

## Technical Details
- Written in C++20, following Google Style.
- Code in `src` folder, built with Makefile (targets: all, install, uninstall, clean, dvi, dist, tests).
- Full unit test coverage for model loading and affine transformations.
- Uses `s21` namespace and s21_matrix+ library for transformations.

[Русская версия README](README_RUS.md)