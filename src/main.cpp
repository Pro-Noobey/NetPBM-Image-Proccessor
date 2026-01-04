#include <iostream> // for I/O
#include <vector> // for storing pixel data
#include <string> // for I/O
#include <fstream> // file operations
#include <chrono> // for timing
#include "ops.h" // for Image operations
#include "image_io.h" // for Image I/O
#include <omp.h> // Parralelelelelleel Proccessing Babyyy

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
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
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

Image load_image(std::string path)
{
    std::ifstream file(path, std::ios::binary);

    std::string type;
    file >> type;
    int _type = type[1] - '0';

    if (_type == PBM_ASCII)
    {
        return load_image_pbm(path, false);
    }
    else if (_type == PBM_BINARY)
    {
        return load_image_pbm(path, true);
    }
    else if (_type == PPM_ASCII)
    {
        return load_image_ppm(path, false);
    }
    else if (_type == PPM_BINARY)
    {
        return load_image_ppm(path, true);
    }
    else if (_type == PGM_ASCII)
    {
        return load_image_pgm(path, false);
    }
    else if (_type == PGM_BINARY)
    {
        return load_image_pgm(path, true);
    }
    return {};
}

int write_image(std::string path, Image img)
{
    if (img.TYPE == PPM_ASCII)
    {
        return write_image_ppm(path, img);
    }
    return 2; // Format does not exist
}

std::string input(const std::string& prompt) {
    std::cout << prompt;
    std::string response;
    std::getline(std::cin, response);
    return response;
}

int main() {

    omp_set_num_threads(2);

    std::string path = input("enter path\n>>");
    auto start = std::chrono::high_resolution_clock::now();
    Image img = load_image(path);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    if (img.data.empty()) {
        std::cout << "Failed to load image." << std::endl;
        return 1;
    }
    
    std::cout << "Image loaded successfully: " << img.WIDTH << "x" << img.HEIGHT << " in " << duration.count() << " milliseconds." << std::endl;

    std::string whatodo = input("What to do with image? : \n1. Blur\n>>");

    if (whatodo == "Blur")
    {
        int passes = std::stoi(input("Enter Passes Amount\n>>"));
        int kernel_size = std::stoi(input("Enter Kernel Size\n>>"));
        auto new_start = std::chrono::high_resolution_clock::now();
        img = blur(img, passes, kernel_size);
        auto new_end = std::chrono::high_resolution_clock::now();
        auto new_duration = std::chrono::duration_cast<std::chrono::seconds>(new_end - new_start);
    }
    std::cout << "\nBlurring Complete! in " << duration.count() << " seconds" << std::endl;

    return 0;
}
