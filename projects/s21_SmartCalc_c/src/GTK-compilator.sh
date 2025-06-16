#!/bin/bash

SOURCE_FILES="$1"
OUTPUT="./GUI/calculator_GUI"

# Определение ОС и установка путей
if [[ "$OSTYPE" == "darwin"* ]]; then
    # Пути для macOS
    export PKG_CONFIG_PATH="/usr/local/opt/gtk+3/lib/pkgconfig:/usr/local/opt/cairo/lib/pkgconfig:/usr/local/opt/libffi/lib/pkgconfig:/usr/local/opt/freetype/lib/pkgconfig:$PKG_CONFIG_PATH"
    GTK_CFLAGS="-I/usr/local/opt/gtk+3/include/gtk-3.0 -I/usr/local/opt/cairo/include/cairo"
    GTK_LIBS="-L/usr/local/opt/gtk+3/lib -lgtk-3 -L/usr/local/opt/cairo/lib -lcairo"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # Пути для Linux
    GTK_CFLAGS=$(pkg-config --cflags gtk+-3.0 cairo 2>/dev/null)
    GTK_LIBS=$(pkg-config --libs gtk+-3.0 cairo 2>/dev/null)
fi

# Если pkg-config не сработал, используем стандартные пути
if [ -z "$GTK_CFLAGS" ]; then
    GTK_CFLAGS="-I/usr/include/gtk-3.0 -I/usr/include/cairo"
    GTK_LIBS="-lgtk-3 -lcairo"
fi

echo "Using CFLAGS: $GTK_CFLAGS"
echo "Using LIBS: $GTK_LIBS"

# Компиляция
gcc -Wall -Wextra -Werror \
    $GTK_CFLAGS \
    $SOURCE_FILES \
    ./GUI/calculator_GUI.c \
    ./GUI/function_graph.c \
    ./GUI/credit_calculator.c \
    -o $OUTPUT \
    $GTK_LIBS -lm

if [ $? -eq 0 ]; then
    echo "Compilation successful: $OUTPUT"
else
    echo "Compilation failed"
    exit 1
fi
