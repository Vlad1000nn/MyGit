#include <iostream>
#include <string>
#include <cstring>


using namespace std;

constexpr char vowels[]{ "AaEeIiUuYyOo" };		//Все гласные

bool isVowel(char c)		//Проверка на гласную
{
	for (int i = 0; i < 12; i++)
	{
		if (c == vowels[i])
			return true;
	}
	return false;
}


//Реализуем класс строка с помощью C-style строк
class MyString
{
protected:
	int length;			//Длина
	int capacity;		//Выделяемая память
	char* arr;			//Указатель на наш массив

public:

	//Конструктор принимающий string
	MyString(const string& s)
	{
		if (s.size() == 0)		//Проверка на пустую строку
		{
			capacity = 1;
			length = 0;

			while (arr == 0)
				arr = new char[capacity];	//Проверка на выделение памяти
			arr[0] = '\0';
		}
		else
		{
			length = s.size();
			capacity = length + 1;

			while (arr == 0)
				arr = new char[capacity];

			for (int i = 0; i < length; i++)
				arr[i] = s[i];

			arr[length] = '\0';
		}
	}

	//Конструктор принимающий С-строку
	MyString(char* str)
	{
		if (strlen(str) == 0)
		{
			capacity = 1;
			length = 0;

			while (arr == 0)
				arr = new char[capacity];

			arr[0] = '\0';
		}
		else
		{
			length = strlen(str);
			capacity = sizeof(str);

			while (arr == 0)
				arr = new char[capacity];

			for (int i = 0; i < length; i++)
				arr[i] = str[i];

			arr[length] = '\0';
		}

	}

	//Конструктор по умолчанию
	MyString()
	{
		capacity = 1;
		length = 0;

		while (arr == 0)
			arr = new char[capacity];

		arr[0] = '\0';
	}

	//Конструктор копий
	MyString(const MyString& s)
	{
		length = s.length;
		capacity = s.capacity;

		while (true)
		{
			arr = new char[capacity];
			if (arr != 0) break;
		}

		for (int i = 0; i < length; i++)
			arr[i] = s.arr[i];

		arr[length] = '\0';
	}

	//Оператор []
	char& operator[](int index)
	{
		if (index < 0 || index >= length)
		{
			cout << "Wrong index value!\n";
			return arr[length];
		}
		else
			return arr[index];
	}

	//Оператор =  (для объекта класса)
	MyString& operator=(MyString& s)
	{
		if (this == &s)		//Если передали сами себя
			return *this;

		length = s.length;
		capacity = s.capacity;

		while (true)
		{
			arr = new char[capacity];
			if (arr != 0)
				break;
		}

		for (int i = 0; i < length; i++)
			arr[i] = s.arr[i];

		arr[length] = '\0';


		return *this;
	}

	//Оператор =   (для строк)
	MyString& operator=(const string& s)
	{
		if (s.size() == 0)
		{
			length = 0;
			capacity = 1;

			while (true)
			{
				arr = new char[capacity];
				if (arr != 0) break;
			}

			arr[0] = '\0';
		}
		else
		{
			length = s.size();
			capacity = length + 1;

			while (true)
			{
				arr = new char[capacity];
				if (arr != 0) break;
			}

			for (int i = 0; i < length; i++)
				arr[i] = s[i];

			arr[length] = '\0';
		}
		return *this;
	}

	//Оператор =   (для С-строк)
	MyString& operator=(char* str)
	{
		if (strlen(str) == 0)
		{
			length = 0;
			capacity = 1;

			while (true)
			{
				arr = new char[capacity];
				if (arr != 0) break;
			}

			arr[length] = '\0';
		}
		else
		{
			length = strlen(str);
			capacity = sizeof(str);

			while (true)
			{
				arr = new char[capacity];
				if (arr != 0) break;
			}

			arr[length] = '\0';
		}
		return *this;
	}

	//Длина строки
	int size()
	{
		return length;
	}

	//Оператор сложения двух строк
	MyString operator+(const MyString& s)
	{
		MyString ans;

		ans.length = length + s.length;
		ans.capacity = capacity + s.capacity - 1;

		while (true)
		{
			ans.arr = new char[ans.capacity];
			if (ans.arr != 0) break;
		}

		for (int i = 0; i < length; i++)
			ans.arr[i] = arr[i];

		for (int i = 0, index = length; i < s.length; i++, index++)
		{
			ans.arr[index] = s.arr[i];
		}

		ans.arr[ans.length] = '\0';
		return ans;

	}

	//Оператор сложения строки и MyString
	MyString operator+(const string& s)
	{
		MyString ans;

		ans.length = length + s.size();
		ans.capacity = s.size() + capacity;

		while (true)
		{
			ans.arr = new char[ans.capacity];
			if (arr != 0) break;
		}

		for (int i = 0; i < length; i++)
			ans.arr[i] = arr[i];

		for (int i = 0, index = length; i < s.size(); i++, index++)
			ans.arr[index] = s[i];

		ans.arr[ans.length] = '\0';
		return ans;
	}

	//Оператор сложения MyString с С-строкой
	MyString operator+(char* str)
	{
		MyString ans;

		ans.length = length + strlen(str);
		ans.capacity = capacity + strlen(str);

		while (true)
		{
			ans.arr = new char[ans.capacity];
			if (arr != 0) break;
		}

		for (int i = 0; i < length; i++)
			ans.arr[i] = arr[i];

		for (int i = 0, index = length; i < strlen(str); i++, index++)
			ans.arr[index] = str[i];

		ans.arr[ans.length] = '\0';
		return ans;
	}


	MyString operator+(char c)
	{
		MyString ans;

		ans.length = length + 1;
		ans.capacity = capacity + 1;

		while (true)
		{
			ans.arr = new char[ans.capacity];
			if (arr != 0) break;
		}

		for (int i = 0; i < length; i++)
			ans.arr[i] = arr[i];

		ans.arr[length] = c;
		ans.arr[ans.length] = '\0';

		return ans;
	}


	//Подсчитать количество пар символов у которых за гласной следует согласная
	int pairs()
	{
		int sum = { 0 };

		for (int i = 0; i < length - 1; i++)
		{
			if (!isVowel(arr[i]) && isVowel(arr[i + 1]))
				sum += 1;
		}
		return sum;
	}

	//Вывод строки
	void print()
	{
		int index = 0;
		while (arr[index] != '\0')
		{
			cout << arr[index];
			index++;
		}
	}

	//Деструктор
	~MyString()
	{
		delete[] arr;
	}
};



int main()
{
	string s{ "BLAhaMA" };
	MyString mystring{ s };

	const char s1[]{ "My name is Goustavo" };
	MyString mystring2{ s1 };

	mystring.print(); 	cout << '\n';

	mystring2.print(); cout << '\n';

	cout << "The third element is " << mystring[3];
	cout << '\n';

	MyString mystring3;


	mystring3 = mystring;
	mystring3.print(); cout << '\n';

	mystring3 = s;
	mystring3.print(); cout << '\n';

	mystring3 = s1;
	mystring3.print(); cout << '\n';

	MyString mystring4;
	(mystring + mystring3).print();	cout << '\n';
	(mystring + s).print(); cout << '\n';
	(mystring + s1).print(); cout << '\n';
	(mystring + '9').print(); cout << '\n';

	return 0;
}