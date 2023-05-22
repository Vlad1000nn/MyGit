#include <iostream>
#include <vector>
#include <random>
#include <utility>
#include <fstream>

using namespace std;

//Генерация случайных чисел
namespace Random
{
    //Генератор
    std::mt19937 mt{ std::random_device{}() };

    //Получение значения в диапазоне [min,max]
    int get(int min, int max)
    {
        std::uniform_int_distribution die{ min, max };
        return die(mt);
    }
}


//Группы
class Group
{
    //Объекты
    class Object
    {
    public:
        //Вес объекта
        int weight;
        //Стоимость объекта
        int price;
        //Оценка объекта, после чистки класса
        double second_value{};
        //Конструктор по умолчанию
        Object()
        {
            generator();
        }

        //Базовый конструктор
        Object(pair<int, int> values)
        {
            weight = values.first;
            price = values.second;
        }

        //Генератор предметов
        void generator()
        {
            weight = Random::get(1, 1000);
            price  =  Random::get(1, 1000);
        }

        //Оператор сравнения
        bool operator >(const Object& x) const
        {
            return (this->weight <= x.weight) && (this->price >= x.price);
        }

        //Оператор равенства
        bool operator ==(const Object& x) const
        {
            return (this->weight == x.weight) && (this->price == x.price);
        }

        //Оператор присваивания
        Object& operator=(pair<int,int> values)
        {
            weight = values.first;
            price = values.second;
            return *this;
        }

        void print() const
        {
            cout << price << ' ' << weight << ' ' << second_value;
        }
    };

    // Элементы нашей группы
    vector<Object> elements;

    // Нулевой элемент
    Object null_el{make_pair(0,0)};

public:
    //Конструктор по умолчанию
    Group()
        :elements(10)
    {}

    // Базовый конструктор
    Group(const vector<pair<int, int>>& vec)
    {
        elements.resize(vec.size());
        for (int i = 0; i < vec.size(); ++i)
            elements[i] = { vec[i].first,vec[i].second };
    }

    //Геттеры
    //Количество элементов
    int get_count() const
    {
        return static_cast<int>(elements.size());
    }
    //Вес элемента с индексом index
    int get_weight(const int index) const
    {
        return elements[index].weight;
    }
    //Цена элемента с индексом index
    int get_price(const int index) const
    {
        return elements[index].price;
    }
    //Новое значение элемента с индексом index
    double get_value(const int index) const
    {
        return elements[index].second_value;
    }
    //Пара(вес,цена) элемента с индексом index
    pair<int, int> get_object(const int index) const
    {
        return make_pair(elements[index].price, elements[index].weight);
    }

    //Убираем ненужные нам элементы
    void reduction()
    {
        //Убираем все элементы,над которыми доминируют
        for (int i = 0; i < elements.size() - 1; ++i)
        {
            for (int g = i + 1; g < elements.size(); ++g)
            {
                if (elements[i] > elements[g] && !(elements[g] == null_el)) 
                    elements[g] = null_el;
                else if (elements[g] > elements[i] && !(elements[i] == null_el))
                    elements[i] = null_el;
            }
        }
        clear();
        sorting();

        //Убираем элементы, над которыми имеется LP-доминация
        if (elements.size() > 2)
        {
            for (int i = 0; i < elements.size()-2; ++i)
            {
                for (int g = i + 2; g < elements.size(); ++g)
                {
                    for (int k = i + 1; k < g; ++k)
                    {
                        if (!(elements[i] == null_el) && !(elements[g] == null_el) && !(elements[k] == null_el))
                        if (double(elements[g].price - elements[k].price) / double(elements[g].price - elements[k].price) >=
                            double(elements[k].price - elements[i].price) / double(elements[k].weight - elements[i].weight))
                            elements[k] = null_el;
                    }
                }
            }
        }
        clear();
        sorting();
        // Теперь получаем новые значения в нашей группе
        creating_new_values();
    }

    //Сортировка элементов группы по весу
    void sorting()
    {
        sort(elements.begin(), elements.end(),[&](const auto x, const auto y)
            { return y.weight > x.weight; }   );
    }

    //Очистка мусора из группы
    void clear()
    {
        for (int i = 0; i < elements.size(); ++i)
        {
            if (elements[i] == null_el) {
                elements.erase(elements.begin() + i);
                --i;
            }
        }
    }

    //Создание новых значений, после чистки группы
    void creating_new_values()
    {
        if (elements.size() < 2)
            return;
        for (int i = 1; i < elements.size(); ++i)
            elements[i].second_value = static_cast<double>(elements[i].price - elements[i - 1].price) / static_cast<double>(elements[i].weight - elements[i - 1].weight);

    }

