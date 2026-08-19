@echo off
setlocal

:: Prefer clang++, fallback to g++
where clang++ >nul 2>&1
if not errorlevel 1 (
    set COMPILER=clang++
) else (
    where g++ >nul 2>&1
    if not errorlevel 1 (
        set COMPILER=g++
    ) else (
        echo Error: Neither clang++ nor g++ found. Please install one.
        endlocal
        exit /b 1
    )
)

echo Using %COMPILER% compiler
echo Baking your bread...
mkdir build 2>nul
"%COMPILER%" src\bread.cpp -o build\bread.exe -std=c++20 -O2 -Wall -Wextra -Werror

if not errorlevel 1 (
    echo Build successful!
) else (
    echo Build failed!
)

endlocal
