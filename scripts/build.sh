#!/usr/bin/env bash

# Prefer clang++, fall back to g++
if command -v clang++ >/dev/null 2>&1; then
    COMPILER=clang++
elif command -v g++ >/dev/null 2>&1; then
    COMPILER=g++
else
    echo "Error: Neither clang++ nor g++ found. Please install one or add it to PATH." >&2
    exit 1
fi

echo "Using $COMPILER compiler"
echo "Baking your bread..."
mkdir -p build
"$COMPILER" src/bread.cpp -o build/bread -std=c++20 -O2 -Wall -Wextra -Werror \
    && echo "Build successful!" \
    || { echo "Build failed!" >&2; exit 1; }
