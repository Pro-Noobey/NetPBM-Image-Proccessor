#include <iostream> // for I/O
#include <vector> // for storing pixel data
#include <string> // for I/O
#include <fstream> // file operations
#include <chrono> // for timing
#include "ops.h" // for Image operations
#include "image_io.h" // for Image I/O
#include "image.h" // For Pixel and Image struct and class
#include <omp.h> // Parralelelelelleel Proccessing Babyyy

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
    if (img.TYPE == PPM_ASCII || img.TYPE == PPM_BINARY)
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

    std::string whatodo = input("What to do with image? : \n1. Blur\n2. Nothing (Enter Any or Literally Nothing)\n>>");

    // keep a copy of the image to write later; assign to this if we modify it
    Image new_img = img;

    if (whatodo == "Blur")
    {
        int passes = std::stoi(input("Enter Passes Amount\n>>"));
        int kernel_size = std::stoi(input("Enter Kernel Size\n>>"));
        auto new_start = std::chrono::high_resolution_clock::now();
        new_img = blur(img, passes, kernel_size);
        auto new_end = std::chrono::high_resolution_clock::now();
        auto new_duration = std::chrono::duration_cast<std::chrono::milliseconds>(new_end - new_start);
        std::cout << "\nBlurring Complete! in " << new_duration.count() << " milliseconds" << std::endl;
    }

    path = input("Enter Path to write to file: ");
    int code = write_image(path, new_img);

    if (code == 0)
    {
        std::cout << "Successfully Wrote to " << path << " Image! Code: " << code << std::endl;
    }
    else if (code == 1)
    {
        std::cout << "Error with path Code: " << code << std::endl;
    }
    else if (code == 2)
    {
        std::cout << "Format does not exist Code: " << code << std::endl;
    }

    return code;
}
