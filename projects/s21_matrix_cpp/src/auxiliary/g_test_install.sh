#!/bin/bash
# установка g_test в ubuntu 20, отсюда: https://habr.com/ru/articles/667880/

apt-get update
apt-get install libgtest-dev libgmock-dev -y
apt-get install libtbb-dev -y
apt-get install cmake -y
cd /usr/src/googletest/ && mkdir build && cd build || exit
cmake .. && make && cp lib/* /usr/lib
rm -rf build
