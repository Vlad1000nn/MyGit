#include <iostream>
#define NOMINMAX
#include "functions.h"
#include <random>
#include <chrono>
#include "locale.h"
#include <conio.h>
#include <limits>
#include <Windows.h>

using namespace std;

int PCsum = {0};
int Playersum = { 0 };

namespace Random
{
	std::mt19937 mt{ std::random_device{}() };

	int get(int min, int max)
	{
		std::uniform_int_distribution die{ min, max };
		return die(mt);
	}
}

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


void IgnoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool StartOfProgramm()
{
	while (true)
	{
		char c = {};
		cin >> c;
		if (c == 'r' || c == 'R')
			return whoIsFirst();
		else if (c == 'x' || c == 'X')
			exitProgramm();
		else
		{
			cin.clear();
			IgnoreLine();
		}
	}
}

bool whoIsFirst()
{
	bool x = { static_cast<bool>(Random::get(0,1)) };
	if (x == 0)
	{
		cout << "\nКомпьютер ходит первым.\n";
		return 0;
	}
	else
	{
		cout << "\nВы ходите первым.\n";
		return 1;
	}

}

void exitProgramm()
{
	cout << '\n' << "Завершение работы программы...";
	Sleep(1000);
	exit(0);
}

void Input()
{
	while (true)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'x':
			case'X':
				exitProgramm();
				return;
			case's':
			case'S':
				YourStep();
				return;
			}
		}
	}
}

void YourStep()
{
	Sleep(1000);
	cout << "\n\nВы:\n";
	Sleep(2000);
	int x = {Random::get(1,6) };
	int y = {Random::get(1,6)};
	Output(x);
	Sleep(2000);
	Output(y);
	Playersum += x + y;
}

void Step(bool a)
{
	Sleep(1000);
	if (a == 0)
	{
		int x = { Random::get(1,6) };
		int y = { Random::get(1,6) };
		cout << "\nКомпьюьтер:\n";
		Sleep(2000);
		Output(x);
		Sleep(2000);
		Output(y);
		PCsum += x + y;

		cout <<'\n'<< "Нажмите s, чтобы сделать ход...";
		Input();
		Sleep(1000);
		cout << "\nСчёт:\nКомпьютер: " << PCsum << '\n' << "Вы: " << Playersum << '\n';
		Sleep(2000);
	}
	else
	{
		cout << '\n' << "Нажмите s, чтобы сделать ход...";
		Input();
		Sleep(1000);
		
		int x = { Random::get(1,6) };
		int y = { Random::get(1,6) };
		cout << "\nКомпьюьтер:\n";
		Sleep(2000);
		Output(x);
		Sleep(1000);
		cout << '\n';
		Output(y);
		cout << '\n';
		PCsum += x + y;

		cout << "\nСчёт:\nКомпьютер: " << PCsum << '\n' << "Вы: " << Playersum << '\n';
		Sleep(2000);
	}

}

void Results()
{
	if (PCsum > Playersum)
		cout << '\n' << "Вы проиграли!\n";
	else if (PCsum < Playersum)
		cout << '\n' << "Вы выйграли!\n";
	else if (PCsum == Playersum)
		cout << '\n' << "Ничья!\n";
}

void Again()
{
	cout << "Игра окочена, не хотите ли сыграть ещё? (y/n)\n";
	while (true)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'n':
			case 'N':
			{
				cout << "\nСпасибо за игру!\n";
				exit(0);
			}
			case 'y':
			case 'Y':
				return;
			}
		}
	}


}
void Output(int x)
{
	cout << '\n';
	switch (x)
	{
	case 1:
		SetColor(15,15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout <<'\n';
		SetColor(15, 15);
		cout << "***";
		SetColor(15,0);
		cout << ' ';
		SetColor(15, 15);
		cout << "***";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 0);
		break;
	case 2:
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
			cout << ' ';
			SetColor(15, 15);
			cout << "*****";
			SetColor(15, 0);
			cout << '\n';
			SetColor(15, 15);
			cout << "*******";
			SetColor(15, 0);
			cout << '\n';
			SetColor(15, 15);
			cout << "*****";
			SetColor(15, 0);
			cout << ' ';
			SetColor(15, 15);
			cout << "*";
			SetColor(15, 0);
			cout << '\n';
			SetColor(15, 15);
			cout << "*******";
			SetColor(15, 0);
			cout << '\n';
		break;
	case 3:
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*****";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "***";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "***";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*****";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		break;
	case 4:
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "***";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "***";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		break;
	case 5:
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "***";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "***";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "***";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "***";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		break;
	case 6:
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << ' ';
		SetColor(15, 15);
		cout << "*";
		SetColor(15, 0);
		cout << '\n';
		SetColor(15, 15);
		cout << "*******";
		SetColor(15, 0);
		cout << '\n';
		break;
	}
	cout << '\n';
}
int main()
{
	setlocale(LC_ALL, "rus");

	while (true)
	{
		cout << "Добро пожаловать! В этой игре вам предстоит по очереди кидать по 2 кубика вместе с компьютером.\n"
			"Всего 4 попытки. Побеждает тот, у кого больше очков. В любой момент игры вы можете нажать X и выйти из игры. Удачи!\n";
		cout << "\nНажмите R и Enter для случайного выбора первоходящего: ";
		bool a = { StartOfProgramm() };
		Sleep(1000);
		for (int i = 1; i <= 4; i++)
		{
			cout <<'\n'<< i << "-й ход:\n";
			Sleep(1000);
			Step(a);
		}
		Results();
		Again();
		PCsum = 0;
		Playersum = 0;
		cout << '\n';
	}
	return 0;
}