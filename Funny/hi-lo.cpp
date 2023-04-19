#include <iostream>
#include <random>
#include <chrono>
#include <limits>

using namespace std;

void IgnoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool getChar()
{
	while (true)
	{
		cout << "Would you like to play again (y/n)? ";
		char c = {};
		cin >> c;
		IgnoreLine();
		switch(c)
		{
			case'y':
			case'Y':
				return 0;
			case 'n':
			case'N':
				return 1;
			default:
				;
		}
	}
}

int getX()
{
	while (true)
	{
		int x = {};
		cin >> x;
		if (!cin)
		{
			cin.clear();
			IgnoreLine();
		}
		else
		{
			if (x > 100 || x < 1)
				;
			else
			{
				IgnoreLine();
				return x;
			}
		}
	}
}

int main()
{
	std::mt19937 mt{ static_cast<unsigned int> (std::chrono::steady_clock::now().time_since_epoch().count()) };
	std::uniform_int_distribution die100{ 1,100 };
	bool a = {};
	while (!a)
	{
		cout << "Let's play a game. I'm thinking of a number. You have 7 tries to guess what it is.\n";
		int y = { die100(mt) };
		for (int i = 1; i <= 7; i++)
		{
			cout << "Guess #" << i << ": ";
			int x = {getX()};
			if (x == y)
			{
				cout << "Correct! You win!";
				break;
			}
			else if (x > y)
				cout << "Your guess is too high.\n";
			else if (x < y)
				cout << "Your guess is too low.\n";
			if (i == 7 && x != y)
				cout << "Sorry, you lose. The correct number was " << y;
		}
		cout << '\n';
		a = { getChar() };
	}

}