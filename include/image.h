// image.h

#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <cstdint>

// constants
const int PBM_ASCII = 1;
const int PBM_BINARY = 4;
const int PGM_ASCII = 2;
const int PGM_BINARY = 5;
const int PPM_ASCII = 3;
const int PPM_BINARY = 6;
const int PAM_BINARY_ASCII = 7;

struct Pixel
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;
};

class Image
{
public:
    int WIDTH;
    int HEIGHT;
    int MAXVAL;
    int TYPE;
    std::vector<Pixel> data;
};

#endif