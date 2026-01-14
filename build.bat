@echo off
setlocal

REM ===== CONFIG =====
set COMPILER=g++
set FLAGS=-O3 -march=native -fopenmp
set INCLUDE=-Iinclude
set SRC=src\*.cpp
set OUTPUT=pbmtool.exe
REM ==================

echo Building with %COMPILER%...
echo Flags: %FLAGS%
echo.

%COMPILER% %FLAGS% %INCLUDE% %SRC% -o %OUTPUT%

if errorlevel 1 (
    echo.
    echo Build failed.
    exit /b 1
)

echo.
echo Build successful: %OUTPUT%
endlocal

