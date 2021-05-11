#include <iostream>
#include <ostream>
#include <png.hpp>
#include <vector>
#include <random>
#include <list>
#include <time.h>

size_t count = 0;
void map_draw(png::image <png::rgb_pixel>& image, size_t height, size_t width, int** arr)
{
    png::rgb_pixel color0 = png::rgb_pixel(0, 0, 0);
    png::rgb_pixel color1 = png::rgb_pixel(0, 255, 0);
    png::rgb_pixel color2 = png::rgb_pixel(255, 0, 0);


    for (png::uint_32 i = 0; i != image.get_width(); i++)
    {
        for (png::uint_32 j = 0; j != image.get_height(); j++)
        {
            if (arr[i][j] == 0)
                image[i][j] = color0;
            if (arr[i][j] == 1)
                image[i][j] = color1;
            if (arr[i][j] == 2)
                image[i][j] = color2;
        }
    }
    image.write("out/palette" + std::to_string(count) + ".png");
    count++;
}

class Arr_Collect
{
public:
    void arr_build_by_line(int** arr, std::string chain, size_t height, size_t width)
    {
        size_t count = 0;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                arr[i][j] = chain[count];
                count++;
            }
        }
    }
    void arr_build_re_by_line(int** arr, std::string chain, size_t height, size_t width)
    {
        size_t count = 0;
        for (int i = width - 1; i >= 0; i--)
        {
            for (int j = height - 1; j >= 0; j--)
            {
                arr[i][j] = chain[count];
                count++;
            }
        }
    }
    void arr_build_by_colomn(int** arr, std::string chain, size_t height, size_t width)
    {
        size_t count = 0;
        for (int i = width - 1; i >= 0; i--)
        {
            for (int j = height - 1; j >= height; j--)
            {
                arr[j][i] = chain[count];
                count++;
            }
        }
    }
    void arr_build_re_by_colomn(int** arr, std::string chain, size_t height, size_t width)
    {
        size_t count = 0;
        for (int i = width - 1; i >= 0; i--)
        {
            for (int j = height - 1; j >= 0; j--)
            {
                arr[j][i] = chain[count];
                count++;
            }
        }
    }
    void arr_build(int** arr, std::string chain, size_t height, size_t width, size_t a)
    {
        if (a == 0)
            arr_build_by_line(arr, chain, height, width);
        else if (a == 1)
            arr_build_re_by_line(arr, chain, height, width);
        else if (a == 2)
            arr_build_by_colomn (arr, chain, height, width);
        else if (a == 3)
            arr_build_re_by_colomn(arr, chain, height, width);
    }

    int** arr_create(size_t x, size_t y)
    {
        int** arr = new int* [x];
        for (int i = 0; i < x; i++)
        {
            arr[i] = new int[y];
        }
        return arr;
    }
    void arr_fill(int** arr, size_t height, size_t width)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                arr[i][j] = rand() % 3;
            }
        }
    }
};
class Chain_Build {
public:
    std::string str_build_by_line(int** arr, size_t height, size_t width)
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
    std::string str_build_re_by_line(int** arr, size_t height, size_t width)
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
    std::string str_build_by_colomn(int** arr, size_t height, size_t width)
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
    std::string str_build_re_by_colomn(int** arr, size_t height, size_t width)
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
    std::string str_create(int** arr, size_t height, size_t width, size_t a)
    {
        std::string str = {};
        if (a == 0)
            str = str_build_by_line(arr, height, width);
        else if (a == 1)
            str = str_build_re_by_line(arr, height, width);
        else if (a == 2)
            str = str_build_by_colomn(arr, height, width);
        else if (a == 3)
            str = str_build_re_by_colomn(arr, height, width);
        return str;
    }

    std::list <std::string> chains_breaker(const std::string& chain, int p)
    {
        std::list <std::string> chains;
        int from = 0;
        for (int i = 0; i < chain.size(); i++) //деление на подстроки
        {
            if (rand()%10 < p || (i - from) >= 1  || i == chain.size() - 1)
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
    void apply_rule(std::list <std::string>& chains, int p)
    {
        for (auto it = chains.begin(); it != chains.end(); it++)
        {
            if (rand() % 10 < p)
            {
                if (*it == "01")
                    *it = "11";

                else if (*it == "12")
                    *it = "22"; 

                else if (*it == "2")
                    *it = "0";

                else if (*it == "1")
                    *it = "0";
            }
        }
    }
};

int main()
{

    srand(time(NULL));
    int p = 6; //вероятность в % * 10
    const int width = 10, height = 10;
    png::image<png::rgb_pixel> image(height, width);


    Arr_Collect arr_collect;
    int** arr = arr_collect.arr_create(height, width);
    arr_collect.arr_fill(arr, height, width);

    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << arr[i][j] + " ";
        }
        std::cout << std::endl;
    } 

    map_draw(image, height, width, arr); //первый кадр

    Chain_Build chain_build;
    int a = rand() % 4;
    std::string chain = chain_build.str_create(arr, height, width, a);
    //std::cout << chain << std::endl;
    std::list<std::string> chains = chain_build.chains_breaker(chain, p);
    chain_build.apply_rule(chains, p);
    
    chain = {};
    for (auto it = chains.begin(); it != chains.end(); it++)
    {
        chain = chain + *it;
        //std::cout << *it + " ";
    }
    std::cout << std::endl;
    //std::cout << chain;


    arr_collect.arr_build(arr, chain, height, width, a);
    
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << arr[i][j] + " ";
        }
        std::cout << std::endl;
    } 

    map_draw(image, height, width, arr); //второй кадр

}
