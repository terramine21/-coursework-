#include <iostream>
#include <ostream>
#include <png.hpp>
#include <vector>

void map_draw(png::image <png::rgb_pixel> &image, size_t width, size_t height)
{
    for (png::uint_32 i = 0; i != image.get_width(); i++)
    {
        for (png::uint_32 j = 0; j != image.get_height(); j++)
        {
            std::vector <png::uint_32> color = { 100, 100, 100 };
            image[i][j] = png::rgb_pixel(color[0], color[1], color[2]); //нужно записать одной переменной
        }
    }
    image.write("out/palette1.png");
}


struct pixel //3 заготовленных цвета и типа
{
    size_t pixel_type; 


};

class Chain_Build {
public:
    std::string by_line(png::image <png::rgb_pixel>& image, size_t width, size_t height)
    {
        std::string str = {};

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                str += std::to_string(x) + std::to_string(y);
            }
        }
        return str;
    }

    std::string re_by_line(png::image <png::rgb_pixel>& image, size_t width, size_t height)
    {
        std::string str = {};

        for (int y = height - 1; y >= 0; y--)
        {
            for (int x = width - 1; x >= 0; x--)
            {
                str += std::to_string(x) + std::to_string(y);
            }
        }
        return str;
    }

    std::string by_colomn(png::image <png::rgb_pixel>& image, size_t width, size_t height)
    {
        std::string str = {};

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                str += std::to_string(x) + std::to_string(y);
            }
        }
        return str;
    }

    std::string re_by_colomn(png::image <png::rgb_pixel>& image, size_t width, size_t height)
    {
        std::string str = {};

        for (int x = width - 1; x >= 0; x--)
        {
            for (int y = height - 1; y >= 0; y--)
            {
                str += std::to_string(x) + std::to_string(y);
            }
        }
        return str;
    }
};


int main()
{
    size_t width = 3, height = 3;
    png::image< png::rgb_pixel > image(width, height);
    
    map_draw(image, width, height);

    Chain_Build chain_build;

    std::string kek = chain_build.by_line(image, width, height);
    std::cout << kek << std::endl;

    kek = chain_build.re_by_line(image, width, height);
    std::cout << kek << std::endl;

    kek = chain_build.by_colomn(image, width, height);
    std::cout << kek << std::endl;

    kek = chain_build.re_by_colomn(image, width, height);
    std::cout << kek << std::endl;

    
}
