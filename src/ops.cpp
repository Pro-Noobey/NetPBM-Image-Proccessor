#include <vector>
#include <chrono> // cuz uint8_t wont work without it for some reason
#include <stdexcept>
#include <omp.h>

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

auto sum(std::vector<int> sum_of)
{
    int final;

    for (const auto& num : sum_of)
    {
        final += num;
    }
    return final;
}

float average(std::vector<int> to_average)
{
    return sum(to_average) / to_average.capacity();
}

auto find_neighbor_indices(int kernel_size, int x, int y)
{
    std::vector<std::vector<int>> neighbors;

    for (int i = 0; i < kernel_size; i++)
    {
        std::vector<std::vector<int>> neighbor = {
            {x+i, y+i},
            {x-i, y-i},
            {x+i, y-i},
            {x-i, y+i},
            {x+i, y},
            {x-i, y},
            {x, y+i},
            {x, y-i}
        };

        neighbors.insert(neighbors.end(), neighbor.begin(), neighbor.end());
    }
    return neighbors;
}

Image blur(Image src_img, int passes, int kernel_size)
{
    int i = 0;
    for (int pass = 0; pass < passes; pass++)
    {
        #pragma omp parallel for
        for (int i = 0; i < src_img.data.size(); i++) 
        {
            int x = i % src_img.WIDTH;
            int y = i / src_img.WIDTH;
            auto neighbors = find_neighbor_indices(kernel_size, x, y);

            int r;
            int g;
            int b;

            std::vector<int> to_average_r = {static_cast<int>(src_img.data[i].r)};
            std::vector<int> to_average_g = {static_cast<int>(src_img.data[i].g)};
            std::vector<int> to_average_b = {static_cast<int>(src_img.data[i].b)};

            // Looping through neighbors
            for (const auto& nb : neighbors)
            {
                try
                {
                    r = static_cast<int>(src_img.data[nb[0], nb[1]].r);
                    g = static_cast<int>(src_img.data[nb[0], nb[1]].g);
                    b = static_cast<int>(src_img.data[nb[0], nb[1]].b);

                    to_average_r.push_back(r);
                    to_average_g.push_back(g);
                    to_average_b.push_back(b);
                }
                catch(const std::exception& e)
                {
                    continue;
                }
            }

            int averaged_r = average(to_average_r);
            int averaged_g = average(to_average_g);
            int averaged_b = average(to_average_b);

            src_img.data[i].r = static_cast<uint8_t>(averaged_r);
            src_img.data[i].g = static_cast<uint8_t>(averaged_g);
            src_img.data[i].b = static_cast<uint8_t>(averaged_b);
        }
    }
    return src_img;
}