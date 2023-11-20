/*⣗⠀⠀⠀⠀⠀⠀⠀⠉⠛⠿⠿⣿⠿⣿⣿⣿⣿⠿⠿⠿⠟⠛⠉⠁⠀⠀⠀⢠⣿
⣿⣷⣀⠀⠈⠛⠢⠥⠴⠟⠂⠀⠀⠀⠉⣛⠉⠁⠀⠐⠲⠤⠖⠛⠁⠀⠀⣐⣿⣿
⣿⣿⣿⣦⣄⡀⠀⠀⠀⠀⣀⡠⣤⣦⣿⣿⣿⣆⣴⣠⣀⣀⡀⣀⣀⣚⣿⣿⣿⢳
⣧⠉⠙⢿⣿⣿⣶⣶⣾⣿⡿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢇⣿
⣿⣷⡄⠈⣿⣿⣿⣿⣯⣥⣦⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢉⣴⣿⣿
⣿⣿⣿⣦⣘⠋⢻⠿⢿⣿⣿⣿⣾⣭⣛⣛⣛⣯⣷⣿⣿⠿⠟⠋⠉⣴⣿⣿⣿⣿
⣿⣿⣿⣿⠆⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⡅⠀⠀⠻⣿⣿⠿⠛⠋⠉⠉⠉⠀⠀⢈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⡇⠀⠀⠀⠊⠀⠀⠠⠀⠀⠐⠒⢲⠛⠻⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⡇⠀⡠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡀⠀⠂⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣷⠀⠁⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠄⣀⣠⣼⡿⢿⠿⠟⠛⠉⢹
⣿⣿⣿⣿⣿⠀⣼⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣶⣿⣿
⣿⣿⣿⣿⣠⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠤⣴⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⡖⢦⢰⠖⣦⠀⣶⠀⢲⡖⢲⡆⠀⠀⠀⡖⢲⠀⡖⠒⣶⢰⡆⣶⢰⡆⡴⢲⡄
⡇⠀⢸⠤⠟⢰⢻⡄⢸⡇⢸⡗⢦⠀⠀⡗⢾⠀⡷⠆⠻⣼⡇⣿⢾⡇⡇⢸⡇
⠷⠞⠸⠀⠀⠾⠉⠷⠸⠇⠸⠷⠞⠀⠀⠷⠾⠀⠷⠶⠀⠸⠇⠿⠸⠇⠳⠼⠀*/



#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


namespace Random {
	mt19937 mt{ random_device{}() };

	int get(int min, int max) {
		uniform_int_distribution die{ min, max };
		return die(mt);
	}
}

//Абстрактный класс исключений
class Exception : public exception {
protected:
	char* str;
public:

	//Конструктор
	Exception(const char* str_e) {
		while (true) {
			str = new char[strlen(str_e) + 1];
			if (str != 0) break;
		}

		for (int i = 0; i < strlen(str_e); i++)
			str[i] = str_e[i];
		str[strlen(str_e)] = '\0';
	}

	//Конструктор копий
	Exception(const Exception& e) {
		str = new char[strlen(e.str) + 1];
		for (int i = 0; i < strlen(e.str); i++)
			str[i] = e.str[i];
		str[strlen(e.str)] = '\0';
	}

	//Деструктор
	~Exception() {
		delete[] str;
	}

	virtual void print() = 0;
};

//Передача nullptr указателя в функцию
class null_ptr : public Exception {
public:
	null_ptr() : Exception("Nullptr pointer was find in arguments") { }

	void print() {
		cout << "Exception: nullptr pointer\n";
	}
};

//Выход за границы списка
class WrongIndex : public Exception {
public:

	WrongIndex() : Exception("Attempt to go out of bounds") { }

	void print() {
		cout << "Exception: wrong index\n";
	}
};


//Ошибка выделения памяти
class bad_allocs :public Exception {
public:

	bad_allocs() :Exception("Memory was not allocated") { }

	void print() {
		cout << "Exception: " << str << '\n';
	}
};


