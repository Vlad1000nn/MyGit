#include "Judy.h"

#include <iterator> // for std::bidirectional_iterator_tag, std::reverse_iterator
#include <utility>  // for std::pair
#include <cstddef>  // for std::ptr_diff_t
#include <iostream> // for std::ostream, std::istream

// Для конструкторов
#include <vector>   // for std::vector
#include <set>      // for std::set, std::multiset
#include <bitset>   // for std::bitset


class JudyIteratorFactory {
private:

    // Класс-родитель для итераторов
    template<typename Treeptr_>
    class iterator_base {
    public:

        using iterator_category = std::bidirectional_iterator_tag;  // Категория итераторов(на основе нашего контейнера)
        using value_type =  std::pair<const Word_t, int>;
        using difference_type = std::ptr_diff_t;    // необходимо определить, не используется, будет std::distance O(n)
        using pointer = value_type*;
        using reference = value_type; // с ссылкой проблемы, но наш контейнер и не предоставляет доступ по ссылке к элементам, поэтому ОК
        
    protected:
        
        Treeptr_ tree_;
        Word_t current_Index__;
        
        iterator_base(Treeptr_ tree, const Word_t Index_)
        : tree_(tree)
        , current_Index__(Index_)
        { }
        
    public:
        
        iterator_base()
        : tree_(nullptr_)
        , current_Index__(Judy1::npos)
        { }

        iterator_base(const iterator_base& other) = default;
        
        iterator_base& operator=(const iterator_base& other) = default;
        
        iterator_base& operator++()
        {
            if(tree_ && current_Index__ != Judy1::npos)
            current_Index__ = tree_->next(current_Index__);
            return *this;
        }
        
        iterator_base& operator--()
        {
            if(tree_)
            current_Index__ = tree_->prev(current_Index__);
            return *this;
        }

        reference operator*()  const
        {
            if(tree_ && current_Index__ != Judy1::npos)
            return value_type(current_Index__, tree_->test(current_Index__));
            // можно бросить исключение в целом, да и в предыдщух методах тоже
            return reference(Judy1::npos, 0);
        }
        
        // Вспомогательный класс для оператора стрелки(для решения проблемы с временными объектами)
        class arr_ow_proxy {
            private:
            
            value_type value_;
            
            public:
            
            explicit arr_ow_proxy(value_type value)
            : value_(value)
            { }
            
            auto operator->()   const -> decltype(&value_)
            {
                return &value_;
            } 
            
            ~arr_ow_proxy() = default;
            
        };
        // arr_ow_proxy
        
        arr_ow_proxy operator->()    const
        {
            return arr_ow_proxy(operator*());
        }
        
        bool operator==(const iterator_base& other)  const
        {
            return tree_ == other.tree_ && current_Index__ == other.current_Index__;
        }
        
        bool operator!=(const iterator_base& other)  const
        {
            return !(*this == other);
        }
        
        ~iterator_base() = default;

    };
    // iterator_base
    
    friend class Judy1;
    
};

// Обёртка для класса Judy1 (для удобства использования) (С++17 и выше)
// (нужно ли по ссылке передавать?)

/*
ОК:
    
    for(auto it : j) { }                        
    for(const auto& it : j) { }             
    for(auto [key, val] : j) { }            
    for(const auto& [key, val] : j) { }     

НЕ ОК:
    
    for(auto& it : j) { }                   
    for(auto& [key, val] : j) { }           
*/


class Judy1 {
    private:
    
    mutable int Rc_int__;     // код возврата функций
    mutable Word_t Rc_word__; // число возврата(колво байт)
    mutable Word_t Index__;   
    
    Pvoid_t arr__;    // Указатель на корень массива

    inline static bool debug_ = false;
    
public:
    
    // Для алгоритмов, если что-то не найдено
    inline static constexpr Word_t npos = static_cast<Word_t>(-1);
    
    // Некоторые std::cout для отладки
    static void set_debug_mode(const bool value)
    {
        debug_ = value;
    }
   
    // Базовый конструктор
    Judy1() 
        : Rc_int__(0)
        , Rc_word__(0)
        , Index__(0)
    { 
        arr__ = (Pvoid_t) NULL;
    }

    // Конструктор на основе списка(устанавливает 1 в указанные индексы)
    Judy1(std::initializer_list<Word_t> init_list) : Judy1()
    {
        for(const auto& it : init_list)
            set(it);
    }

