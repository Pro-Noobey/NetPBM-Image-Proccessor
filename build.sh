#!/usr/bin/env bash

echo "Choose compiler:"
echo "1) g++"
echo "2) clang"
echo "3) MSVC (cl)"
read -p "Enter number: " COMPILER_CHOICE

case "$COMPILER_CHOICE" in
  1)
    COMPILER=g++
    OUTPUT=nic
    ;;
  2)
    COMPILER=clang++
    OUTPUT=nic
    ;;
  3)
    COMPILER=cl
    OUTPUT=nic.exe
    ;;
  *)
    echo "Invalid choice"
    exit 1
    ;;
esac

read -p "Enter compiler flags: " FLAGS

echo
echo "Building..."
echo

if [ "$COMPILER" = "cl" ]; then
    $COMPILER $FLAGS /Iinclude src/*.cpp /Fe:$OUTPUT
else
    $COMPILER $FLAGS -Iinclude src/*.cpp -o $OUTPUT
fi
