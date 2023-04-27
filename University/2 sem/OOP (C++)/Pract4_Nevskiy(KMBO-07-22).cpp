#include <iostream>
#include <string>
#include <cstring>


using namespace std;

constexpr char vowels[]{ "AaEeIiUuYyOo" };		//��� �������

bool isVowel(char c)		//�������� �� �������
{
	for (int i = 0; i < 12; i++)
	{
		if (c == vowels[i])
			return true;
	}
	return false;
}


//��������� ����� ������ � ������� C-style �����
class MyString
{
protected:
	int length;			//�����
	int capacity;		//���������� ������
	char* arr;			//��������� �� ��� ������

public:

	//����������� ����������� string
	MyString(const string& s)
	{
		if (s.size() == 0)		//�������� �� ������ ������
		{
			capacity = 1;
			length = 0;

			while (arr == 0)
				arr = new char[capacity];	//�������� �� ��������� ������
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

	//����������� ����������� �-������
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

	//����������� �� ���������
	MyString()
	{
		capacity = 1;
		length = 0;

		while (arr == 0)
			arr = new char[capacity];

		arr[0] = '\0';
	}

	//����������� �����
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

	//�������� []
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

	//�������� =  (��� ������� ������)
	MyString& operator=(MyString& s)
	{
		if (this == &s)		//���� �������� ���� ����
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

	//�������� =   (��� �����)
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

	//�������� =   (��� �-�����)
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

	//����� ������
	int size()
	{
		return length;
	}

	//�������� �������� ���� �����
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

	//�������� �������� ������ � MyString
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

	//�������� �������� MyString � �-�������
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


	//���������� ���������� ��� �������� � ������� �� ������� ������� ���������
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

	//����� ������
	void print()
	{
		int index = 0;
		while (arr[index] != '\0')
		{
			cout << arr[index];
			index++;
		}
	}

	//����������
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