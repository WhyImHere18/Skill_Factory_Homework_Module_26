// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <random>
#include <chrono>

#define ARR_SIZE 10000
#define N_PARTS 50
#define THREADS_NUM 100

int64_t static summa = 0;

void arr_sum(int arr[], int begin, int end)
{
	int s = summa;
	for (int i = begin; i < end; i++)
	{
		summa += arr[i];
	}

	std::cout << "sum(" << begin << "..." << end << ") = " << summa - s << std::endl;
}

 int getRandomNumber(int min, int max)
 {
	 static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	 return static_cast<int>(rand() * fraction * (max - min + 1) + min);
 }

int main()
{
	int array[ARR_SIZE]{};

	for (int i = 0; i < ARR_SIZE; i++)
	{
		array[i] = getRandomNumber(1, 100);
		//int x = THREADS_NUM + 1;
		//while (x > THREADS_NUM)
		//{
		//	x = 1 + std::rand() / ((RAND_MAX + 1u) / THREADS_NUM);
		//	array[i] = x;
		//	std::cout << array[i] << " ";
		//}
		//if ((i + 1) % THREADS_NUM == 0)
		//{
		//	std::cout << std::endl;
		//}
	}

	auto begin = std::chrono::steady_clock::now();

	for (int i = 0; i < ARR_SIZE; i += ARR_SIZE / N_PARTS)
	{
		int begin = i;
		int end = i + ARR_SIZE / N_PARTS;
		std::thread t(arr_sum, std::ref(array), std::ref(begin), std::ref(end));

		if (t.joinable())
			t.join();
	}

	std::cout << "sum of all array elements = " << summa << std::endl;

	auto end = std::chrono::steady_clock::now();

	auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin);	//duration in milliseconds

	std::cout << "elapsed time = " << elapsed_time.count() << " ms" << std::endl;

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
