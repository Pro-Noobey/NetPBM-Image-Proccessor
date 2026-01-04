#include <iostream> // for I/O
#include <vector> // for storing pixel data
#include <string> // for I/O
#include <fstream> // file operations
#include <chrono> // for timing
#include <sstream> // for I/O

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


std::string clean(std::string path)
{
    std::ifstream file(path, std::ios::binary);

    std::string cleaned = "";
    std::string line;

    while (std::getline(file, line))
    {
        if (line[0] == '#')
        {
            continue;
        }
        else
        {
            cleaned += line;
            cleaned += "\n";
        }   
    }
    
    return cleaned;
}
std::vector<unsigned char> extract(unsigned char byte) {
    std::vector<unsigned char> bits;
    for (int i = 7; i >= 0; i--) {
        // Mask the specific bit with bitwise AND and right-shift to isolate it
        unsigned char bit = (byte >> i) & 1;  
        bits.push_back(bit);
    }
    return bits;
}
Image load_image_pbm(std::string path, bool binary)
{
    if (binary)
    {
        // NOTE: something broken
        std::ifstream file(path);

        std::string magicnumber;
        int width;
        int height;
        int maxval = 255;
        std::istringstream cleaned_file(clean(path));
        std::string line;
        
        cleaned_file >> magicnumber >> width >> height;

        std::cout << magicnumber << " " << width << "x" << height << "\n";

        cleaned_file.ignore();

        int image_size = width * height * 3;


        // Create a buffer to hold the entire file
        std::vector<char> buffer(image_size);

        // Read the file into the buffer
        file.read(buffer.data(), image_size);

        Image img{width, height, maxval ,PBM_BINARY};
        img.data.resize(width * height);
        int i = 0;
        for (const auto& byte : buffer)
        {
            std::vector<unsigned char> bits = extract(byte);
            for (const auto& bit : bits)
            {
                if (i == width * height)
                {
                    break;
                }
                if (bit == 1)
                {
                    img.data[i] = {static_cast<uint8_t>(255), static_cast<uint8_t>(255), static_cast<uint8_t>(255), static_cast<uint8_t>(255)};
                }
                else
                {
                    img.data[i] = {static_cast<uint8_t>(0), static_cast<uint8_t>(0), static_cast<uint8_t>(0), static_cast<uint8_t>(0)};
                }
                i++;
            }   
        }
        
        return img;
    }

    std::ifstream file(path);

    std::string magicnumber;
    int width;
    int height;
    int maxval = 255;

    int i = 1;
    std::string line;

    std::istringstream cleaned_file(clean(path));

    cleaned_file >> magicnumber >> width >> height;

    Image img{width, height, maxval, PBM_ASCII};
    img.data.resize(width * height);
    std::string b;
    for (int i = 0; i < width * height; i++) {
        cleaned_file >> b;
        if (std::stoi(b) == 1)
        {
            img.data[i] = {static_cast<uint8_t>(255), static_cast<uint8_t>(255), static_cast<uint8_t>(255), static_cast<uint8_t>(255)};
        }
        else
        {
            img.data[i] = {static_cast<uint8_t>(0), static_cast<uint8_t>(0), static_cast<uint8_t>(0), static_cast<uint8_t>(255)};
        }
    }
    
    return img;
}

Image load_image_pgm(std::string path, bool binary)
{
    if (binary)
    {
        std::ifstream file(path);

        std::string magicnumber;
        int width;
        int height;
        int maxval;

        std::istringstream cleaned_file(clean(path));

        cleaned_file >> magicnumber >> width >> height >> maxval;

        cleaned_file.ignore();

        Image img{width, height, maxval, PGM_BINARY};
        img.data.resize(width * height);

        uint8_t value;
        for (int i = 0; i < width * height; i++)
        {
            cleaned_file >> value;
            img.data[i] = {value, value, value, static_cast<uint8_t>(255)};
        }
        return img;
    }

    std::ifstream file(path);

    std::string magicnumber;
    int width;
    int height;
    int maxval;

    std::istringstream cleaned_file(clean(path));

    cleaned_file >> magicnumber >> width >> height >> maxval;

    cleaned_file.ignore();

    Image img{width, height, maxval, PGM_ASCII};
    img.data.resize(width * height);
    int value;
    for (int i = 0; i < width * height; i++)
    {
        cleaned_file >> value;
        img.data[i] = {static_cast<uint8_t>(value), static_cast<uint8_t>(value),  static_cast<uint8_t>(value)};
    }
    return img;
}

Image load_image_ppm(std::string path, bool binary)
{
    if (binary) {
        std::ifstream file(path, std::ios::binary);

        if (!file.is_open()) {
            return {};
        }

        std::string magicnnumber;
        int width;
        int height;
        int maxval;

        std::istringstream cleaned_file(clean(path));

        cleaned_file >> magicnnumber >> width >> height >> maxval;

        cleaned_file.ignore(); // Skip the newline after maxval

        Image img{width, height, maxval, PPM_BINARY};
        img.data.resize(width * height);

        cleaned_file.read(reinterpret_cast<char*>(img.data.data()), width * height * sizeof(Pixel));

        return img;
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        return {};
    }

    std::string magicnumber;
    int width;
    int height;
    int maxval;

    std::istringstream cleaned_file(clean(path));

    cleaned_file >> magicnumber >> width >> height >> maxval;

    cleaned_file.ignore();
    
    Image img{width, height, maxval, PPM_ASCII, std::vector<Pixel>(width * height)};
    img.data.resize(width * height);
    int r, g, b;
    for (int i = 0; i < width * height; i++) {
        cleaned_file >> r >> g >> b;
        img.data[i] = {static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b), static_cast<uint8_t>(255)};
    }

    return img;
}

int write_image_ppm(std::string path, Image img)
{
    if (img.TYPE == PPM_BINARY)
    {
        // very easy just append the raw bytes to the final string
    }
    std::string final_string = "P3\n# Made by the coolest Image Proccessor in Town!\n# The NetPBM Image Proccessor!!\n";
    std::string dimensions = img.WIDTH + " " + img.HEIGHT;
    final_string += dimensions;
    final_string += "\n";
    final_string += img.MAXVAL;
    final_string += "\n";

    for (const auto& pixel : img.data)
    {
        std::string r(1, static_cast<char>(pixel.r));
        std::string g(1, static_cast<char>(pixel.g));
        std::string b(1, static_cast<char>(pixel.b));
        final_string += r + " " + g + " " + b + "\n";
    }
    return 0;
}