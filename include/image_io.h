// image_io.h

#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include <string>

class Image;

Image load_image_pbm(std::string path, bool binary);
Image load_image_pgm(std::string path, bool binary);
Image load_image_ppm(std::string path, bool binary);


#endif