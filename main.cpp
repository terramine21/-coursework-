#include <iostream>
#include <png.hpp>
#include <random>
#include <list>
#include <time.h>

void map_draw(png::image <png::rgb_pixel>& image, size_t height, size_t width, int** arr, size_t frame)
{
    png::rgb_pixel color0 = png::rgb_pixel(0, 0, 0);
    png::rgb_pixel color1 = png::rgb_pixel(0, 255, 0);
    png::rgb_pixel color2 = png::rgb_pixel(255, 0, 0);
    int a = 0, b = 0;

    for (png::uint_32 i = 0; i != image.get_width(); i++)
    {
        for (png::uint_32 j = 0; j != image.get_height(); j++)
        {
            if (arr[i][j] == 0)
                image[i][j] = color0;
            if (arr[i][j] == 1)
            {
                image[i][j] = color1;
                a++;
            }
            if (arr[i][j] == 2)
            {
                image[i][j] = color2;
                b++;
            }
            
        }
    }
    if (frame % 10 == 0)
    {
        image.write("out/frame" + std::to_string(frame) + ".png"); std::cout << a << " " << b << std::endl;
    }
}

class Arr_Collect
{
public:
    void arr_build_by_line(int** arr, const std::string& chain, size_t height, size_t width)
    {
        size_t count = 0;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int KOSTIL = (int)chain[count] - 48;
                arr[i][j] = KOSTIL;
                count++;
            }
        }
    }
    void arr_build_re_by_line(int** arr, const std::string& chain, size_t height, size_t width)
    {
        size_t count = 0;
        for (int i = width - 1; i >= 0; i--)
        {
            for (int j = height - 1; j >= 0; j--)
            {
                int KOSTIL = (int)chain[count] - 48;
                arr[i][j] = KOSTIL;
                count++;
            }
        }
    }
    void arr_build_by_colomn(int** arr, const std::string& chain, size_t height, size_t width)
    {
        size_t count = 0;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int KOSTIL = (int)chain[count] - 48;
                arr[j][i] = KOSTIL;
                count++;
            }
        }
    }
    void arr_build_re_by_colomn(int** arr,const std::string& chain, size_t height, size_t width)
    {
        size_t count = 0;
        for (int i = width - 1; i >= 0; i--)
        {
            for (int j = height - 1; j >= 0; j--)
            {
                int KOSTIL = (int)chain[count] - 48;
                arr[j][i] = KOSTIL;
                count++;
            }
        }
    }
    void arr_build(int** arr,const std::string& chain, size_t height, size_t width, size_t a)
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

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                str += std::to_string(arr[i][j]);
            }
        }
        return str;
    }
    std::string str_build_re_by_line(int** arr, size_t height, size_t width)
    {
        std::string str = {};

        for (int i = height - 1; i >= 0; i--)
        {
            for (int j = width - 1; j >= 0; j--)
            {
                str += std::to_string(arr[i][j]);
            }
        }
        return str;
    }
    std::string str_build_by_colomn(int** arr, size_t height, size_t width)
    {
        std::string str = {};

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                str += std::to_string(arr[j][i]);
            }
        }
        return str;
    }
    std::string str_build_re_by_colomn(int** arr, size_t height, size_t width)
    {
        std::string str = {};

        for (int i = height - 1; i >= 0; i--)
        {
            for (int j = width - 1; j >= 0; j--)
            {
                str += std::to_string(arr[j][i]);
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
                    str1 += chain[from];
                chains.push_back(str1);
                if(chain.size() - i > 3)
                {
                    int step = rand() % 3;
                    i += step;
                    str1 = {};
                    for(; from <= i; from++)
                        str1 += chain[from];
                    chains.push_back(str1);
                }
            }
        }
        return chains;
    }
    void apply_rule(std::list <std::string>& chains)
    { //0 - nothing, 1 - grass, 2 - cow
        for (auto it = chains.begin(); it != chains.end(); it++)
        {
            int p = 2, q = 10, r = 1, rnd = rand() % 100;
            if (rnd < p)
            {
                if (*it == "10")
                    *it = "01";
                else if (*it == "01")
                    *it = "10";
                else if (*it == "20")
                    *it = "02";
                else if (*it == "02")
                    *it = "20";
                else if (*it == "12")
                    *it = "21";
                else if (*it == "21")
                    *it = "12";
            }
            if (rnd < q)
            {
                if (*it == "10")
                    *it = "11";
                else if (*it == "12")
                    *it = "22";
            }
            if(rnd < r)
            if (*it == "2")
                *it = "0";
        }
    }
};

int main()
{
    srand(time(NULL));
    int p = 5; //вероятность деления строки в % * 10 //нету в презентаии
    const int width = 100, height = 100;
    png::image<png::rgb_pixel> image(height, width);
    
    Arr_Collect arr_collect;
    int** arr = arr_collect.arr_create(height, width);
    arr_collect.arr_fill(arr, height, width);

    map_draw(image, height, width, arr, 0); //first frame

    Chain_Build chain_build;

    
    for (int frame = 1; frame < 1000  ; frame++)
    {
        int a = rand() % 4;
        std::string chain = chain_build.str_create(arr, height, width, a);
        //std::cout << chain << std::endl;
        std::list<std::string> chains = chain_build.chains_breaker(chain, p);
        chain_build.apply_rule(chains);

        chain = {};
        for (auto it = chains.begin(); it != chains.end(); it++)
        {
            chain = chain + *it;
        }
        arr_collect.arr_build(arr, chain, height, width, a);

        map_draw(image, height, width, arr, frame); //второй кадр
    }

    for (int i = 0; i < height; i++)
        delete[] arr[i];
    delete[] arr;

}
