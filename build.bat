@echo off
setlocal enabledelayedexpansion

echo Choose compiler:
echo 1) g++
echo 2) clang
echo 3) MSVC (cl)
set /p COMPILER_CHOICE=Enter number: 

if "%COMPILER_CHOICE%"=="1" (
    set COMPILER=g++
    set OUTPUT=nic.exe
    set SRC=src\*.cpp
) else if "%COMPILER_CHOICE%"=="2" (
    set COMPILER=clang++
    set OUTPUT=nic.exe
    set SRC=src\*.cpp
) else if "%COMPILER_CHOICE%"=="3" (
    set COMPILER=cl
    set OUTPUT=nic.exe
    set SRC=src\*.cpp
) else (
    echo Invalid choice
    exit /b 1
)

set /p FLAGS=Enter compiler flags: 

echo.
echo Building...
echo.

if "%COMPILER%"=="cl" (
    %COMPILER% %FLAGS% /Iinclude %SRC% /Fe:%OUTPUT%
) else (
    %COMPILER% %FLAGS% -Iinclude %SRC% -o %OUTPUT%
)

endlocal
