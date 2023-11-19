#!/bin/bash

# Установка cmake
sudo apt install -y cmake

# Установка пакетов, которые необходимы для сборки grpc
sudo apt install -y build-essential autoconf libtool pkg-config

# Клонирование репозитория с заданными параметрами
git clone --recurse-submodules -b v1.59.2 --depth 1 --shallow-submodules https://github.com/grpc/grpc $HOME

# Установка переменной окружения MY_INSTALL_DIR
export MY_INSTALL_DIR=$HOME/.local

# Создание директории для установки
mkdir -p $MY_INSTALL_DIR

# Добавление пути установки в переменную PATH
export PATH="$MY_INSTALL_DIR/bin:$PATH"

# Создание директории для сборки gRPC
mkdir -p $HOME/grpc/cmake/build

# Переход в директорию для сборки
pushd $HOME/grpc/cmake/build

# Настройка сборки с помощью CMake
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../..

# Сборка проекта
make -j 4

# Установка собранного проекта
make install

# Возврат в предыдущую директорию
popd

# Создать директорию для сборки проекта ping-pong
mkdir build

# Перейти в эту директорию
pushd build

# Создать Makefile
cmake ..

# Запустить сборку
make -j 4

# Выйти из директории
popd
