#!/bin/bash

pkill calculator_GUI
rm -f ./GUI/calculator_GUI
# аргумент - файлы бэкэнда
gcc "./GUI/calculator_GUI.c" "./GUI/function_graph.c" ./GUI/credit_calculator.c $@ -o "./GUI/calculator_GUI" -lm -ldl $(pkg-config --cflags --libs gtk+-3.0) -std=c11