enum class Model {
	Unknown,
	Xiaomi,
	Iphone,
	Huawei,
	OnePlus,
	Google,
	Samsung,
	Poco,
	Realme,
	Honor,
	Max_count,
};
//Вывод модели
ostream& operator<<(ostream& out, const Model& model) {
	//C++20
	//using enum Model;
	switch (model) {
	case Model::Xiaomi: out << "Xiaomi"; break;
	case Model::Iphone: out << "Iphone"; break;
	case Model::Huawei: out << "Huawei"; break;
	case Model::OnePlus: out << "OnePlus"; break;
	case Model::Google: out << "Google"; break;
	case Model::Samsung: out << "Samsung"; break;
	case Model::Poco: out << "Poco"; break;
	case Model::Realme: out << "Realme"; break;
	case Model::Honor: out << "Honor"; break;
	case Model::Unknown: out << "Unknown"; break;
	default: out << "???"; break;
	}
	return out;
}
//Ввод модели
istream& operator>>(istream& in, Model& model) {
	//C++20
	//using enum Model;
	string temp;
	in >> temp;

	if (temp == "Xiaomi")
		model = Model::Xiaomi;
	else if (temp == "Google")
		model = Model::Google;
	else if (temp == "Huawei")
		model = Model::Huawei;
	else if (temp == "Poco")
		model = Model::Poco;
	else if (temp == "Realme")
		model = Model::Realme;
	else if (temp == "Iphone")
		model = Model::Iphone;
	else if (temp == "Samsung")
		model = Model::Samsung;
	else if (temp == "OnePlus")
		model = Model::OnePlus;
	else if (temp == "Honor")
		model = Model::Honor;
	else model = Model::Unknown;

	return in;
}


class SmartPhone {
private:
	Model model;
	double screen_size;
	int count_of_cameras;
	int battery;
	int autonomy_hours;
	double price;
public:
	friend ostream& operator<<(ostream& out, SmartPhone& const smartphone);
	friend istream& operator>>(istream& in, SmartPhone& smartphone);

	//Getters
	Model Modele() { return model; }
	double Screen_size() { return screen_size; }
	int Count_of_cameras() { return count_of_cameras; }
	int Battery() { return battery; }
	int Autonomy() { return autonomy_hours; }
	double Price() { return price; }

	//Setters
	void Modele(Model& _model) { model = _model; }
	void Screen_size(double _screen_size) { screen_size = _screen_size; }
	void Count_of_cameras(int _count_of_cameras) { count_of_cameras = _count_of_cameras; }
	void Battery(int _battery) { battery = _battery; }
	void Autonomy(int _autonomy_hours) { autonomy_hours = _autonomy_hours; }
	void Price(double _price) { price = _price; }

	SmartPhone(Model _model = Model::Unknown, double _screen_size = -1, int _count_of_cameras = -1,
		int _battery = -1, int _autonomy_hours = -1, double _price = -1)
		: model(_model)
		, screen_size(_screen_size)
		, count_of_cameras(_count_of_cameras)
		, battery(_battery)
		, autonomy_hours(_autonomy_hours)
		, price(_price)
	{ }
};

//Вывод смартфона
ostream& operator<<(ostream& out, SmartPhone& const smartphone) {
	out << "\nModel:" << smartphone.Modele() << "\nScreen size:" << smartphone.Screen_size() << "\"\nCount of cameras:" << smartphone.Count_of_cameras();
	out << "\nBattery:" << smartphone.Battery() << " mA\nAutonomy:" << smartphone.Autonomy() << " h\nPrice:" << smartphone.Price() << "$\n";
	return out;
}

//Ввод смартфона
istream& operator>>(istream& in, SmartPhone& smartphone) {
	Model modele; int counts, batterys, hours; double sizes, prices;

	in >> modele >> counts >> batterys >> hours >> sizes >> prices;

	smartphone.Modele(modele); smartphone.Count_of_cameras(counts); smartphone.Battery(batterys);
	smartphone.Autonomy(hours); smartphone.Screen_size(sizes); smartphone.Price(prices);

	return in;
}

