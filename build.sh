#!/usr/bin/env bash
set -e

# ===== CONFIG =====
COMPILER=g++
FLAGS="-O3 -march=native -fopenmp"
INCLUDE="-Iinclude"
SRC="src/*.cpp"
OUTPUT="nic"
# ==================

echo "Building with $COMPILER..."
echo "Flags: $FLAGS"
echo

$COMPILER $FLAGS $INCLUDE $SRC -o $OUTPUT

echo
echo "Build successful: $OUTPUT"
