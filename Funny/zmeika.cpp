#include <iostream>
#include <conio.h>
#define NOMINMAX
#include <limits>
#include  <windows.h>
#include <random>
#include <chrono>

using namespace std;

bool gameOver = {};
char c = {};
const int width = { 20 };
const int height = { 20 };
int x = {};
int y = {};
int fruitX = {};
int fruitY = {};
int score = {};
int speed = {};
int tailX[100];
int tailY[100];
int nTail = {};

namespace Random
{
	std::mt19937 mt{ std::random_device{}() };

	int die19(int min, int max)
	{
		std::uniform_int_distribution die{ min, max };
		return die(mt);
	}
}

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void IgnoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void Setup()
{

	cout << "Hi, this is snake game, thank for choosing us!\n\n";
	cout << "Choose the speed of the game:\n";
	cout << "1. Low\t  2. Medium\t3. High\n";
	bool a = {};
	while (!a)
	{
		cin >> c;
		switch (c)
		{
		case '1':
			speed = 300;
			a = true;
			break;
		case '2':
			speed = 100;
			a = true;
			break;
		case '3':
			speed = 0;
			a = true;
			break;
		default:
			IgnoreLine();
			cin.clear();
			break;
		}
	}

	gameOver = false;
	dir = STOP;
	x = (width / 2)-1;
	y = (height / 2)-1;
	fruitX = Random::die19(1,19);
	fruitY = Random::die19(1,19);
	score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i <= width; i++)
	{
		SetColor(1, 1);
		cout << "#";
		SetColor(15, 0);
	}
	cout << '\n';

	for (int i = 0; i < height; i++)
	{
		for (int g = 0; g < width; g++)
		{
			if (g == 0 || g == width - 1)
			{
				SetColor(1, 1);
				cout << "#";
				SetColor(15, 0);
			}
			if (i == y && g == x)
			{
				SetColor(2, 2);
				cout << "0";
				SetColor(15, 0);
			}
			else if (i == fruitY && g == fruitX)
			{
				SetColor(4, 4);
				cout << "f";
				SetColor(15, 0);
			}
			else
			{
				bool print = {};

				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == g && tailY[k] == i)
					{
						SetColor(10, 10);
						cout << "o";
						print = true;
					}
				}
				SetColor(15, 0);
				if(!print)

					cout << ' ';
			}
		}
		cout << '\n';
	}

	for (int i = 0; i <= width; i++)
	{
		SetColor(1, 1);
		cout << "#";
	}
	SetColor(15, 0);
	cout << '\n';
	cout << "Score " << score << '\n';
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = {tailX[0]};
	int prevY = { tailY[0] };
	int prev2X = {};
	int prev2Y = {};
	tailX[0] = x;
	tailY[0] = y;
	

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++; 
		break;
	}
	if (x >= width-1 || x < 0 || y>=height || y < 0)
		gameOver = true;

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = Random::die19(1, 19);
		fruitY = Random::die19(1, 19);
		nTail++;
	}
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Sleep(speed);
		Input();
		Logic();
	}
	return 0;
}