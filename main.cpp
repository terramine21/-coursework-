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
        for (int i = 0; i < chain.size(); i++) //первое деление
        {
            if (rand() % 2 + 1 == p || i == chain.size() - 1)
            {
                std::string str1 = {};
                for (; from <= i; from++)
                {
                    str1 += chain[from];
                }
                chains.push_back(str1);
            }
        }

        bool level = false;
        while(!level)
        for (std::string it : chains) //деление второе
        {
            int count = 0; //костыль
            level = true;
            from = 0;
            if (it.size() > 2) {
                level = false;
                for (int i = 0; i < it.size(); i++)
                {
                    if (rand() % 2 + 1 == p || i == chain.size() - 1)
                    {
                        std::string str1 = {};
                        for (; from <= i; from++)
                        {
                            str1 += it[from];
                        }
                        std::list <std::string> ::iterator iti;
                        std::advance(iti, count);
                        chains.insert(iti, str1); //где-то проблема
                    }
                }
            }
        }

        return chains;
    }

    std::list <std::string> apply_rule(std::list <std::string> chains, int p)
    {
         for (std::string i : chains)
        {
             if (rand() + 1 == p)
             {
                 if (i == "01")
                     i = "11";

                 if (i == "12")
                     i = "22";

                 if (i == "2")
                     i = "0";

                 if (i == "1")
                     i = "0";
             }
        }
         return chains;
    }
};

int main()
{

    const int width = 3, height = 3;
    int **arr = arr_build(width, height);

    int k = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            k = k + 1;
            arr[i][j] = k;
        }
    }
    Chain_Build chain_build;
    std::string chain = chain_build.by_line(arr, 3, 3);
    std::cout<< chain << std::endl;

    srand(21234);
    int p = 2; //вероятность
    std::list <std::string> chains = chain_build.chains_breaker(chain, p);
    
    chain = {};
    for (std::string i : chains)
    {
        std::cout << i << std::endl;
        chain += i;
    }
    std::cout << chain << std::endl;




    std::cout << "_______________" << std::endl;

    std::list <std::string> keke = { "11", "33", "55" };
    std::list <std::string> ::iterator it = keke.begin();
    std::advance(it, 1);
    keke.insert(it, "22");
    std::advance(it, -1);
    std::string kek = *it;
    std::cout << kek << std::endl;


}