    // Конструктор на основе вектора(устанавливает 1 в указанные индексы(значения вектора))
    explicit Judy1(const std::vector<Word_t>& vec) : Judy1()
    {
        for(const auto& it : vec)
            set(it);
    }

    // Конструктор на основе множества(устанавливает 1 в указанные индексы(значения множества))
    explicit Judy1(const std::set<Word_t>& svec) : Judy1()
    {
        for(const auto& it : svec)
            set(it);
    }
    // Конструктор на основе мультимножества(устанавливает 1 в указанные индексы(значения мультимножества))
    explicit Judy1(const std::multiset<Word_t>& msvec) : Judy1()
    {
        for(const auto& it : msvec)
            set(it);
    }

    // Конструктор на основе std::bitset
    template<std::size_t Nb>
    explicit Judy1(const std::bitset<Nb>& bits) : Judy1()
    {
        std::size_t i;
        for(i = 0; i < Nb; ++i)
            if(bits[i])
                set(i);
    }
    
    
    // Конструктор на основе итераторов контейнеров(для Judy1 требуется (*first).first)
    template<typename It>
    Judy1(It first, It last) : Judy1()
    {
        for(;first != last; ++first)
            set(*first);
    }
    
    // Конструктор на основе итераторов Judy1
    //Judy1(Judy1::iterator first, Judy1::iterator last) :Judy1()
    //{
    //    for(; first != last;++first)
    //        set((*first).first);
    //}

    // Включает бит по индексу Index_ (возвращает 0 если бит уже был включён)
    int set(const Word_t& Index_)
    {
        J1S(Rc_int__, arr__, Index_);
        return Rc_int__;
    }

    // Выключает бит по индексу Index_ (возвращает 0, если бит уже был выключен)
    int unset(const Word_t& Index_) 
    {
        J1U(Rc_int__, arr__, Index_);
        return Rc_int__;
    }

    // Возвращает значение бита по индексу Index_(если такой не существует то 0)
    int test(const Word_t& Index_)    const  
    {
        J1T(Rc_int__, arr__, Index_);
        return Rc_int__;
    }
    
    // Возвращает количество битов в диапазоне [Index_1, Index_2]
    // [0, -1] - возвращает количество вообще всех битов установленных (-1 в unsigned = 111..111)
    // ***Протестировать невалидные значения
    Word_t count(const Word_t& Index_1, const Word_t& Index_2)    const
    {
        J1C(Rc_word__, arr__, Index_1, Index_2);
        return Rc_word__;
    }

    // Возвращает n-й установленный бит (либо -1 если не найден такой), Word_t unsigned
    // непонятно ещё если n = 0, чтото про fully populated arr_ay
    Word_t ncount(const Word_t& n)  const
    {
        J1BC(Rc_int__, arr__, n, Index__);
        return (Rc_int__ ? Index__ : Judy1::npos);
    }

    // Возвращает количество байт которые в данный момент занимает массив
    // (очень быстрый, особенно после set/unset)
    Word_t memused()    const
    {
        J1MU(Rc_word__, arr__);
        return Rc_word__;
    }
    
    // Возвращает первый попавшийся бит начиная с Index_(начать с 0 чтобы найти в массиве в целом первый бит)
    Word_t first(const Word_t& Index_ = 0)   const 
    {
        Index__ = Index_;
        J1F(Rc_int__, arr__, Index__);
        return (Rc_int__ ? Index__ : Judy1::npos);
    }

    // Возвращает первый попавшийся бит начиная с Index_+1
    Word_t next(const Word_t& Index_)    const
    {
        Index__ = Index_;
        J1N(Rc_int__, arr__, Index__);
        return (Rc_int__ ? Index__ : Judy1::npos);
    }

    // ищет начиная с Index_ первый бит (в обратном порядке, т.е. справа налево)
    // -1 для поиска последнего в целом
    Word_t last(const Word_t& Index_)    const
    {
        Index__ = Index_;
        J1L(Rc_int__, arr__, Index__);
        return (Rc_int__ ? Index__ : Judy1::npos);
    }

    // ищет начиная с Index_-1 первый бит
    Word_t prev(const Word_t& Index_)    const
    {
        Index__ = Index_;
        J1P(Rc_int__, arr__, Index__);
        return (Rc_int__ ? Index__ : Judy1::npos);
    }

    // начиная с Index_ находит первый 0
    Word_t first_empty(const Word_t& Index_) const
    {
        Index__ = Index_;
        J1FE(Rc_int__, arr__, Index__);
        return (Rc_int__ ? Index__ : Judy1::npos);
    }

