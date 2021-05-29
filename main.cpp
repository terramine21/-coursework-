#include <iostream>
#include <png.hpp>
#include <random>
#include <time.h>
#include <vector>


struct Matrix
{
	size_t Height,
		Width;
	char** Arr;
	char* Str = {};
};
struct Image
{
	size_t Frames,
		Scale;
	png::image<png::rgb_pixel> image;
};

class Marksys
{
public:
	Matrix mat;
	Image im;

	void set_size(size_t n, size_t m)
	{
		mat.Height = n;
		mat.Width = m;
	}
	void set_scale(size_t scale)
	{
		im.Scale = scale;
	}
	void set_image()
	{
		im.image = png::image<png::rgb_pixel> (mat.Width * im.Scale, mat.Height * im.Scale);
	}

	void matrix_create()
	{
		char** Arr = new char* [mat.Height];
		for (int i = 0; i < mat.Height; i++)
			Arr[i] = new char[mat.Width];

		mat.Arr = Arr;
	}
	void matrix_fill()
	{
		for (int i = 0; i < mat.Height; i++)
			for (int j = 0; j < mat.Width; j++)
				mat.Arr[i][j] = (char)(rand() % 3 + 48);
	}

	void str_build_by_line()
	{
		size_t k = 0;
		for (int i = 0; i < mat.Height; i++)
		{
			for (int j = 0; j < mat.Width; j++)
			{
				mat.Str[k] = mat.Arr[i][j];
				k++;
			}
		}
	}
	void str_build_re_by_line()
	{
		size_t k = 0;

		for (int i = mat.Height - 1; i >= 0; i--)
		{
			for (int j = mat.Width - 1; j >= 0; j--)
			{
				mat.Str[k] = mat.Arr[i][j];
				k++;
			}
		}
	}
	void str_build_by_colomn()
	{
		size_t k = 0;

		for (int i = 0; i < mat.Width; i++)
		{
			for (int j = 0; j < mat.Height; j++)
			{
				mat.Str[k] = mat.Arr[j][i];
				k++;
			}
		}
	}
	void str_build_re_by_colomn()
	{
		size_t k = 0;

		for (int i = mat.Width - 1; i >= 0; i--)
		{
			for (int j = mat.Height - 1; j >= 0; j--)
			{
				mat.Str[k] = mat.Arr[j][i];
				k++;
			}
		}
	}
	void str_build(size_t a)
	{
		switch (a)
		{
		case 0:
			str_build_by_line();
			break;
		case 1:
			str_build_re_by_line();
			break;
		case 2:
			str_build_by_colomn();
			break;

		case 3:
			str_build_re_by_colomn();
		}
	}
	void str_create()
	{
		mat.Str = new char[mat.Height * mat.Width];
	}

	void arr_build_by_line()
	{
		size_t k = 0;
		for (int i = 0; i < mat.Height; i++)
		{
			for (int j = 0; j < mat.Width; j++)
			{
				mat.Arr[i][j] = mat.Str[k];
				k++;
			}
		}
	}
	void arr_build_re_by_line()
	{
		size_t k = 0;
		for (int i = mat.Height - 1; i >= 0; i--)
		{
			for (int j = mat.Width - 1; j >= 0; j--)
			{
				mat.Arr[i][j] = mat.Str[k];
				k++;
			}
		}
	}
	void arr_build_by_colomn()
	{
		size_t k = 0;
		for (int i = 0; i < mat.Width; i++)
		{
			for (int j = 0; j < mat.Height; j++)
			{
				mat.Arr[j][i] = mat.Str[k];
				k++;
			}
		}
	}
	void arr_build_re_by_colomn()
	{
		size_t k = 0;
		for (int i = mat.Width - 1; i >= 0; i--)
		{
			for (int j = mat.Height - 1; j >= 0; j--)
			{
				mat.Arr[j][i] = mat.Str[k];
				k++;
			}
		}
	}
	void arr_build(size_t a)
	{
		switch (a)
		{
		case 0:
			arr_build_by_line();
			break;
		case 1:
			arr_build_re_by_line();
			break;
		case 2:
			arr_build_by_colomn();
			break;
		case 3:
			arr_build_re_by_colomn();
			break;
		}
	}
	double uniform01()
	{
		return (double)rand() / (double)RAND_MAX;
	}
	void apply_rule()
	{
		double p = 0.02, q = 0.1, r = 0.01;
		for (size_t i = 0; i < mat.Height * mat.Width - 1;)
		{
			if (uniform01() < p && mat.Str[i] == '1' && mat.Str[i + 1] == '0')
			{
				mat.Str[i] = '0';
				mat.Str[i + 1] = '1';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < p && mat.Str[i] == '0' && mat.Str[i + 1] == '1')
			{
				mat.Str[i] = '1';
				mat.Str[i + 1] = '0';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < p && mat.Str[i] == '2' && mat.Str[i + 1] == '0')
			{
				mat.Str[i] = '0';
				mat.Str[i + 1] = '2';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < p && mat.Str[i] == '0' && mat.Str[i + 1] == '2')
			{
				mat.Str[i] = '2';
				mat.Str[i + 1] = '0';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < p && mat.Str[i] == '1' && mat.Str[i + 1] == '2')
			{
				mat.Str[i] = '2';
				mat.Str[i + 1] = '1';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < p && mat.Str[i] == '2' && mat.Str[i + 1] == '1')
			{
				mat.Str[i] = '1';
				mat.Str[i + 1] = '2';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < q && mat.Str[i] == '1' && mat.Str[i + 1] == '0')
			{
				mat.Str[i] = '1';
				mat.Str[i + 1] = '1';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < q && mat.Str[i] == '1' && mat.Str[i + 1] == '2')
			{
				mat.Str[i] = '2';
				mat.Str[i + 1] = '2';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < r && mat.Str[i] == '2')
			{
				mat.Str[i] = '0';
				i += 2 + rand() % 3;
			}
			else
				i++;
		}
	}

