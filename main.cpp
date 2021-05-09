#include <iostream>
#include <ostream>
#include <png.hpp>
#include <vector>
#include <random>
#include <list>

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

int** arr_build(size_t x, size_t y)
{
    int** arr = new int* [x];
    for (int i = 0; i < x; i++)
    {
        arr[i] = new int[y];
    }
    return arr;
}


class Chain_Build {
public:
    std::string by_line(int** arr, size_t width, size_t height)
    {
        std::string str = {};

        for (int x = 0; x < height; x++)
        {
            for (int y = 0; y < width; y++)
            {
                str += std::to_string(arr[x][y]);
            }
        }
        return str;
    }

    std::string re_by_line(int** arr, size_t width, size_t height)
    {
        std::string str = {};

        for (int x = height - 1; x >= 0; x--)
        {
            for (int y = width - 1; y >= 0; y--)
            {
                str += std::to_string(arr[x][y]);
            }
        }
        return str;
    }

    std::string by_colomn(int** arr, size_t width, size_t height)
    {
        std::string str = {};

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                str += std::to_string(arr[y][x]);
            }
        }
        return str;
    }

    std::string re_by_colomn(int** arr, size_t width, size_t height)
    {
        std::string str = {};

        for (int x = width - 1; x >= 0; x--)
        {
            for (int y = height - 1; y >= 0; y--)
            {
                str += std::to_string(arr[y][x]);
            }
        }
        return str;
    }
    
    std::list <std::string> chains_breaker(std:: string chain, int p)
    {
        std::list <std::string> chains;
        int from = 0;
        for (int i = 0; i < chain.size(); i++) //деление на подстроки
        {
            if (rand() % 2 + 1 == p || i == chain.size() - 1 || (i - from) >= 1)
            {
                std::string str1 = {};
                for (; from <= i; from++)
                {
                    str1 += chain[from];
                }
                chains.push_back(str1);
            }
        }
        return chains;
    }

    std::list <std::string> apply_rule(std::list <std::string> chains, int p)
    {
         for (auto it = chains.begin(); it != chains.end(); it++)
        {
             if (rand() % 2 + 1 == p)
             {
                 if (*it == "01")
                     *it = "11";

                 if (*it == "12")
                     *it = "22";

                 if (*it == "2")
                     *it = "0";

                 if (*it == "1")
                     *it = "0";
             }
        }
         return chains;
    }
};

int main()
{
    srand(2489);
    int p = 2; //вероятность

    const int width = 100, height = 100;
    int **arr = arr_build(width, height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = rand() % 3;
        }
    }
    Chain_Build chain_build;
    std::string chain = chain_build.by_line(arr, width, height);
    std::cout<< chain << std::endl;
    std::cout << "_____________________" << std::endl;
    
    std::list <std::string> chains = chain_build.chains_breaker(chain, p);

    for (std::string i : chains)
    {
        std::cout << i << std::endl;
    }
    std::cout << "_____________________" << std::endl;
    chain = {};
    chains = chain_build.apply_rule(chains, p);
    for (std::string i : chains)
    {
        std::cout << i << std::endl;
        chain += i;
    }
    std::cout << "_____________________" << std::endl;

    std::cout << chain << std::endl;

}
