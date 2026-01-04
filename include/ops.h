// ops.h

#ifndef OPS_H
#define OPS_H

class Image;

Image blur(Image img, int passes, int kernel_size);

#endif