    // начиная с Index_+1 находит первый 0
    Word_t next_empty(const Word_t& Index_)  const
    {
        Index__ = Index_;
        J1NE(Rc_int__, arr__, Index__);
        return (Rc_int__ ? Index__ : Judy1::npos);
    }

    // начиная с Index_ находит первый 0 в обратном порядке (справа налево)
    Word_t last_empty(const Word_t& Index_)  const
    {
        Index__ = Index_;
        J1LE(Rc_int__, arr__, Index__);
        return (Rc_int__ ? Index__ : Judy1::npos);
    }
    
    // начиная с Index_-1 находит первый 0 в обратном порядке (справа налево)
    Word_t prev_empty(const Word_t& Index_)  const
    {
        Index__ = Index_;
        J1PE(Rc_int__, arr__, Index__);
        return (Rc_int__ ? Index__ : Judy1::npos);
    }
    
    // Класс-имитация доступа к отдельным битам
    class reference {
        private:

        friend class Judy1;
        
        Judy1& tree_;    // Ссылка на родительский Judy1
        Word_t Index__;   // Индекс бита
        
        reference();
        
        public:
        
        reference(Judy1& tree, const Word_t Index_) 
        : tree_(tree)
        , Index__(Index_) 
        { }
        
        reference(const reference&) = default;
        
        // перегрузка оператора= для bool
        reference& operator=(bool value) 
        {
            value ? tree_.set(Index__) : tree_.unset(Index__);
            return *this;
        }

        // Перегрузка оператора= для int
        reference& operator=(int value)
        {
            value ? tree_.set(Index__) : tree_.unset(Index__);
            return *this;
        }
        
        // Оператор присваивания (для tree[Index_] = tree_[other])
        reference& operator=(const reference& other) 
        {
            tree_[Index__] = static_cast<bool>(other);
            return *this;
        }
        
        // Оператор для приведения в тип bool
        operator bool() const 
        {
            return tree_.test(Index__);
        }
        
        // Оператор для приведения в тип int
        operator int()  const
        {
            return tree_.test(Index__);
        }
        
        // Оператор инвертирования
        bool operator~()    const
        {
            return !tree_.test(Index__);
        }
        
        // Перегрузка оператора вывода
        friend std::ostream& operator<<(std::ostream& out, const reference& obj)
        {
            out << static_cast<int>(obj);
            return out;
        }
        
        // Перегрузка оператора ввода
        friend std::istream& operator>>(std::istream& in, reference& obj)
        {
            int tmp; in >> tmp;
            obj = tmp;
            return in;
        }
        
        ~reference() = default;

    };
    // reference
    
    // Оператор [] 
    reference operator[](const Word_t& Index_) 
    {
        return reference(*this, Index_);
    }


    
public:

    // Классический итератор по Judy дереву
    class iterator : public JudyIteratorFactory::iterator_base<Judy1*> {
    private:
        
        friend class Judy1;
        friend class const_iterator;

        explicit iterator(Judy1* tree, const Word_t Index_) : iterator_base<Judy1*>(tree, Index_)
        { }

    public:

        iterator() = default;

        iterator(const iterator& other) = default;
        iterator& operator=(const iterator& other) = default;

        using iterator_base<Judy1*>::operator++;
        using iterator_base<Judy1*>::operator--;

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        ~iterator() = default;

    };
    // iterator

    
    //    Константный итератор, позволяет обходить const Judy дерево(без права на изменение)
    class const_iterator : public JudyIteratorFactory::iterator_base<const Judy1*> {
    private:

        friend class Judy1;

        explicit const_iterator(const Judy1* tree, const Word_t Index_) : iterator_base<const Judy1*>(tree, Index_)
        { }

    public:

        const_iterator() = default;

        const_iterator(const const_iterator& other)= default;
        const_iterator& operator=(const const_iterator& other) = default;

        const_iterator(const iterator& other) : iterator_base<const Judy1*>(other.tree_, other.current_Index__)
        { }

        using iterator_base<const Judy1*>::operator++;
        using iterator_base<const Judy1*>::operator--;

        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        ~const_iterator() = default;

    };
    // const_iterator

    // Обратные итераторы просто сделаем на основе обычных 
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Все итераторы типа begin(), end()
    iterator begin()
    {
        return iterator(this, this->first(0));
    }

    iterator end()
    {
        return iterator(this, Judy1::npos);
    }

    const_iterator begin()  const
    {
        return const_iterator(this, this->first(0));
    }

