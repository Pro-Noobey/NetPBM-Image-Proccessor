#include <vector>
#include <cstdint> // cuz uint8_t wont work without it for some reason
#include <stdexcept>
#include <omp.h>
#include "image.h"

auto sum(const std::vector<int>& sum_of)
{
    int final = 0;

    for (const auto& num : sum_of)
    {
        final += num;
    }
    return final;
}

float average(const std::vector<int>& to_average)
{
    return static_cast<float>(sum(to_average)) / static_cast<float>(to_average.size());
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

std::vector<std::vector<std::vector<int>>> getchunks(
    int x /* width of the image */, 
    int y /* height of the image */, 
    int chunk_size /*chunk size aka just the kernel size*/
)
{
    std::vector<std::vector<std::vector<int>>> chunks
}

/*
A chunk is structured as follows:
[
    [
        [x, y],
        [x, y],
        [x, y]
    ],
    [
        [x, y],
        [x, y],
        [x, y]
    ]
]

The blur function must iterate through each chunk and find all the pixel values in the chunk as neighbors ONCE,
then loop through each pixel in the chunk, average them together with itself
*/

Image blur(Image src_img, int passes, int kernel_size)
{
    Image new_img{src_img.WIDTH, src_img.HEIGHT, src_img.MAXVAL, src_img.TYPE};
    new_img.data.resize(src_img.data.size());

    auto chunks = getchunks(src_img.WIDTH, src_img.HEIGHT, kernel_size);
    for (int pass = 0; pass < passes; pass++)
    {
        // first we will do single thread to test if it works
        for (const auto& chunk : chunks)
        {
            
            for (const auto&pixel : chunk)
            {
                int x = pixel[0];
                int y = pixel[1];

                std::vector<int> to_average_r = {static_cast<int>(src_img.data[y * src_img.WIDTH + x].r)};
                std::vector<int> to_average_g = {static_cast<int>(src_img.data[y * src_img.WIDTH + x].g)};
                std::vector<int> to_average_b = {static_cast<int>(src_img.data[y * src_img.WIDTH + x].b)};

                // Looping through neighbors with bounds checking
                for (const auto& nb : neighbors)
                {
                    int nx = nb[0];
                    int ny = nb[1];
                    if (nx < 0 || ny < 0 || nx >= src_img.WIDTH || ny >= src_img.HEIGHT) continue;

                    int idx = ny * src_img.WIDTH + nx;
                    int r = static_cast<int>(src_img.data[idx].r);
                    int g = static_cast<int>(src_img.data[idx].g);
                    int b = static_cast<int>(src_img.data[idx].b);

                    to_average_r.push_back(r);
                    to_average_g.push_back(g);
                    to_average_b.push_back(b);
                }

                int averaged_r = static_cast<int>(average(to_average_r));
                int averaged_g = static_cast<int>(average(to_average_g));
                int averaged_b = static_cast<int>(average(to_average_b));

                new_img.data[y * new_img.WIDTH + x].r = static_cast<uint8_t>(averaged_r);
                new_img.data[y * new_img.WIDTH + x].g = static_cast<uint8_t>(averaged_g);
                new_img.data[y * new_img.WIDTH + x].b = static_cast<uint8_t>(averaged_b);
            }
        }
    }

    return new_img;
}