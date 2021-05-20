#include <iostream>
#include <png.hpp>
#include <random>
#include <list>
#include <time.h>
#include <vector>

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
            switch (arr[i][j])
            {
            case 0:
                image[i][j] = color0;
                break;
            case 1:
                image[i][j] = color1;
                a++;
                break;
            case 2:

                image[i][j] = color2;
                b++;
                break;
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
    void arr_build_re_by_colomn(int** arr, const std::string& chain, size_t height, size_t width)
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
    void arr_build(int** arr, const std::string& chain, size_t height, size_t width, size_t a)
    {
        switch (a)
        {
        case 0:
            arr_build_by_line(arr, chain, height, width);
            break;
        case 1:
            arr_build_re_by_line(arr, chain, height, width);
            break;
        case 2:
            arr_build_by_colomn(arr, chain, height, width);
            break;
        case 3:
            arr_build_re_by_colomn(arr, chain, height, width);
            break;
        }
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
        switch (a)
        {
        case 0:
            return str_build_by_line(arr, height, width);
        case 1:
            return str_build_re_by_line(arr, height, width);

        case 2:
            return str_build_by_colomn(arr, height, width);

        case 3:
            return str_build_re_by_colomn(arr, height, width);

        default: return "";
        }
    }

    std::list <std::string> chains_breaker(const std::string& chain, int p)
    {
        std::list <std::string> chains;
        int from = 0;
        for (int i = 0; i < chain.size(); i++) //деление на подстроки
        {
            if (rand() % 10 < p || (i - from) >= 1 || i == chain.size() - 1)
            {
                std::string str1 = {};
                for (; from <= i; from++)
                    str1 += chain[from];
                chains.push_back(str1);
                if (chain.size() - i > 3)
                {
                    int step = rand() % 3;
                    i += step;
                    str1 = {};
                    for (; from <= i; from++)
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
            if (rnd < r)
                if (*it == "2")
                    *it = "0";
        }
    }
};



void f1()
{
    srand(time(NULL));
    int p = 5; //вероятность деления строки в % * 10
    const int width = 100, height = 100;
    png::image<png::rgb_pixel> image(height, width);

    Arr_Collect arr_collect;
    int** arr = arr_collect.arr_create(height, width);
    arr_collect.arr_fill(arr, height, width);

    map_draw(image, height, width, arr, 0); //first frame

    Chain_Build chain_build;


    for (int frame = 1; frame < 1000; frame++)
    {
        int a = rand() % 4;
        std::string chain = chain_build.str_create(arr, height, width, a);
        //std::cout << chain << std::endl;
        std::list<std::string> chains = chain_build.chains_breaker(chain, p);
        chain_build.apply_rule(chains);

        chain = {};
        for (auto it = chains.begin(); it != chains.end(); it++)
        {
            chain += *it;
        }
        arr_collect.arr_build(arr, chain, height, width, a);

        map_draw(image, height, width, arr, frame); //seconds frames

        for (int i = 0; i < height; i++)
            delete[] arr[i];
        delete[] arr;

    }
}


char** matrix_create(size_t y, size_t x)
{
    char** arr = new char* [x];
    for (int i = 0; i < x; i++)
        arr[i] = new char[y];

    return arr;
}
void matrix_fill(char** matrix, size_t y, size_t x)
{
    for (int i = 0; i < y; i++)
        for (int j = 0; j < x; j++)
            matrix[i][j] = (char)(rand() % 3 + 48);
}
void matrix_print(char** matrix, size_t y, size_t x)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void str_build_by_line(char** arr, char* str, size_t height, size_t width)
{
    size_t k = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            str[k] = arr[i][j];
            k++;        
        }
    }
}
void str_build_re_by_line(char** arr, char* str, size_t height, size_t width)
{
    size_t k = 0;

    for (int i = height - 1; i >= 0; i--)
    {
        for (int j = width - 1; j >= 0; j--)
        {
            str[k] = arr[i][j];
            k++;
        }
    }
}
void str_build_by_colomn(char** arr, char* str, size_t height, size_t width)
{
    size_t k = 0;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            str[k] = arr[j][i];
            k++;
        }
    }
}
void str_build_re_by_colomn(char** arr, char* str, size_t height, size_t width)
{
    size_t k = 0;

    for (int i = width - 1; i >= 0; i--)
    {
        for (int j = height - 1; j >= 0; j--)
        {
            str[k] = arr[j][i];
            k++;
        }
    }
}
void str_build(char** arr, char* str, size_t height, size_t width, size_t a)
{
    switch (a)
    {
    case 0:
        str_build_by_line(arr, str, height, width);
        break;
    case 1:
        str_build_re_by_line(arr, str, height, width);
        break;
    case 2:
        str_build_by_colomn(arr, str, height, width);
        break;

    case 3:
        str_build_re_by_colomn(arr, str, height, width);
    }
}
char* str_create(size_t size)
{
    char* str = new char[size];
    return str;
}