//Фильтр по диагонали экрана
bool myfiltr(SmartPhone x, SmartPhone value) {
	return x.Screen_size() > value.Screen_size();
}

//Поиск по модели смартфона
bool myfind(SmartPhone x, SmartPhone model) {
	return x.Modele() == model.Modele();
}

template<class T>
class MyTwoList {
protected:
	//Узел списка
	template<class T>
	class Node {
	public:
		Node* prev;
		Node* next;
		T data;

		//Конструктор по умолчанию
		Node(const T _data = T(), Node* _prev = nullptr, Node* _next = nullptr)
			: data(_data)
			, prev(_prev)
			, next(_next)
		{ }

		//Конструктор копий
		Node(Node<T>& V) {
			this->data = V.data;
			this->prev = V.prev;
			this->next = V.next;
		}
	};
	//Размеры списка
	int size;
	//Начало списка
	Node<T>* head;
	//Конец списка
	Node<T>* tail;

public:
	template<class T>
	friend ostream& operator<<(ostream& out, MyTwoList<T>& const list);
	template<class T>
	friend istream& operator>>(istream& in, MyTwoList<T>& list);
	//Конструктор по умолчанию
	MyTwoList<T>() {
		size = 0;
		head = tail = nullptr;
	}

	//Конструктор с 0-м элементом
	MyTwoList<T>(const T& _data) {
		size = 1;
		head = tail = new Node<T>(_data);
	}

	//Конструктор, приимающий массив (Why not?)
	template<size_t N>
	MyTwoList<T>(T(&arr)[N]) {
		if (arr == nullptr)
			throw null_ptr();

		size = static_cast<int>(N);
		head = new Node<T>(arr[0]);

		Node<T>* current = head;

		for (int i = 1; i < N; ++i) {
			current->next = new Node<T>(arr[i], current);
			current = current->next;
		}
		tail = current;
	}

	//Геттер размера списка
	int Size() { return size; }

	//Геттер головы списка
	Node<T>* first() { return head; }

	//Геттер хвоста списка
	Node<T>* last() { return tail; }

	void setFirst(Node<T>* _head) { head = _head; }

	//Занесение элемента в конец списка
	void push_back(const T& _data) {
		if (!head)						//Если список пустой
			head = tail = new Node<T>(_data);
		else {
			tail->next = new Node<T>(_data, tail); // Нет проверки на неудачное выделение памяти
			if (!tail->next) throw bad_allocs();
			tail = tail->next;
		}
		++size;
	}

	//Вставка в начало
	void push_front(const T& _data) {
		head->prev = new Node<T>(_data, nullptr, head);
		head = head->prev;
		++size;
	}

	//Вставка на какуюто позицию в список
	void InsertAt(const T& _data, const int index) {
		if (index<0 || index>size)
			throw WrongIndex();

		if (index == 0) {
			push_front(_data);
			return;
		}
		else if (index == size - 1) {
			push_back(_data);
			return;
		}

		if (head == nullptr)
			head = tail = new Node<T>(_data);
		else {
			Node<T>* current = head;
			int current_index = 0;

			while (current_index != index)
			{
				current = current->next;
				current_index++;
			}
			Node<T>* prev_ptr = current->prev;
			current->prev = prev_ptr->next = new Node<T>(_data, current->prev, current);
		}
		++size;
	}

	//Удаление элемента с позиции в списке
	void erase(const int index) {
		if (index<0 || index>size)
			throw WrongIndex();

		if (index == 0) {
			pop_front();
			return;
		}
		else if (index == size - 1) {
			pop_back();
			return;
		}

		Node<T>* current = head;
		int current_index = 0;

		while (current_index != index) {
			current = current->next;
			current_index++;
		}

		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;

		--size;
	}

	//Вывод в файл
	ofstream& save(ofstream& out) {
		if (head == nullptr) {
			cout << "List is empty\n";
			return out;
		}
		if (out) {
			out << size << '\n' << size << '\n';
			Node<T>* current = head;

			while (current != tail) {
				out << current->data << ' ';
				current = current->next;
			}
			out << current->data;
			return out;
		}
	}

