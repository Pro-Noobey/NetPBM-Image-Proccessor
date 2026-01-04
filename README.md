NetPBM Image Proccessor
=======================

Image Proccessor focused on **NetPBM Image Formats**

## Supports
* **.PBM** (Portable Binary Map) - Binary and ASCII
* **.PGM** (Portable Gray Map) - Binary and ASCII
* **.PPM** (Portable Pixel Map) - Binary and ASCII
* **.PAM** (Portable Arbitary Map) - Binary Only
* **.BMP** (BitMap) - *Extra*

# Functions

Functions the Proccessor can do

## Blur
Applies A **Box Blur** with parameters `passes` and `kernel_size`

## Conversion
Conversion from one of the **above supported formats** to **another supported format**

## Optimize
Makes the Image smaller in size by doing **semantic compression**  
Example: If the Image is a `PPM` but all the pixels are grayscale (`r==g and g==b`) then it will convert the image to a `PGM`.