    const_iterator cbegin() const
    {
        return const_iterator(this, this->first(0));
    }
    
    const_iterator end()    const
    {
        return const_iterator(this, Judy1::npos);
    }

    const_iterator cend()   const
    {
        return const_iterator(this, Judy1::npos);
    }

    reverse_iterator rbegin() 
    {
        return reverse_iterator(end());
    }

    reverse_iterator rend() 
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator rend()   const
    {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crbegin()    const
    {
        return const_reverse_iterator(cend());
    }

    const_reverse_iterator crend()  const
    {
        return const_reverse_iterator(cbegin());
    }

    // Деструктор для очищения данных
    ~Judy1()
    {
        J1FA(Rc_word__, arr__); // очищает весь массив, количество очищенных байт в Rc_word_
        if(debug_)
            std::clog << "Free " << Rc_word__ << " bytes" << std::endl;
    }

};
    // Judy1


#include <bitset>
#include <map>

#include <cassert>
#include <vector>
#include <limits>
#include <algorithm>

void stress_test_judy1_iterators() {
    std::cout << "=== Judy1 Iterator Stress Test ===" << std::endl;
    
    // Тест 1: Пустой контейнер
    {
        std::cout << "\nTest 1: Empty container" << std::endl;
        Judy1 j;
        assert(j.begin() == j.end());
        assert(j.cbegin() == j.cend());
        assert(j.rbegin() == j.rend());
        assert(j.crbegin() == j.crend());
        std::cout << "✓ Empty container test passed" << std::endl;
    }
    
    // Тест 2: Один элемент
    {
        std::cout << "\nTest 2: Single element" << std::endl;
        Judy1 j;
        j.set(42);
        
        auto it = j.begin();
        assert(it != j.end());
        assert((*it).first == 42);
        assert((*it).second == 1);
        ++it;
        assert(it == j.end());
        
        // Reverse
        auto rit = j.rbegin();
        assert(rit != j.rend());
        assert((*rit).first == 42);
        std::cout << "✓ Single element test passed" << std::endl;
    }
    
    // Тест 3: Множество элементов
    {
        std::cout << "\nTest 3: Multiple elements" << std::endl;
        Judy1 j;
        std::vector<Word_t> test_values = {1, 10, 100, 1000, 10000, 
                                          std::numeric_limits<Word_t>::max() - 1};
        
        // Заполнение
        for(auto val : test_values) {
            j.set(val);
        }
        
        // Прямая итерация
        std::vector<Word_t> forward_result;
        for(auto it = j.begin(); it != j.end(); ++it) {
            forward_result.push_back((*it).first);
            assert((*it).second == 1);
        }
        assert(forward_result == test_values);
        
        // Range-based for
        size_t idx = 0;
        for(const auto& [key, val] : j) {
            assert(key == test_values[idx++]);
            assert(val == 1);
        }
        
        // Обратная итерация
        std::vector<Word_t> reverse_result;
        for(auto rit = j.rbegin(); rit != j.rend(); ++rit) {
            reverse_result.push_back((*rit).first);
        }
        std::reverse(reverse_result.begin(), reverse_result.end());
        assert(reverse_result == test_values);
        
        std::cout << "✓ Multiple elements test passed" << std::endl;
    }
    
    // Тест 4: Операторы ++ и --
    {
        std::cout << "\nTest 4: Increment/Decrement operators" << std::endl;
        Judy1 j;
        j.set(10);
        j.set(20);
        j.set(30);
        
        auto it = j.begin();
        assert((*it).first == 10);
        
        // Префиксный ++
        ++it;
        assert((*it).first == 20);
        
        // Постфиксный ++
        auto it2 = it++;
        assert((*it2).first == 20);
        assert((*it).first == 30);
        
        // Префиксный --
        --it;
        assert((*it).first == 20);
        
        // Постфиксный --
        auto it3 = it--;
        assert((*it3).first == 20);
        assert((*it).first == 10);
        
        // --end()
        auto end_it = j.end();
        --end_it;
        assert((*end_it).first == 30);
        
        std::cout << "✓ Increment/Decrement test passed" << std::endl;
    }
    
    // Тест 5: Константные итераторы
    {
        std::cout << "\nTest 5: Const iterators" << std::endl;
        Judy1 j;
        j.set(5);
        j.set(15);
        
        const Judy1& cj = j;
        auto cit = cj.begin();
        assert(cit != cj.end());
        assert((*cit).first == 5);
        
        // Конверсия iterator -> const_iterator
        Judy1::iterator it = j.begin();
        Judy1::const_iterator cit2 = it;
        assert(cit2 == cj.begin());
        
        std::cout << "✓ Const iterators test passed" << std::endl;
    }
    
    // Тест 6: Операторы сравнения
    {
        std::cout << "\nTest 6: Comparison operators" << std::endl;
        Judy1 j;
        j.set(1);
        j.set(2);
        
        auto it1 = j.begin();
        auto it2 = j.begin();
        assert(it1 == it2);
        assert(!(it1 != it2));
        
        ++it2;
        assert(it1 != it2);
        assert(!(it1 == it2));
        
        std::cout << "✓ Comparison operators test passed" << std::endl;
    }
    
    // Тест 7: arr_ow operator
    {
        std::cout << "\nTest 7: arr_ow operator" << std::endl;
        Judy1 j;
        j.set(123);
        
        auto it = j.begin();
        assert(it->first == 123);
        assert(it->second == 1);
        
        std::cout << "✓ arr_ow operator test passed" << std::endl;
    }
    
    // Тест 8: STL алгоритмы
    {
        std::cout << "\nTest 8: STL algorithms" << std::endl;
        Judy1 j;
        for(Word_t i = 0; i < 10; ++i) {
            j.set(i * i);  // 0, 1, 4, 9, 16, 25, 36, 49, 64, 81
        }
        
        // std::distance
        auto dist = std::distance(j.begin(), j.end());
        assert(dist == 10);
        
        // std::find_if
        auto found = std::find_if(j.begin(), j.end(), 
            [](const auto& p) { return p.first == 25; });
        assert(found != j.end());
        assert((*found).first == 25);
        
        // std::count_if
        auto count = std::count_if(j.begin(), j.end(),
            [](const auto& p) { return p.first > 20; });
        assert(count == 5);  // 25, 36, 49, 64, 81
        
        std::cout << "✓ STL algorithms test passed" << std::endl;
    }
    
    // Тест 9: Граничные случаи
    {
        std::cout << "\nTest 9: Edge cases" << std::endl;
        Judy1 j;
        
        // Максимальное значение
        j.set(Judy1::npos - 1);
        j.set(0);
        j.set(1);
        
        auto it = j.begin();
        assert((*it).first == 0);
        ++it;
        assert((*it).first == 1);
        ++it;
        assert((*it).first == Judy1::npos - 1);
        
        std::cout << "✓ Edge cases test passed" << std::endl;
    }
    
    // Тест 10: Модификация во время итерации
    {
        std::cout << "\nTest 10: Modification during iteration" << std::endl;
        Judy1 j;
        j.set(10);
        j.set(20);
        j.set(30);
        
        // Собираем ключи
        std::vector<Word_t> keys;
        for(const auto& [key, val] : j) {
            keys.push_back(key);
        }
        
        // Модифицируем
        for(auto key : keys) {
            j[key] = 0;  // unset
        }
        
        assert(j.begin() == j.end());  // Должен быть пустым
        
        std::cout << "✓ Modification test passed" << std::endl;
    }
    
    std::cout << "\n=== All iterator tests passed! ===" << std::endl;
}

#include <map>

int main(int argc, char** argv) {


    //stress_test_judy1_iterators();
    
    std::vector<unsigned long> vec = {1,2,3};
    std::set<unsigned long> svec = {1,2,3};
    std::multiset<unsigned long> msvec = {1, 2, 3, 1, 2, 3};
    
    Judy1 j1 = {1, 2, 3};
    Judy1 j2(vec.begin(), vec.begin()+2);
    Judy1 j3(svec);
    Judy1 j4(msvec);
    Judy1::iterator it1 = j1.begin();
    it1++;
    Judy1 j5;//(j1.begin(), it1);

    std::cout << "J1:" << '\n';
    for(auto [key, val] : j1)
        std::cout << key << ": " << val << '\n';  
    
    std::cout << "J2:" << '\n';
    for(auto [key, val] : j2)
        std::cout << key << ": " << val << '\n';
    
    std::cout << "J3:" << '\n';
    for(auto [key, val] : j3)
        std::cout << key << ": " << val << '\n';
    
    std::cout << "J4:" << '\n';
    for(auto [key, val] : j4)
        std::cout << key << ": " << val << '\n';
    
    std::cout << "J5:" << '\n';
    for(auto [key, val] : j5)
        std::cout << key << ": " << val << '\n';

    return 0;
}