	//чтение из файла
	MyTwoList<T>& load(ifstream& in) {
		if (in) {
			int temp_size, count;
			in >> count >> temp_size;

			for (int i = 0; i < temp_size; i++) {
				T _data;
				in >> _data;
				push_back(_data);
			}
		}
		return *this;
	}


	//Удаление из начала списка
	void pop_front() {
		Node<T>* temp = head;
		head = head->next;
		--size;
		delete temp;
	}

	//Удаление с конца списка
	void pop_back() {
		Node<T>* temp = tail;
		tail->prev->next = nullptr;
		delete temp;
		--size;
	}

	//Поиск индекса элемента по значению
	int find(const T& _data) const {
		if (head == nullptr) {
			cout << "List is empty\n";
			return -1;
		}
		else {
			Node<T>* current = head;
			int current_index = 0;

			while (current->data != _data && current_index < size - 1) {
				current = current->next;
				current_index++;
			}

			if (current->data == _data)
				return current_index;
			else {
				cout << "An element " << _data << " didn't find in the list\n";
				return -1;
			}
		}
	}

	//Обращение по индексу
	T& operator[](const int index) const {
		if (index < 0 || index >= size)
			throw WrongIndex();

		Node<T>* current = head;
		int current_index = 0;

		while (current_index != index) {
			current = current->next;
			current_index++;
		}

		return current->data;
	}

	//Оператор присваивания списка
	MyTwoList<T>& operator=(const MyTwoList<T>& V) {
		if (&V == this)
			return *this;

		if (V.head == nullptr)
			return *this;

		this->size = V.size;
		this->head = new Node<T>(V.head->data);

		Node<T>* current = this->head;
		Node<T>* Vcurrent = V.head;
		int current_index = 0;

		while (current_index < V.size - 1) {
			current->next = new Node<T>(Vcurrent->next->data, current);
			Vcurrent = Vcurrent->next;
			current = current->next;
			current_index++;
		}
		this->tail = current;

		return *this;
	}

	//Фильтр
	MyTwoList& filtr(const T& value, bool(*f)(T, T) = myfiltr) const {
		static MyTwoList res;

		if (head == nullptr) {
			cout << "List is empty";
			return res;
		}

		Node<T>* current = head;
		while (current != tail) {
			if (f((current->data), value))
				res.push_back(current->data);
			current = current->next;
		}

		if (f((tail->data), value))
			res.push_back(tail->data);

		return res;
	}

	//Поиск 
	T& find_el(const T& value, bool(*f)(T, T) = myfind) const {
		if (f == nullptr) throw null_ptr();

		if (head == nullptr) {
			cout << "List is empty\n";
			static T nothing{};
			return nothing;
		}

		Node<T>* current = head;
		while (current != tail)
		{
			if (f((current->data), value))
				return current->data;
			current = current->next;
		}
		if (f((tail->data), value))
			return tail->data;

		cout << "Didn't find in the list\n";
		return head->data;
	}

	//Рандомное заполнение списка
	void rand_fill() {
		int count = Random::get(1, 40);
		size = count;

		T head_data = static_cast<T>(Random::get(1, 40));
		head = new Node<T>(head_data);

		int current_index = 1;
		Node<T>* current = head;

		while (current_index != size) {
			T data = static_cast<T>(Random::get(1, 40));
			current->next = new Node<T>(data, current);
			current = current->next;
			current_index++;
		}
		tail = current;
	}

	//очищаем список
	void clear() {
		while (size)
			pop_front();
	}

	//Вывод
	void print() {
		if (head == nullptr)
			cout << "List is empty\n";
		else {
			Node<T>* current = head;
			while (current->next != nullptr) {
				cout << current->data << ' ';
				current = current->next;
			}
			cout << current->data << '\n';
		}
	}

	//Деструктор
	~MyTwoList<T>() {
		clear();
	}
};


