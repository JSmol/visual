#!/bin/bash
set -ex

# main visualizer logic as .so
gcc helpers.c -c -o static/helpers.o
gcc visual.c -fPIC -rdynamic -shared -o include/visual.so \
    static/helpers.o \
    -L/home/josip/visual/raylib/src/ \
    -lraylib -lm

# Application
gcc app.c -c -o static/app.o
gcc main.c -o main \
    static/app.o \
    -L/home/josip/visual/raylib/src/ \
    -lraylib -lm

# ./main

