#!/bin/bash

set -e

echo "=== Установка зависимостей ==="

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "Установка для Linux..."
    sudo apt-get update
    sudo apt-get install -y \
        libgtk-3-dev \
        libcairo2-dev \
        librsvg2-dev \
        pkg-config \
        check
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Установка для macOS..."
    if ! command -v brew >/dev/null; then
        echo "Установка Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi

    brew install \
        gtk+3 \
        cairo \
        librsvg \
        pkg-config \
        check

    # Добавляем пути для pkg-config на macOS
    export PKG_CONFIG_PATH="/usr/local/opt/cairo/lib/pkgconfig:/usr/local/opt/libffi/lib/pkgconfig:/usr/local/opt/freetype/lib/pkgconfig"
fi

echo "=== Проверка установленных библиотек ==="
pkg-config --exists gtk+-3.0 cairo || {
    echo "Ошибка: библиотеки не найдены через pkg-config"
    exit 1
}

echo "=== Все зависимости успешно установлены ==="
