#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <execution>

using namespace std;
using namespace std::chrono_literals;

// Очередь клиентов
// Вам нужно создать приложение, которое имитирует очередь в окошко.Для этого нужно создать два потока, работающие с одной разделяемой переменной.
//
// Первый поток имитирует клиента : раз в секунду он обращается к счётчику клиентов и увеличивает его на 1. Максимальное количество клиентов должно быть параметризировано.
//
// Второй поток имитирует операциониста : раз в 2 секунды он обращается к счётчику клиентов и уменьшает его на 1. «Операционист» работает до последнего клиента.

constexpr int clients_max = 10;

atomic<int> clients_counter = 1;

namespace {
	void client(void)
	{
		while (clients_counter < clients_max)
		{
			this_thread::sleep_for(1s);
			clients_counter++;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			cout << "(" << __FUNCTION__ << ") Количество клиентов: " << clients_counter << endl;
		}
	}

	void manager(void)
	{
		do {
			this_thread::sleep_for(2s);
			if (clients_counter) clients_counter--;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout << "(" << __FUNCTION__ << ") Количество клиентов: " << clients_counter << endl;
		} while (clients_counter);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	thread t_client(client);
	thread t_manager(manager);

	t_client.join();
	t_manager.join();
	system("pause");
}
