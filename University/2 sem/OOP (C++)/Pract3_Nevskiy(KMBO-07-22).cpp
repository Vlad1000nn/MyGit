#include <iostream>

using namespace std;

//Схема наследования
//		A1	--------	B1	--
//				x				x C1
//		A2	--------	B2	--



class A1
{
protected:
	int a1;
public:

	A1(int V1 = 0)
	{
		a1 = V1;
		cout << "A1 constructor\n";
	}

	virtual void print()
	{
		cout << "A1\n";
	}

	virtual void show()
	{
		cout << "a1= " << a1 << '\n';
	}

	~A1()
	{
		cout << "A1 destructor\n";
	}

};

class A2
{
protected:
	int a2;
public:

	A2(int V2 = 0)
	{
		a2 = V2;
		cout << "A2 constructor\n";
	}

	virtual void print()
	{
		cout << "A2\n";
	}

	virtual void show()
	{
		cout << "a2 =" << a2 << '\n';
	}

	~A2()
	{
		cout << "A2 destructor\n";
	}
};


class B1 : virtual public A1, virtual public A2
{
protected:
	int b1;
public:

	B1(int V = 0, int V1 = 0, int V2 = 0) : A1(V1), A2(V2)
	{
		b1 = V;
		cout << "B1 constructor\n";
	}

	virtual void print() override
	{
		cout << "B1\n";
	}

	virtual void show() override
	{
		cout << "a1 = " << a1 << ", a2 = " << a2 << ", b1 = " << b1 << '\n';
	}

	~B1()
	{
		cout << "B1 destructor\n";
	}

};

class B2 : virtual public A1, virtual public A2
{
protected:
	int b2;
public:
	B2(int V = 0, int V1 = 0, int V2 = 0) : A1(V1), A2(V2)
	{
		b2 = V;
		cout << "B2 constructor\n";
	}

	virtual void print() override
	{
		cout << "B2\n";
	}

	virtual void show() override
	{
		cout << "a1 = " << a1 << ", a2 = " << a2 << ", b2 = " << b2 << '\n';
	}

	~B2()
	{
		cout << "B2 destructor\n";
	}

};


class C1 : public B1, public B2
{
protected:
	int c1;
public:
	C1(int V = 0, int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0, int V5 = 0, int V6 = 0) : B1(V1, V5, V6), B2(V4, V2, V3)
	{
		c1 = V;
		cout << "C1 constructor\n";
	}

	void print() override
	{
		cout << "C1\n";
	}

	void show() override
	{
		cout << "a1 = " << a1 << ", a2 = " << a2 << ", b1 = " << b1 << ", b2 = " << b2 << ", c1 = " << c1 << '\n';
	}

	~C1()
	{
		cout << "C1 destructor\n";
	}
};



int main()
{
	cout << "For A1:\n";
	A1 obj1{ 1 };
	cout << "For A2:\n";
	A2 obj2{ 2 };
	cout << "For B1:\n";
	B1 obj3{ 3,4,5 };
	cout << "For B2:\n";
	B2 obj4{ 6,7,8 };
	cout << "For C1:\n";
	C1 obj5{ 9,10,11,12,13 };

	A1* ptr1 = &obj3;
	A2* ptr2 = &obj5;

	obj1.print();
	obj1.show();

	obj2.print();
	obj2.show();

	obj3.print();
	obj3.show();

	obj4.print();
	obj4.show();

	obj5.print();
	obj5.show();

	ptr1->print();
	ptr1->show();

	ptr2->print();
	ptr2->show();


	return 0;
}