#!/bin/bash
# Ensure the build directory exists locally
mkdir -p build

# Compile using your exact local configuration
gcc src/main.c src/logic.c src/data.c -I"C:/raylib/raylib/src" -L"C:/raylib/raylib/src" -lraylib -lopengl32 -lgdi32 -lwinmm -o build/game.exe