    void print() const
    {
        cout << "\nGroup:\n";
        for (int i = 0; i < elements.size(); ++i) {
            elements[i].print();
            cout << '\n';
        }
    }
};

// Пихаем новые значения в вектор и сортируем
void push_new_values(const vector<Group>& vec, vector < pair<double,pair<int,int>>>& it)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i].get_count() < 2)
            continue;

        for (int g = 1; g < vec[i].get_count(); ++g)
            it.push_back(make_pair(vec[i].get_value(1), make_pair(i, g)));
    }

    //Сортируем по значениям
    sort(it.begin(), it.end(), [&](const auto x, const auto y)
        {
            return x.first > y.first;
        });
}


//Рюкзак
class Knapsack
{
    //Вес рюкзака
    int weight;
    
    // Итоговая ценность рюкзака
    long long get_sum(const vector<pair<int, int>>& answer) const
    {
        long long ans{};
        for (int i = 0; i < answer.size(); ++i)
            ans += answer[i].first;
        return ans;
    }

public:
    //Конструктор по умолчанию
    Knapsack(int _weight = 1000)
    {
        weight = _weight;
    }
    // Геттер
    // Вес рюкзака
    int get_weight() const
    {
        return weight;
    }

    //Решение
    void solve(vector<Group>& vec)
    {
        int curr_weight = 0;

        vector <pair<int, int>> answer(vec.size());
        //Кладём минимальные по весу из каждой группы
        for (int i = 0; i < vec.size(); ++i)
        {
            answer[i] = vec[i].get_object(0);
            curr_weight += vec[i].get_weight(0);
        }
       
        //Вектор пара(новое значение, пара(номер группы,номер элемента в группе)
        vector<pair<double, pair<int, int>>> it;
        push_new_values(vec, it);

        //Если превысили — невозможно дать ответ 
        if (curr_weight > weight) {
            cout << "Ответ: невозможно\n";
            return;
        }
        //Идеально уложились
        else if (curr_weight == weight)
        {
            sort(answer.begin(), answer.end(), [&](const auto x, const auto y)
                {
                    if (x.first == y.first)
                    return x.second > y.second;
                    else return x.first < y.first;
                });
            print_answer(answer,curr_weight);
        }

        // Теперь будем брать самые лучшие значения среди новых элементов и поочердёно пихать их в рюкзак.
        for (int i = 0; i < it.size(); ++i)
        {
            if (good_choise(answer, it, i, vec,curr_weight))
            {
                curr_weight -= answer[it[i].second.second].second;
                answer[it[i].second.first] = vec[it[i].second.first].get_object(it[i].second.second);
                curr_weight += answer[it[i].second.first].second;
            }
        }

        sort(answer.begin(), answer.end(), [&](const auto x, const auto y)
            {
                if (x.second == y.second)
                return x.first < y.first;
                else return x.second < y.second;
            });

        //Ответ
        print_answer(answer, curr_weight);
       
    }

    // Проверяем, можем ли мы заменить элемент на новый
    bool good_choise(const vector < pair<int, int>> answer, const vector<pair<double,pair<int,int>>>& it,const int index, const vector<Group>& vec,
        const int curr_weight) const
    {
        int buff_weight = curr_weight;
        buff_weight -= answer[it[index].second.first].second;
        buff_weight += vec[it[index].second.first].get_weight(it[index].second.second);
        return (buff_weight <= weight);
    }

    void print_answer(const vector<pair<int, int>>& answer, const int curr_weight) const
    {
        cout << "Ответ:\n(цена, вес)\n";
        for (int i = 0; i < answer.size(); ++i)
            cout << answer[i].first << '\t' << answer[i].second << '\n';

        cout << "Итого занято: " << curr_weight << "\nЦенность:" << get_sum(answer) << '\n';
    }

   

};




int main()
{
    setlocale(LC_ALL, "rus");

    vector<Group> condition;

    //Считываем
    ifstream fin("test.in");
    if (fin)		//Елси файл открылся и всё ок
    {
        for (int index = 0; index < 10; ++index)
        {
            vector<pair<int, int>> input(10);
            for (int i = 0; i < 10; ++i)
            {
                fin >> input[i].second >> input[i].first;
            }
            condition.push_back({ input });
        }
            fin.close();			//Закрыть
        
    }


    for (int i = 0; i < condition.size(); ++i)
        condition[i].reduction();

    Knapsack knapsack;

    cout << "\nВес рюкзака:" << knapsack.get_weight() << '\n';

    knapsack.solve(condition);

	return 0;
}