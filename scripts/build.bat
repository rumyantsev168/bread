@echo off
setlocal
pwd
:: Prefer clang++, fallback to g++
where clang++ >nul 2>&1
if not errorlevel 1 (
    set COMPILER=clang++
    echo Using clang++ compiler
) else (
    where g++ >nul 2>&1
    if not errorlevel 1 (
        set COMPILER=g++
        echo Using g++ compiler
    ) else (
        echo Error: Neither clang++ nor g++ found. Please install one.
        endlocal
        exit /b 1
    )
)

echo Baking your bread...
"%COMPILER%" src\bread.cpp -o build\bread.exe -O2 -Wall -Wextra -Werror

if not errorlevel 1 (
    echo Build successful!
) else (
    echo Build failed!
)

endlocal
pause
