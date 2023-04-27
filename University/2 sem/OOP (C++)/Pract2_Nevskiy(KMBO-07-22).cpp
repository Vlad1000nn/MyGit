#include <iostream>
#include <numeric>
#include <random>

using namespace std;

double dnan_value = numeric_limits <double> ::quiet_NaN();
int nnan_value = numeric_limits <int> ::quiet_NaN();

class MyArrayParent
{
protected:
	int capacity;		//кол-во памяти
	int count;			//кол-во элементов
	double* arr;		//массив

public:
	//конструктор
	MyArrayParent(int cap = 100)
	{
		arr = new double[cap];
		capacity = cap;
		count = 0;
	}

	//оператор =(другой массив)
	MyArrayParent operator=(MyArrayParent& v)
	{
		capacity = v.capacity;
		count = v.count;
		for (int i = 0; i < count; i++)
		{
			arr[i] = v[i];
		}
	}

	//обращение к полям
	int Capacity()
	{
		return capacity;
	}

	int Size()
	{
		return count;
	}


	double GetComponent(int index)
	{
		if (index < 0 || index >= count)
		{
			cout << "Wrong index value!\n";
			return  dnan_value;
		}
		return arr[index];
	}

	void SetComponent(int index, double value)
	{
		if (index < 0 || index >= count)
		{
			cout << "Wrong index value!\n";
			return;
		}
		arr[index] = value;
	}

	//конструктор принимающий другой массив
	MyArrayParent(double* mass, int cnt)
	{
		arr = new double[cnt + 10];
		capacity = cnt + 10;
		count = cnt;
		for (int i = 0; i < cnt; i++)
		{
			arr[i] = mass[i];
		}
	}

	//Конструктор копий
	MyArrayParent(MyArrayParent& v)
	{
		capacity = v.capacity;
		count = v.count;
		arr = new double[v.capacity];
		for (int i = 0; i < count; i++)
		{
			arr[i] = v[i];
		}
	}

	//Оператор[]
	double& operator[](int index)
	{
		if (index<0 || index> count)
		{
			cout << "Wrong index value!\n";
			return  dnan_value;
		}
		return *(arr + index);
	}

	void push(double value)
	{
		if (count >= capacity)
		{
			cout << "Error, the number of elements exceeds the possible!\n";
			return;
		}
		arr[count] = value;
		count++;
	}

	void removeLastValue()
	{
		if (count < 0)
		{
			cout << "Your array is already empty!\n";
			return;
		}
		count--;
	}

	//Дестркуктор
	~MyArrayParent()
	{
		if (arr != NULL)
		{
			delete[] arr;
			arr = NULL;
		}
	}

	int IndexOf(double value)
	{
		for (int i = 0; i < count; i++)
		{
			if (arr[i] == value)
				return i;
		}
		cout << "Didn't found the " << value << " inside array.'\n'";
		return numeric_limits <int> ::quiet_NaN();
	}

	void print()
	{
		cout << "\nMyArr, size: " << count << ", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << arr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}";
	}


};


class MyArrayChild : public MyArrayParent
{
public:

	//Конструкторы
	MyArrayChild() : MyArrayParent()
	{
		;
	}
	MyArrayChild(MyArrayChild& v) :MyArrayParent(v)
	{
		;
	}
	MyArrayChild(double* mass, int cnt) : MyArrayParent(mass, cnt)
	{
		;
	}

	//Удаление элемента из массива
	void RemoveAt(int index = -1)
	{
		for (int i = index + 1; i < count; i++)
		{
			arr[i - 1] = arr[i];
		}
		count--;
	}

	//Добавление элемента в массив
	void InsertAt(double value, int index = 0)
	{
		if (count >= capacity)
		{
			cout << "Error, your array is full\n'";
			return;
		}
		count++;
		for (int i = count - 1; i >= index; i--)
		{
			arr[i + 1] = arr[i];
		}
		arr[index] = value;
	}

	//Сумма между крайними нулевыми значениями,-1 если меньше 2х нулевых
	double sum_btw_zeros()
	{
		int index_1{ 0 }, index_2{ count - 1 };
		double sum = 0.0;

		//Поиск левого крайнего
		while (arr[index_1] != 0)
		{
			if (index_1 == count - 1 && arr[index_1] != 0)
				return -1;
			index_1++;
		}

		//Поиск правого крайнего
		while (arr[index_2] != 0)
		{
			if (index_2 == 0 && arr[index_2] != 0)
				return -1;
			index_2--;
		}

		//Если один 0
		if (index_1 == index_2)
			return -1;

		//Считаем сумму
		for (int i = index_1; i <= index_2; i++)
			sum += arr[i];
		return sum;
	}