void arr_build_by_line(char** arr, char* str, size_t height, size_t width)
{
    size_t k = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = str[k];
            k++;
        }
    }
}
void arr_build_re_by_line(char** arr, char* str, size_t height, size_t width)
{
    size_t k = 0;
    for (int i = width - 1; i >= 0; i--)
    {
        for (int j = height - 1; j >= 0; j--)
        {
            arr[i][j] = str[k];
            k++;
        }
    }
}
void arr_build_by_colomn(char** arr, char* str, size_t height, size_t width)
{
    size_t k = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = str[k];
            k++;
        }
    }
}
void arr_build_re_by_colomn(char** arr, char* str, size_t height, size_t width)
{
    size_t k = 0;
    for (int i = width - 1; i >= 0; i--)
    {
        for (int j = height - 1; j >= 0; j--)
        {
            arr[i][j] = str[k];
            k++;
        }
    }
}
void arr_build(char** arr, char* str, size_t height, size_t width, size_t a)
{
    switch (a)
    {
    case 0:
        arr_build_by_line(arr, str, height, width);
        break;
    case 1:
        arr_build_re_by_line(arr, str, height, width);
        break;
    case 2:
        arr_build_by_colomn(arr, str, height, width);
        break;
    case 3:
        arr_build_re_by_colomn(arr, str, height, width);
        break;
    }
}

void apply_rule(char* str, size_t chance, size_t size)
{
    int p = 2, q = 10, r = 1;
    for (size_t i = 0; i < size; i++)
    {
        size_t split = rand() % 100;
        size_t rnd = rand() % 100;
        if (split < chance)
            split = 1;
        else split = 0;

        if (split == 1 && i + 2 < sizeof(str))
        {
            if (rnd < p)
            {
                if (str[i] == '1' && str[i + 1] == '0')
                {
                    str[i] = '0'; str[i + 1] = '1';
                }
                else if (str[i] == '0' && str[i + 1] == '1')
                {
                    str[i] = '1'; str[i + 1] = '0';
                }
                else if (str[i] == '2' && str[i + 1] == '0')
                {
                    str[i] = '0'; str[i + 1] = '2';
                }
                else if (str[i] == '0' && str[i + 1] == '2')
                {
                    str[i] = '2'; str[i + 1] = '0';
                }
                else if (str[i] == '1' && str[i + 1] == '2')
                {
                    str[i] = '2'; str[i + 1] = '1';
                }
                else if (str[i] == '2' && str[i + 1] == '1')
                {
                    str[i] = '1'; str[i + 1] = '2';
                }
            }
            if (rnd < q)
            {
                if (str[i] == '1' && str[i + 1] == '0')
                {
                    str[i] = '1'; str[i + 1] = '1';
                }
                else if (str[i] == '1' && str[i + 1] == '2')
                {
                    str[i] = '2'; str[i + 1] = '2';
                }
            }
        }
        else if (split == 0 && rnd < r && str[i] == '2' && i + 2 < sizeof(str))
        {
            str[i] = '0';
        }
    }
}
void str_print(char* str, size_t size)
{
    for (size_t i = 0; i < size; i++)
        std::cout << str[i] << " ";
    std::cout << std::endl;
}
void map_draw(png::image <png::rgb_pixel>& image, size_t height, size_t width, char** arr, size_t frame)
{
    png::rgb_pixel color0 = png::rgb_pixel(0, 0, 0);
    png::rgb_pixel color1 = png::rgb_pixel(0, 255, 0);
    png::rgb_pixel color2 = png::rgb_pixel(255, 0, 0);
    int a = 0, b = 0; //для счёт жертв и хищников

    for (png::uint_32 i = 0; i != image.get_width(); i++)
    {
        for (png::uint_32 j = 0; j != image.get_height(); j++)
        {
            switch (arr[i][j])
            {
            case'0':
                image[i][j] = color0;
                break;
            case '1':
                image[i][j] = color1;
                a++;
                break;
            case '2':
                image[i][j] = color2;
                b++;
                break;
            }
        }
    }
    if (frame % 10 == 0)
    {
        image.write("out/frame" + std::to_string(frame) + ".png"); std::cout << a << " " << b << std::endl;
    }
}
int main()
{
    int n = 1000, m = 1000;
    srand(time(NULL));
    png::image<png::rgb_pixel> image(n, m);

    char** matrix = matrix_create(n, m);
    matrix_fill(matrix, n, m);
    //matrix_print(matrix, n, m);

    int a = rand() % 4;
    char* str = str_create(n * m);
    str_build(matrix, str, n, m, a);
    apply_rule(str, 50, n * m);
    arr_build(matrix, str, n, m, a);

    for (int i = 0; i < 5000; i++)
    {
        a = rand() % 4;
        str_build(matrix, str, n, m, a);
        apply_rule(str, 50, n * m);
        arr_build(matrix, str, n, m, a);
        map_draw(image, n, m, matrix, i);
    }



}
