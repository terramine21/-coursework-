#include <iostream>
#include <png.hpp>
#include <random>
#include <list>
#include <time.h>
#include <vector>


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
			arr[j][i] = str[k];
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
			arr[j][i] = str[k];
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
double uniform01()
{
	return (double)rand() / (double)RAND_MAX;
}
void apply_rule(char* str, size_t chance, size_t size)
{
	double p = 0.02, q = 0.1, r = 0.01;
	for (size_t i = 0; i < size - 1;)
	{
		if (uniform01() < p && str[i] == '1' && str[i + 1] == '0')
		{
			str[i] = '0';
			str[i + 1] = '1';
			i += 2 + rand() % 3;
		}
		else if (uniform01() < p && str[i] == '0' && str[i + 1] == '1')
		{
			str[i] = '1';
			str[i + 1] = '0';
			i += 2 + rand() % 3;
		}
		else if (uniform01() < p && str[i] == '2' && str[i + 1] == '0')
		{
			str[i] = '0';
			str[i + 1] = '2';
			i += 2 + rand() % 3;
		}
		else if (uniform01() < p && str[i] == '0' && str[i + 1] == '2')
		{
			str[i] = '2';
			str[i + 1] = '0';
			i += 2 + rand() % 3;
		}
		else if (uniform01() < p && str[i] == '1' && str[i + 1] == '2')
		{
			str[i] = '2';
			str[i + 1] = '1';
			i += 2 + rand() % 3;
		}
		else if (uniform01() < p && str[i] == '2' && str[i + 1] == '1')
		{
			str[i] = '1';
			str[i + 1] = '2';
			i += 2 + rand() % 3;
		}
		else if (uniform01() < q && str[i] == '1' && str[i + 1] == '0')
		{
			str[i] = '1';
			str[i + 1] = '1';
			i += 2 + rand() % 3;
		}
		else if (uniform01() < q && str[i] == '1' && str[i + 1] == '2')
		{
			str[i] = '2';
			str[i + 1] = '2';
			i += 2 + rand() % 3;
		}
		else if (uniform01() < r && str[i] == '2')
		{
			str[i] = '0';
			i += 2 + rand() % 3;
		}
		else
			i++;
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
		image.write("out/frame" + std::to_string(frame) + ".png");
		std::cout << ++frame << " " << a << " " << b << std::endl;
	}
}
void frame_maker(char** matrix, char* str, size_t n, size_t m, size_t a)
{
	str_build(matrix, str, n, m, a);
	apply_rule(str, 50, n * m);
	arr_build(matrix, str, n, m, a);
}
int main()
{
	int n = 100, m = 100;
	srand(time(NULL));
	png::image<png::rgb_pixel> image(n, m);

	char** matrix = matrix_create(n, m);
	matrix_fill(matrix, n, m);

	int a = rand() % 4;
	char* str = str_create(n * m);

	frame_maker(matrix, str, n, m, a);
	for (int i = 0; i < 5000; i++)
	{
		a = rand() % 4;
		frame_maker(matrix, str, n, m, a);
		map_draw(image, n, m, matrix, i);
	}
}