	//Поиск индекса по значению
	int find_index_of_value(double value)
	{
		for (int i = 0; i < count; i++)
		{
			if (arr[i] == value)
				return i;
		}
		cout << "The " << value << " is not in array!\n";
		return -1;
	}

	//Добавление элемента через бинарный оператор +
	MyArrayChild operator+(double value)
	{
		MyArrayChild ans;
		ans.count = count;
		ans.capacity = capacity;
		for (int i = 0; i < count; i++)
		{
			ans[i] = arr[i];
		}

		if (count >= capacity)
		{
			cout << "Your array is full!\n";
			return ans;
		}
		count++;
		ans[count] = value;
		return ans;

	}

	//Выделение подпоследовательности
	MyArrayChild SubSequence(int start_index = 0, int Length = 0)
	{
		MyArrayChild ans;

		if (start_index < 0 || start_index >= count || start_index + Length >= count || Length < 0)
		{
			cout << "Cannot get SubSequence with your data!\n";
			ans.capacity = capacity;
			ans.count = count;
			for (int i = 0; i < count; i++)
			{
				ans[i] = arr[i];
			}
			return ans;
		}

		ans.capacity = Length + 1;
		ans.count = Length;
		for (int i = start_index, g = 0; i < start_index + Length; i++, g++)
		{
			ans[g] = arr[i];
		}
		return ans;
	}


	//Деструктор
	~MyArrayChild()
	{
		;
	}
};

class MySortedArray : public MyArrayChild
{
public:
	//Конструкторы
	MySortedArray() :MyArrayChild()
	{
		;
	}
	MySortedArray(MySortedArray& v) :MyArrayChild(v)
	{
		;
	}
	MySortedArray(double* mass, int cnt) : MyArrayChild(mass, cnt)
	{
		;
	}


	int IndexOf(double value)
	{
		for (int i = 0; i < count; i++)
		{
			if (arr[i] > value)
				break;
			if (arr[i] == value)
				return i;
		}
		cout << "Didn't found the " << value << " inside array.'\n'";
		return numeric_limits <int> ::quiet_NaN();
	}



	void push(double value)
	{
		if (count >= capacity)
		{
			cout << "Error, the number of elements exceeds the possible!\n";
			return;
		}
		count++;
		int index_i = count;
		bool isfind = { false };
		for (int i = 0; i < count; i++)
		{
			if (arr[i] > value)
			{
				isfind = true;
				index_i = i;
			}
		}
		if (isfind)
		{
			InsertAt(value, index_i);
		}
		else
			arr[count] = value;
	}

	double sum_btw_zeros()
	{
		if (arr[0] = arr[1] == 0)
			return 0;
		else
			return -1;
	}

	//Деструктор
	~MySortedArray()
	{
		;
	}
};



template<typename T>
void fill_array(T& mass)
{
	for (int i = 0; i < 50; i++)
	{
		mass.push((rand() % 15));
	}
}


int main()
{
	MyArrayParent arr_1;
	fill_array(arr_1);

	arr_1.print();
	cout << '\n' << "Capacity is " << arr_1.Capacity();
	cout << '\n' << "Size is " << arr_1.Size() << '\n';


	MyArrayParent arr_2 = arr_1;
	arr_2.print();

	cout << "\nSixth element of array is " << arr_1[5] << '\n';

	cout << "13 has a postition " << arr_2.IndexOf(13) << '\n';

	MyArrayChild arr_3;
	fill_array(arr_3);
	arr_3.print();


	arr_3.RemoveAt(6);
	arr_3.InsertAt(190, 39);
	arr_3.print();

	arr_3[7] = arr_3[15] = arr_3[19] = 0;
	arr_3.print();

	cout << "\nSum between zeros is " << arr_3.sum_btw_zeros() << '\n';



	double N[51];
	for (int i = 0; i < 50; i++)
	{
		N[i] = rand() % 21;
	}
	sort(N, N + 50);

	MySortedArray arr_4{ N,40 };
	arr_4.print();
	cout << '\n' << arr_4.IndexOf(12) << '\n';
	cout << arr_4.sum_btw_zeros();




	return 0;
}