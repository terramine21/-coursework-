#include <iostream>
#include <png.hpp>
#include <random>
#include <time.h>
#include <vector>


class Matrix
{
	char** Arr = nullptr;
	size_t N = 5, M = 5;
public:
	Matrix(size_t n, size_t m);
	Matrix();
	~Matrix();
	void fill();


	Matrix(size_t n, size_t m)
	{
		N = n;
		M = m;
		char** arr = new char* [n];
		for (int i = 0; i < n; i++)
			arr[i] = new char[m];
		Arr = arr;
		fill();
	}
	Matrix()
	{
		char** arr = new char* [N];
		for (int i = 0; i < N; i++)
			arr[i] = new char[M];
		Arr = arr;
		fill();
	}
	~Matrix()
	{
		for (int i = 0; i < N; i++)
			delete[] Arr[i]; 
		delete[] Arr;
	}

	void fill()
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				Arr[i][j] = (char)(rand() % 3 + 48);
	}
	char** get_matrix()
	{
		return Arr;
	}
};




class Marksys
{
	size_t N = 20, M = 20, Scale = 1, Size = N*M, Frames = 1000;
	char** Arr = {};
	char* Str = {};
	png::image<png::rgb_pixel> Image = {};
public:


	void set_size(size_t n, size_t m)
	{
		N = n;
		M = m;
		Size = N * M;
	}
	void set_scale(size_t scale)
	{
		Scale = scale;
	}
	void set_image()
	{
		Image = png::image<png::rgb_pixel> (N * Scale, M * Scale);
	}

	void matrix_create()
	{
		char** arr = new char* [N];
		for (int i = 0; i < N; i++)
			arr[i] = new char[M];

		Arr = arr;
	}
	void matrix_fill()
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				Arr[i][j] = (char)(rand() % 3 + 48);
	}

	void str_build_by_line()
	{
		size_t k = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				Str[k] = Arr[i][j];
				k++;
			}
		}
	}
	void str_build_re_by_line()
	{
		size_t k = 0;

		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = M - 1; j >= 0; j--)
			{
				Str[k] = Arr[i][j];
				k++;
			}
		}
	}
	void str_build_by_colomn()
	{
		size_t k = 0;

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				Str[k] = Arr[j][i];
				k++;
			}
		}
	}
	void str_build_re_by_colomn()
	{
		size_t k = 0;

		for (int i = M - 1; i >= 0; i--)
		{
			for (int j = N - 1; j >= 0; j--)
			{
				Str[k] = Arr[j][i];
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
		Str = new char[N*M];
	}

	void arr_build_by_line()
	{
		size_t k = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				Arr[i][j] = Str[k];
				k++;
			}
		}
	}
	void arr_build_re_by_line()
	{
		size_t k = 0;
		for (int i = N - 1; i >= 0; i--)
		{
			for (int j = M - 1; j >= 0; j--)
			{
				Arr[i][j] = Str[k];
				k++;
			}
		}
	}
	void arr_build_by_colomn()
	{
		size_t k = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				Arr[j][i] = Str[k];
				k++;
			}
		}
	}
	void arr_build_re_by_colomn()
	{
		size_t k = 0;
		for (int i = M - 1; i >= 0; i--)
		{
			for (int j = N - 1; j >= 0; j--)
			{
				Arr[j][i] = Str[k];
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
		for (size_t i = 0; i < Size - 1;)
		{
			if (uniform01() < p && Str[i] == '1' && Str[i + 1] == '0')
			{
				Str[i] = '0';
				Str[i + 1] = '1';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < p && Str[i] == '0' && Str[i + 1] == '1')
			{
				Str[i] = '1';
				Str[i + 1] = '0';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < p && Str[i] == '2' && Str[i + 1] == '0')
			{
				Str[i] = '0';
				Str[i + 1] = '2';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < p && Str[i] == '0' && Str[i + 1] == '2')
			{
				Str[i] = '2';
				Str[i + 1] = '0';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < p && Str[i] == '1' && Str[i + 1] == '2')
			{
				Str[i] = '2';
				Str[i + 1] = '1';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < p && Str[i] == '2' && Str[i + 1] == '1')
			{
				Str[i] = '1';
				Str[i + 1] = '2';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < q && Str[i] == '1' && Str[i + 1] == '0')
			{
				Str[i] = '1';
				Str[i + 1] = '1';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < q && Str[i] == '1' && Str[i + 1] == '2')
			{
				Str[i] = '2';
				Str[i + 1] = '2';
				i += 2 + rand() % 3;
			}
			else if (uniform01() < r && Str[i] == '2')
			{
				Str[i] = '0';
				i += 2 + rand() % 3;
			}
			else
				i++;
		}
	}

	void map_draw(int frame)
	{
		int a = 0, b = 0; //prey predator


		for (size_t i = 0; i < N * Scale; i++)
		{
			for (size_t j = 0; j < M * Scale; j++)
			{
				switch (Arr[i / Scale][j / Scale])
				{
				case'0':
					Image[i][j] = png::rgb_pixel(0, 0, 0);
					break;
				case '1':
					Image[i][j] = png::rgb_pixel(0, 255, 0);
					a++;
					break;
				case '2':
					Image[i][j] = png::rgb_pixel(255, 0, 0);
					b++;
					break;
				}
			}
		}
		
		if (frame % 10 == 0)
		{
			Image.write("out/frame" + std::to_string(frame) + ".png");
			std::cout << frame << " " << a << " " << b << std::endl;
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
		Frames = frames;
	}
	size_t get_frames()
	{
		return Frames;
	}


	Marksys()
	{

	}
};


void print_menu(int argc, char** argv, class Marksys& marksys) //добавить обработку ошибок
{
	system("cls"); // очищаем экран
	std::cout << "There are " << argc-1 << " arguments:\n";
	std::cout << ">";

	if (argc == 1)
	{
		std::cout << "Enter -help if you don't know what to do" << std::endl;
		exit(1);
	}
	else
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-help") == 0 || strcmp(argv[i], "--h") == 0)
			{
				std::cout <<
					"-help or --h: list of commands + example \n" <<
					"-setsize: set matrix size n x m. -setsize 50 50 \n" <<
					"-setscale: set  pixel size. -setscale 2 \n" <<
					"-countframes: set number of frames. -countframes 1000 \n";
			exit(1);
			}
		}
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-setsize") == 0)
			{
				marksys.set_size(std::atoi(argv[i + 1]), atoi(argv[i + 2]));
				i+= 2;
			}
			else if (strcmp(argv[i], "-setscale") == 0)
			{
				marksys.set_scale(std::atoi(argv[i + 1]));
				i += 1;
			}
			else if (strcmp(argv[i], "-countframes") == 0)
			{
				marksys.set_frames(std::atoi(argv[i + 1]));
				i += 1;
			}
			else
			{
				std::cout << "unknown command " << "\"" << argv[i] << "\"";
				exit(1);
			}
		}
		marksys.set_image();

	}
}

int main(int argc, char** argv)
{
	srand(time(NULL));

	Matrix matrix;
	char** mat = matrix.get_matrix();




	//size_t N = 20, M = 20, Scale = 1, Size = N * M;
	//png::image<png::rgb_pixel> image (N * Scale, M * Scale);
	Marksys marksys;
	print_menu(argc, argv, marksys);


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