	void map_draw(int frame)
	{
		int a = 0, b = 0; //prey predator
		

		for (size_t i = 0; i < mat.Height * im.Scale; i++)
		{
			for (size_t j = 0; j < mat.Width * im.Scale; j++)
			{
				switch (mat.Arr[i / im.Scale][j / im.Scale])
				{
				case'0':
					im.image[i][j] = png::rgb_pixel(0, 0, 0);
					break;
				case '1':
					im.image[i][j] = png::rgb_pixel(0, 255, 0);
					a++;
					break;
				case '2':
					im.image[i][j] = png::rgb_pixel(255, 0, 0);
					b++;
					break;
				}
			}
		}
		
		if (frame % 10 == 0)
		{
			im.image.write("out/frame" + std::to_string(frame) + ".png");
			std::cout << frame << " " << a / im.Scale << " " << b/im.Scale << std::endl;
		}
	}

	void frame_maker(size_t a)
	{
		str_build(a);
		apply_rule();
		arr_build(a);
	}
	void set_frames(size_t frames)
	{
		im.Frames = frames;
	}
	size_t get_frames()
	{
		return im.Frames;
	}
	Marksys()
	{
	}
	~Marksys()
	{
		delete[] mat.Str;
		for (int i = 0; i < mat.Height; i++)
			delete[] mat.Arr[i];
		delete[] mat.Arr;
	}
	void dflt()
	{
		mat.Height = 50;
		mat.Width = 25;
		im.Frames = 1000;
		im.Scale = 2;
	}
};

bool is_number(const std::string& s)
{
	return !s.empty() && (s.find_first_not_of("0123456789") == s.npos) && std::stoi(s) > 0;
}
void menu(int argc, char** argv, class Marksys& marksys) //добавить обработку ошибок
{
	marksys.dflt();
	system("cls"); // очищаем экран
	std::cout << "There are " << argc - 1 << " arguments:\n";
	std::cout << ">";
	marksys.dflt();
	if (argc == 1)
	{
		std::cout << "Enter -help if you don't know what to do" << std::endl;
		exit(1);
	}
	else
	{
		size_t arg = 0;
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "--h") == 0)
			{
				std::cout <<
					"-help or --h: list of commands + example \n" <<
					"-setsize: set matrix size n x m. -setsize 50 50 \n" <<
					"-setscale: set  pixel size. -setscale 2 \n" <<
					"-default: default settings . -default \n" <<
					"-countframes: set number of frames. -countframes 1000 \n";
				exit(1);
			}
		}
		for (int i = 1; i < argc; i++)
		{
			arg++;
			if (strcmp(argv[i], "-setsize") == 0)
			{
				if (arg+3 > argc || !is_number(argv[i+1]) || !is_number(argv[i+2]))
				{
					std::cout << "Invalid size \n";
					exit(1);
				}
				marksys.set_size(std::atoi(argv[i + 1]), atoi(argv[i + 2]));
				i += 2;
			}
			else if (strcmp(argv[i], "-setscale") == 0)
			{
				if (arg + 2 > argc || !is_number(argv[i + 1]))
				{
					std::cout << "Invalid scale \n";
					exit(1);
				}
				marksys.set_scale(std::atoi(argv[i + 1]));
				i += 1;
			}
			else if (strcmp(argv[i], "-countframes") == 0)
			{
				if (arg + 2 > argc || !is_number(argv[i + 1]))
				{
					std::cout << "Invalid count \n";
					exit(1);
				}
				marksys.set_frames(std::atoi(argv[i + 1]));
				i += 1;
			}
			else if (strcmp(argv[i], "-default") == 0)
			{
				marksys.dflt();
			}
			else
			{
				std::cout << "unknown command " << "\"" << argv[i] << "\"";
				exit(1);
			}
		}
	}
	marksys.set_image();
}

int main(int argc, char** argv)
{
	srand(time(NULL));

	Marksys marksys;

	menu(argc, argv, marksys);

	marksys.matrix_create();
	marksys.matrix_fill();
	int a = rand() % 4;
	marksys.str_create();

	for (int i = 0; i < marksys.get_frames(); i++)
	{
		a = rand() % 4;
		marksys.frame_maker(a);
		marksys.map_draw(i);

	}
}