//Вывод
template<class T>
ostream& operator<<(ostream& out, MyTwoList<T>& const list) {
	if (typeid(out).name() == typeid(ofstream).name())
		out << list.Size() << '\n';
	out << list.Size() << '\n';

	MyTwoList<T> temp;

	temp.setFirst(list.first());
	while (temp.first() != list.last()) {
		out << temp.first()->data << ' ';
		temp.setFirst(temp.first()->next);
	}
	out << temp.first()->data;

	return out;
}

//Ввод
template<class T>
istream& operator>>(istream& in, MyTwoList<T>& list) {
	int count, size_temp;
	if (typeid(in).name() == typeid(ifstream).name())
		in >> count;

	in >> size_temp;

	for (int i = 0; i < size_temp; i++) {
		T _data;
		in >> _data;
		list.push_back(_data);
	}
	return in;
}

int main() {
	SmartPhone myPhone{ Model::Xiaomi, 6.67, 5, 5000,8, 500 };
	cout << myPhone << '\n';


	MyTwoList<SmartPhone> test;
	for (int i = 0; i < 10; i++) {
		SmartPhone random{ static_cast<Model>(Random::get(1,9)),static_cast<double>(Random::get(4,7)),Random::get(0,6),Random::get(1200,6000),Random::get(5,12),static_cast<double>(Random::get(100,3000)) };
		test.push_back(random);
	}
	test.print();

	cout << "Search\n";
	cout << test.find_el(myPhone);

	cout << "Filtr\n";
	test.filtr(myPhone).print();

	MyTwoList<int> listik;
	cout << "Push back 3 2 4\n";
	listik.push_back(3); listik.push_back(2); listik.push_back(4);
	cout << listik[0] << ' ' << listik[1] << ' ' << listik[2] << '\n';

	listik.print();
	cout << "Size is " << listik.Size() << '\n';
	cout << listik;

	cout << "Insert 5 1, 5 1, 5 1, 5 1\n";
	listik.InsertAt(5, 1); listik.InsertAt(5, 1); listik.InsertAt(5, 1); listik.InsertAt(5, 1);
	listik.print();
	cout << "Size is " << listik.Size() << '\n';

	cout << "erase 3 0 0\n";
	listik.erase(3); listik.erase(0); listik.erase(0);
	listik.print();
	cout << "Size is " << listik.Size() << '\n';

	cout << "Pop back + pop_front\n";
	listik.pop_back();
	listik.pop_front();
	listik.print();
	cout << "Size is " << listik.Size() << '\n';

	cout << "Push front 8 9\n";
	listik.push_front(8);
	listik.push_front(9);
	listik.print();
	cout << "Size is " << listik.Size() << '\n';

	MyTwoList<int> listik2;
	cout << "rand fill\n";
	listik2.rand_fill();
	listik2.print();
	cout << "Size is " << listik2.Size() << '\n';

	cout << "Listik2 find (2) ";
	cout << listik2.find(2) << '\n';
	cout << "Listik find (2) ";
	cout << listik.find(2) << '\n';

	listik.print();
	MyTwoList<int> listik3;
	cout << "listik3=listik\n";
	listik3 = listik;
	listik3.print();
	cout << "Size is " << listik3.Size() << '\n';

	cout << "Listik3 = listik3\n";
	listik3 = listik3;
	listik3.print();
	cout << "Size is " << listik3.Size() << '\n';


	int arr[10];
	for (int i = 0; i < 10; i++) {
		arr[i] = Random::get(1, 40);
		cout << arr[i] << ' ';
	}

	cout << '\n';

	MyTwoList<int> listik4{ arr };
	listik4.print();

	MyTwoList<int>* ptr = new MyTwoList<int>{ arr };
	ptr->print();

	ofstream fout;
	fout.open("test.txt", ios::out);
	if (fout) {
		listik4.save(fout);
		fout.close();
	}

	cout << '\'n';
	MyTwoList<int> novi;
	MyTwoList<int> novi2;
	ifstream fin("test.txt");
	if (fin) {
		fin >> novi;
		fin.close();
		cout << "\n" << novi;
	}
	delete ptr;

	cout << '\n';
	system("pause");
	return 0;
}