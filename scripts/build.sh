#!/usr/bin/env bash

# Prefer clang++, fall back to g++
if command -v clang++ >/dev/null 2>&1; then
    COMPILER=clang++
    echo Using clang++ compiler
elif command -v g++ >/dev/null 2>&1; then
    COMPILER=g++
    echo Using g++ compiler
else
    echo "Error: Neither clang++ nor g++ found. Please install one or add it to PATH." >&2
    exit 1
fi

echo "Baking your bread..."
mkdir -p build
"$COMPILER" src/bread.cpp -o build/bread -std=c++20 -O2 -Wall -Wextra -Werror \
    && echo "Build successful!" \
    || { echo "Build failed!" >&2; exit 1; }
