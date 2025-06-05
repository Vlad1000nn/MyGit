#include "Judy.h"
#include <utility>      // for std::pair, std::swap
#include <stdexcept>    // for std::out_of_range
#include <iostream>     // for std::ostream, std::istream
#include <optional>     // for std::optional

namespace judy {
// ШАБЛОН JUDYL НЕ ОСОБО НУЖЕН, ПОДОЙДЁТ ТОЛЬКО ПРИ ИСПОЛЬЗОВАНИИ УКАЗАТЕЛЕЙ

// Обёртка для класса JudyL (для удобства использования)
// (нужно ли по ссылке передавать?)
// Index_ поменять Word_t на size_t
// что делать, static_cast или reinterpret_cast
// Вообще надо прям юзать JERR, PJERR, PPJERR
// template<typename Key, typename Type, cmp, alloc>
class JudyL {
private:

    using size_type = std::size_t;

    mutable int Rc_int_;     // код возврата функций
    mutable Word_t Rc_word_; // число возврата(колво байт)
    mutable Word_t Index_;   // JudyByCount

    mutable PWord_t PValue_;
    mutable void* ptr_;

    Pvoid_t arr_;    // Указатель на корень массива

    // Большого смысла пока не имеет, просто вывод в деструкторе количества освобождённой памяти
    inline static bool debug_ = false;

public:

    // Включает/выключает debug_
    static void set_debug_mode(const bool value)
    {
        debug_ = value;
    }

    // Базовый конструктор
    JudyL() 
        : Rc_int_(0)
        , Rc_word_(0)
        , Index_(0)
        , PValue_(nullptr)
        , ptr_(nullptr)
    { 
        arr_ = (Pvoid_t) NULL;
    }

    PWord_t insert(const Word_t& index)
    {
        Index_ = index;
        JLI(ptr_, arr_, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        
        return PValue_;
    }
    
    // удаление по индексу из массива. Возвращает 1 если успешно, 0 - если индекса не было, -1 если ошибка в malloc()
    int del(const Word_t& index) 
    {
        JLD(Rc_int_, arr_, index);
        return Rc_int_;
    }

    // возвращает указатель на элемент Index_, либо если его нет указатель на 0, либо указатель на -1 если malloc() ошибка
    PWord_t get(const Word_t& index)    const
    {
        JLG(ptr_, arr_, index);
        PValue_ = static_cast<PWord_t>(ptr_);
        return PValue_;
    }

    // Вовзаращет количество занятых индексов между Index_1 и Index_2 включительно
    // Для подсчёта всех - 0 и -1
    Word_t count(const Word_t& index1, const Word_t& index2)    const
    {  
        JLC(Rc_word_, arr_, index1, index2);
        return Rc_word_;
    }

    // возвращает n-й занятый элемент в массиве (n = 1 - первый)
    // Нужно сделать возврат пары значений
    std::pair<PWord_t, Word_t> ncount(const Word_t& n)  const
    {
        JLBC(ptr_, arr_, n, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(PValue_, Index_);
    }

    // Возвращает количество байт которые в данный момент занимает массив
    // (очень быстрый, особенно после Insert/Delete)
    Word_t memused()    const
    {
        JLMU(Rc_word_, arr_);
        return Rc_word_;
    }

    // Количество элементов
    size_type size()  const
    {
        return count(0, -1);
    }

    bool empty()    const
    {
        return size();
    }

    void clear()
    {
        JLFA(Rc_word_, arr_);
    }

    // Возвращает первый попавшийся бит начиная с Index_(начать с 0 чтобы найти в массиве в целом первый бит)
    std::pair<PWord_t, Word_t> first(const Word_t& index)   const
    {
        Index_ = index;
        JLF(ptr_, arr_, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(PValue_, Index_);
    }

    // Возвращает первый попавшийся бит начиная с Index_+1
    std::pair<PWord_t, Word_t> next(const Word_t& index)    const
    {
        Index_ = index;
        JLN(ptr_, arr_, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(PValue_, Index_);
    }

    // ищет начиная с Index_ первый бит (в обратном порядке, т.е. справа налево)
    std::pair<PWord_t, Word_t> last(const Word_t& index)    const
    {
        Index_ = index;
        JLL(ptr_, arr_, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(PValue_, Index_);
    }

    // ищет начиная с Index_-1 первый бит
    std::pair<PWord_t, Word_t> prev(const Word_t& index)    const
    {
        Index_ = index;
        JLP(ptr_, arr_, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(PValue_, Index_);
    }

    // начиная с Index_ находит первый 0
    std::optional<Word_t> first_empty(const Word_t& index) const
    {
        Index_ = index;
        JLFE(Rc_int_, arr_, Index_);
        return (Rc_int_ ? std::optional<Word_t>(Index_) : std::nullopt);
    }

    // начиная с Index_+1 находит первый 0
    std::optional<Word_t> next_empty(const Word_t& index)  const
    {
        Index_ = index;
        JLNE(Rc_int_ , arr_, Index_);
        return (Rc_int_ ? std::optional<Word_t>(Index_) : std::nullopt);
    }

    // начиная с Index_ находит первый 0 в обратном порядке (справа налево)
    std::optional<Word_t> last_empty(const Word_t& index)  const
    {
        Index_ = index;
        JLLE(Rc_int_, arr_, Index_);
        return (Rc_int_ ? std::optional<Word_t>(Index_) : std::nullopt);
    }

    // начиная с Index_-1 находит первый 0 в обратном порядке (справа налево)
    std::optional<Word_t> prev_empty(const Word_t& index)  const
    {
        Index_ = index;
        JLPE(Rc_int_, arr_, Index_);
        return (Rc_int_ ? std::optional<Word_t>(Index_) : std::nullopt);
    }


    class reference {
    private:

        friend class JudyL;

        JudyL& tree_;
        Word_t Index_;

    reference();

    public:

        reference(JudyL& tree, const Word_t index)
        : tree_(tree)
        , Index_(index)
        { 
            if(!tree_.get(Index_))
                tree_.insert(Index_);
        }


        reference(const reference&) = default;

        reference& operator=(Word_t value)
        {
            PWord_t current = tree_.get(Index_);
            *current = value;
            return *this;
        }

        reference& operator=(const reference& other)
        {
            tree_[Index_] = static_cast<Word_t>(other);
            return *this;
        }

        reference& operator+=(Word_t value) 
        {
            PWord_t current = tree_.get(Index_);
            *current += value;
            return *this;
        }

        reference& operator-=(Word_t value) 
        {
            PWord_t current = tree_.get(Index_);
            *current -= value;
            return *this;
        }

        reference& operator*=(Word_t value) 
        {
            PWord_t current = tree_.get(Index_);
            *current *= value;
            return *this;
        }

        reference& operator/=(Word_t value) 
        {
            PWord_t current = tree_.get(Index_);
            *current /= value;
            return *this;
        }

        reference& operator&=(Word_t value) 
        {
            PWord_t current = tree_.get(Index_);
            *current &= value;
            return *this;
        }

        reference& operator|=(Word_t value) 
        {
            PWord_t current = tree_.get(Index_);
            *current |= value;
            return *this;
        }

        reference& operator^=(Word_t value) 
        {
            PWord_t current = tree_.get(Index_);
            *current ^= value;
            return *this;
        }

        reference& operator++()
        {
            PWord_t current = tree_.get(Index_);
            ++(*current);
            return *this;
        }

        Word_t operator++(int)
        {
            PWord_t current = tree_.get(Index_);
            Word_t tmp = *current;
            ++(*current);
            return tmp;
        }

        operator Word_t()   const
        {
            return *tree_.get(Index_);
        }
        
        ~reference() = default;
        
    };
    
    reference operator[](const Word_t& index)
    {
        return reference(*this, index);
    }

    // Функция at() для доступа по ключу версии non-const и const
    Word_t& at(const Word_t& index)
    {
        get(index);
        if(PValue_ == nullptr)
            throw std::out_of_range("Judyl::at");
        
        return *PValue_;
    }
    
    const Word_t& at(const Word_t& index)   const
    {
        get(index);
        if(PValue_ == nullptr)
            throw std::out_of_range("Judyl::at");
            
        return *PValue_;
    }
        
    // Класс-родитель для итераторов
    template<typename Treeptr>
    class iterator_base {
        public:
        
        using iterator_category = std::bidirectional_iterator_tag;  // Категория итераторов(на основе нашего контейнера)
        using value_type =  std::pair<const Word_t, Word_t>;
        using difference_type = std::ptrdiff_t;    // необходимо определить, не используется, будет std::distance O(n)
        using pointer = value_type*;
        using reference = value_type; // с ссылкой проблемы, но наш контейнер и не предоставляет доступ по ссылке к элементам, поэтому ОК
        
        protected:
        
        Treeptr tree_;
        std::optional<Word_t> current_index_;
        
        iterator_base(Treeptr tree, const std::optional<Word_t> index)
        : tree_(tree)
        , current_index_(index)
        { }
        
        public:
        
        iterator_base()
        : tree_(nullptr)
        , current_index_(std::nullopt)
        { }
        
        iterator_base(const iterator_base& other) = default;
        
        iterator_base& operator=(const iterator_base& other) = default;
        
        iterator_base& operator++()
        {
            if(tree_ && current_index_.has_value()) {
                std::pair<PWord_t, Word_t> next_val = tree_->next(current_index_.value());
                current_index_ = (next_val.first ? std::optional<Word_t>(next_val.second) : std::nullopt);
            }
            // else UB
            return *this;
        }
        
        iterator_base& operator--()
        {
            if(tree_) {
                if(current_index_.has_value()) {
                    std::pair<PWord_t, Word_t> prev_val = tree_->prev(current_index_.value());
                    current_index_ = (prev_val.first ? std::optional<Word_t>(prev_val.second) : std::nullopt);
                }
                else {
                    std::pair<PWord_t, Word_t> last_val = tree_->last(static_cast<Word_t>(-1));
                    current_index_ = (last_val.first ? std::optional<Word_t>(last_val.second) : std::nullopt);
                }
            }
            // else UB
            
            return *this;
        }
        
        reference operator*()  const
        {
            if(tree_ && current_index_.has_value())
                return value_type(current_index_.value(), *tree_->get(current_index_.value()));
            
            throw std::runtime_error("Dereference invalid iterator");
        }
        
        // Вспомогательный класс для оператора стрелки(для решения проблемы с временными объектами)
        class arrow_proxy {
            private:
            
            value_type value_;
            
            public:
            
            explicit arrow_proxy(value_type value)
            : value_(value)
            { }
        
            auto operator->()   const -> decltype(&value_)
            {
                return &value_;
            } 
            
            ~arrow_proxy() = default;
            
        };
        // arr_ow_proxy
        
        arrow_proxy operator->()    const
        {
            return arrow_proxy(operator*());
        }
        
        bool operator==(const iterator_base& other)  const
        {
            return tree_ == other.tree_ && current_index_ == other.current_index_;
        }
        
        bool operator!=(const iterator_base& other)  const
        {
            return !(*this == other);
        }
        
        ~iterator_base() = default;
        
    };
    // iterator_base

    class iterator : public iterator_base<JudyL*> {
    private:

        friend class JudyL;
        friend class const_iterator;

        explicit iterator(JudyL* tree, std::optional<Word_t> index) : iterator_base<JudyL*>(tree, index)
        { }

    public:

        iterator() = default;
        iterator(const iterator& other) = default;
        iterator& operator=(const iterator& other) = default;

        using iterator_base<JudyL*>::operator++;
        using iterator_base<JudyL*>::operator--;

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

    class const_iterator : public iterator_base<const JudyL*>{
    private:

        friend class JudyL;

        explicit const_iterator(const JudyL* tree, const std::optional<Word_t> index) : iterator_base<const JudyL*>(tree, index)
        { }

    public:

        const_iterator() = default;
        
        const_iterator(const iterator& other) : iterator_base<const JudyL*>(other.tree_, other.current_index_)
        { }

        const_iterator& operator=(const const_iterator& other) = default;

        using iterator_base<const JudyL*>::operator++;
        using iterator_base<const JudyL*>::operator--;
    
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

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin()
    {
        first(0);
        return iterator(this, (PValue_ ? std::optional<Word_t>(Index_) : std::nullopt));
    }

    iterator end()
    {
        return iterator(this, std::nullopt);
    }

    const_iterator begin()  const
    {
        first(0);
        return const_iterator(this, (PValue_ ? std::optional<Word_t>(Index_) : std::nullopt));
    }

    const_iterator cbegin() const
    {
        first(0);
        return const_iterator(this, (PValue_ ? std::optional<Word_t>(Index_) : std::nullopt));
    }

    const_iterator end()    const
    {
        return const_iterator(this, std::nullopt);
    }
    
    const_iterator cend()    const
    {
        return const_iterator(this, std::nullopt);
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

    // STL алгоритмы
    iterator lower_bound(const Word_t& index)
    {
        first(index);
        return iterator(this, PValue_ ? std::optional<Word_t>(Index_) : std::nullopt);
    }

    iterator upper_bound(const Word_t& index)
    {
        next(index);
        return iterator(this, PValue_ ? std::optional<Word_t>(Index_) : std::nullopt);
    }

    const_iterator lower_bound(const Word_t& index) const
    {
        first(index);
        return const_iterator(this, PValue_ ? std::optional<Word_t>(Index_) : std::nullopt);
    }

    const_iterator upper_bound(const Word_t& index) const
    {
        next(index);
        return const_iterator(this, PValue_ ? std::optional<Word_t>(Index_) : std::nullopt);
    }

    std::pair<iterator, iterator> equal_range(const Word_t& index)
    {
        return std::make_pair(lower_bound(index), upper_bound(index));
    }

    std::pair<const_iterator, const_iterator> equal_range(const Word_t& index)  const
    {
        return std::make_pair(lower_bound(index), upper_bound(index));
    }

    iterator find(const Word_t& index)
    {
        get(index);
        return iterator(this, PValue_ ? std::optional<Word_t>(index) : std::nullopt);
    }

    const_iterator find(const Word_t& index)    const
    {
        get(index);
        return const_iterator(this, PValue_ ? std::optional<Word_t>(index) : std::nullopt);
    }

    iterator erase(iterator pos)
    {
        erase(const_iterator(pos));
    }

    iterator erase(const_iterator pos)
    {
        if(pos == cend())
            throw std::invalid_argument("JudyL::Cannot erase end() iterator");
        if(pos.tree_ != this)
            throw std::invalid_argument("JudyL::Cannot erase iterator from different array");
        
        Word_t key_to_del = pos->first;
        const_iterator tmp = pos;
        ++tmp;
        del(key_to_del);

        return iterator(this, std::optional<Word_t>(tmp->first));
    }


    iterator erase(iterator first, iterator last)
    {
        erase(const_iterator(first), const_iterator(last));
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        std::vector<Word_t> keys_to_del;
        const_iterator it = first;
        for(; it != last; ++it)
            keys_to_del.push_back(it->first);
        
        for(Word_t& key : keys_to_del)
            del(key);   

        return iterator(this, std::optional<Word_t>(last->first));
    }

    size_type erase(const Word_t& index)
    {
        del(index);
        return Rc_int_;
    }

    void swap(JudyL& other) noexcept
    {
        std::swap(arr_, other.arr_);
        std::swap(Rc_int_, other.Rc_int_);
        std::swap(Rc_word_, other.Rc_word_);
        std::swap(Index_, other.Index_);
        std::swap(PValue_, other.PValue_);
        std::swap(ptr_, other.ptr_);
        std::swap(debug_, other.debug_);
    }

    size_type count(const Word_t& index)  const
    {
        return (get(index) ? 1 : 0);
    }

    bool contains(const Word_t& index)    const
    {
        return get(index) != nullptr;
    }

    // Деструктор для очищения данных
    ~JudyL()
    {
        clear();// очищает весь массив, количество очищенных байт в Rc_word_
        if(debug_)
            std::clog << "Free " << Rc_word_ << " bytes" << std::endl;
    }
    
};
// JudyL

// Перегрузка оператора вывода класса JudyL::reference
inline std::ostream& operator<<(std::ostream& out, const JudyL::reference& obj)
{
    out << static_cast<Word_t>(obj);
    return out;
}

// Перегрузка оператора ввода класса JudyL::reference
inline std::istream& operator>>(std::istream& in, JudyL::reference obj)
{
    Word_t tmp; in >> tmp;
    obj = tmp;
    return in;
}

void swap(JudyL& j1, JudyL& j2) noexcept
{
    j1.swap(j2);
}


}
// namespace judy

#include <map>
#include <bitset>

#include <cassert>
#include <limits>
#include <algorithm>
#include <vector>
#include <sstream>

void stress_test_judyl_iterators() {
    std::cout << "=== JudyL Iterator Stress Test ===" << std::endl;
    
    // Тест 1: Пустой контейнер
    {
        std::cout << "\nTest 1: Empty container" << std::endl;
        judy::JudyL j;
        assert(j.begin() == j.end());
        assert(j.cbegin() == j.cend());
        assert(j.rbegin() == j.rend());
        assert(j.crbegin() == j.crend());
        std::cout << "✓ Empty container test passed" << std::endl;
    }
    
    // Тест 2: Один элемент
    {
        std::cout << "\nTest 2: Single element" << std::endl;
        judy::JudyL j;
        j[42] = 100;
        
        auto it = j.begin();
        assert(it != j.end());
        assert((*it).first == 42);
        assert((*it).second == 100);
        ++it;
        assert(it == j.end());
        
        // Reverse
        auto rit = j.rbegin();
        assert(rit != j.rend());
        assert((*rit).first == 42); 
        assert((*rit).second == 100);
        std::cout << "✓ Single element test passed" << std::endl;
    }
    
    // Тест 3: Множество элементов
    {
        std::cout << "\nTest 3: Multiple elements" << std::endl;
        judy::JudyL j;
        std::vector<std::pair<Word_t, Word_t>> test_values = {
            {1, 10}, {10, 20}, {100, 30}, {1000, 40}, {10000, 50}, 
            {std::numeric_limits<Word_t>::max() - 1, 60}
        };
        
        // Заполнение
        for(const auto& [key, val] : test_values) {
            j[key] = val;
        }
        
        // Прямая итерация
        std::vector<std::pair<Word_t, Word_t>> forward_result;
        for(auto it = j.begin(); it != j.end(); ++it) {
            forward_result.push_back({(*it).first, (*it).second});
        }
        assert(forward_result == test_values);
        
        // Range-based for
        size_t idx = 0;
        for(const auto& [key, val] : j) {
            assert(key == test_values[idx].first);
            assert(val == test_values[idx].second);
            idx++;
        }
        
        // Обратная итерация
        std::vector<std::pair<Word_t, Word_t>> reverse_result;
        for(auto rit = j.rbegin(); rit != j.rend(); ++rit) {
            reverse_result.push_back({(*rit).first, (*rit).second});
        }
        std::reverse(reverse_result.begin(), reverse_result.end());
        assert(reverse_result == test_values);
        
        std::cout << "✓ Multiple elements test passed" << std::endl;
    }
    
    // Тест 4: Операторы ++ и --
    {
        std::cout << "\nTest 4: Increment/Decrement operators" << std::endl;
        judy::JudyL j;
        j[10] = 111;
        j[20] = 222;
        j[30] = 333;
        
        auto it = j.begin();
        assert((*it).first == 10);
        assert((*it).second == 111);
        
        // Префиксный ++
        ++it;
        assert((*it).first == 20);
        assert((*it).second == 222);
        
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
        assert((*end_it).second == 333);
        
        std::cout << "✓ Increment/Decrement test passed" << std::endl;
    }
    
    // Тест 5: Константные итераторы
    {
        std::cout << "\nTest 5: Const iterators" << std::endl;
        judy::JudyL j;
        j[5] = 55;
        j[15] = 155;
        
        const judy::JudyL& cj = j;
        auto cit = cj.begin();
        assert(cit != cj.end());
        assert((*cit).first == 5);
        assert((*cit).second == 55);
        
        // Конверсия iterator -> const_iterator
        judy::JudyL::iterator it = j.begin();
        judy::JudyL::const_iterator cit2 = it;
        assert(cit2 == cj.begin());
        
        std::cout << "✓ Const iterators test passed" << std::endl;
    }
    
    // Тест 6: Операторы сравнения
    {
        std::cout << "\nTest 6: Comparison operators" << std::endl;
        judy::JudyL j;
        j[1] = 11;
        j[2] = 22;
        
        auto it1 = j.begin();
        auto it2 = j.begin();
        assert(it1 == it2);
        assert(!(it1 != it2));
        
        ++it2;
        assert(it1 != it2);
        assert(!(it1 == it2));
        
        std::cout << "✓ Comparison operators test passed" << std::endl;
    }
    
    // Тест 7: Arrow operator
    {
        std::cout << "\nTest 7: Arrow operator" << std::endl;
        judy::JudyL j;
        j[123] = 456;
        
        auto it = j.begin();
        assert(it->first == 123);
        assert(it->second == 456);
        
        std::cout << "✓ Arrow operator test passed" << std::endl;
    }
    
    // Тест 8: STL алгоритмы
    {
        std::cout << "\nTest 8: STL algorithms" << std::endl;
        judy::JudyL j;
        for(Word_t i = 0; i < 10; ++i) {
            j[i * i] = i * 10;  // ключи: 0, 1, 4, 9, 16, 25, 36, 49, 64, 81
        }                       // значения: 0, 10, 20, 30, 40, 50, 60, 70, 80, 90
        
        // std::distance
        auto dist = std::distance(j.begin(), j.end());
        assert(dist == 10);
        
        // std::find_if
        auto found = std::find_if(j.begin(), j.end(), 
            [](const auto& p) { return p.first == 25; });
        assert(found != j.end());
        assert((*found).first == 25);
        assert((*found).second == 50);
        
        // std::count_if
        auto count = std::count_if(j.begin(), j.end(),
            [](const auto& p) { return p.second > 40; });
        assert(count == 5);  // 50, 60, 70, 80, 90
        
        std::cout << "✓ STL algorithms test passed" << std::endl;
    }
    
    // Тест 9: Граничные случаи
    {
        std::cout << "\nTest 9: Edge cases" << std::endl;
        judy::JudyL j;
        
        // Максимальное значение ключа и значения
        j[static_cast<Word_t>(-1)] = static_cast<Word_t>(-1);
        j[0] = 0;
        j[1] = std::numeric_limits<Word_t>::max();
        
        auto it = j.begin();
        assert((*it).first == 0);
        assert((*it).second == 0);
        ++it;
        assert((*it).first == 1);
        assert((*it).second == std::numeric_limits<Word_t>::max());
        ++it;
        assert((*it).first == static_cast<Word_t>(-1));
        assert((*it).second == static_cast<Word_t>(-1));
        
        std::cout << "✓ Edge cases test passed" << std::endl;
    }
    
    // Тест 10: Модификация во время итерации
    {
        std::cout << "\nTest 10: Modification during iteration" << std::endl;
        judy::JudyL j;
        j[10] = 100;
        j[20] = 200;
        j[30] = 300;
        
        // Собираем ключи и модифицируем значения
        std::vector<Word_t> keys;
        for(const auto& [key, val] : j) {
            keys.push_back(key);
        }
        
        // Изменяем значения
        for(auto key : keys) {
            j[key] = j[key] * 2;
        }
        
        // Проверяем изменения
        assert(j[10] == 200);
        assert(j[20] == 400);
        assert(j[30] == 600);
        
        // Удаляем элементы
        for(auto key : keys) {
            j.del(key);
        }
        
        assert(j.begin() == j.end());  // Должен быть пустым
        
        std::cout << "✓ Modification test passed" << std::endl;
    }
    
    // Тест 11: Тест reference и operator[]
    {
        std::cout << "\nTest 11: Reference and operator[] test" << std::endl;
        judy::JudyL j;
        
        // Тест создания через []
        j[5] = 50;
        assert(j[5] == 50);
        
        // Тест арифметических операций
        j[5] += 10;
        assert(j[5] == 60);
        
        j[5]++;
        assert(j[5] == 61);
        
        ++j[5];
        assert(j[5] == 62);
        
        // Тест присваивания между элементами
        j[10] = j[5];
        assert(j[10] == 62);
        
        // Тест сложных выражений
        j[15] = j[5] + j[10];
        assert(j[15] == 124);
        
        std::cout << "✓ Reference test passed" << std::endl;
    }
    
    // Тест 12: Тест at()
    {
        std::cout << "\nTest 12: at() method test" << std::endl;
        judy::JudyL j;
        j[1] = 10;
        
        // Успешный доступ
        assert(j.at(1) == 10);
        j.at(1) = 20;
        assert(j.at(1) == 20);
        
        // Const версия
        const judy::JudyL& cj = j;
        assert(cj.at(1) == 20);
        
        // Исключения
        bool exception_thrown = false;
        try {
            j.at(999);
        } catch(const std::out_of_range&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
        
        exception_thrown = false;
        try {
            cj.at(999);
        } catch(const std::out_of_range&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
        
        std::cout << "✓ at() method test passed" << std::endl;
    }
    
    // Тест 13: Ввод/вывод
    {
        std::cout << "\nTest 13: Input/Output test" << std::endl;
        judy::JudyL j;
        
        // Симулируем ввод/вывод через stringstream
        std::stringstream ss;
        ss << "42";
        ss >> j[1];
        assert(j[1] == 42);
        
        std::stringstream out;
        out << j[1];
        assert(out.str() == "42");
        
        std::cout << "✓ Input/Output test passed" << std::endl;
    }
    
    std::cout << "\n=== All JudyL iterator tests passed! ===" << std::endl;
}



int main(int argc, char** argv) {
    
    stress_test_judyl_iterators();
    
    
    return 0;
}


/* Любые итераторы
// Поиск
std::find(begin, end, value)
std::find_if(begin, end, predicate)
std::find_if_not(begin, end, predicate)
std::adjacent_find(begin, end)
std::search(begin, end, pattern_begin, pattern_end)
std::search_n(begin, end, count, value)

// Подсчёт
std::count(begin, end, value)
std::count_if(begin, end, predicate)

// Сравнение
std::equal(begin1, end1, begin2)
std::mismatch(begin1, end1, begin2)
std::lexicographical_compare(begin1, end1, begin2, end2)

// Проверки
std::all_of(begin, end, predicate)
std::any_of(begin, end, predicate)
std::none_of(begin, end, predicate)

// Обход
std::for_each(begin, end, function)

// Другие
std::distance(begin, end)  // O(n) для bidirectional
std::advance(it, n)         // O(n) для bidirectional
std::next(it, n)
std::prev(it, n)

НЕ КОНСТАНТНЫЕ ИТЕРАТОРЫ
// Копирование (destination должен быть не-const)
std::copy(begin, end, dest_begin)
std::copy_if(begin, end, dest_begin, predicate)
std::copy_backward(begin, end, dest_end)  // требует bidirectional!

// Перемещение
std::move(begin, end, dest_begin)
std::move_backward(begin, end, dest_end)  // требует bidirectional!

// Заполнение
std::fill(begin, end, value)
std::fill_n(begin, count, value)
std::generate(begin, end, generator)
std::generate_n(begin, count, generator)

// Замена
std::replace(begin, end, old_value, new_value)
std::replace_if(begin, end, predicate, new_value)
std::replace_copy(begin, end, dest_begin, old_value, new_value)
std::replace_copy_if(begin, end, dest_begin, predicate, new_value)

// Трансформация
std::transform(begin, end, dest_begin, unary_op)
std::transform(begin1, end1, begin2, dest_begin, binary_op)

// Удаление (для контейнеров с erase)
std::remove(begin, end, value)
std::remove_if(begin, end, predicate)
std::remove_copy(begin, end, dest_begin, value)
std::remove_copy_if(begin, end, dest_begin, predicate)

// Уникальность
std::unique(begin, end)
std::unique_copy(begin, end, dest_begin)

// Реверс
std::reverse(begin, end)  // требует bidirectional!
std::reverse_copy(begin, end, dest_begin)

// Поворот
std::rotate(begin, middle, end)  // требует bidirectional!
std::rotate_copy(begin, middle, end, dest_begin)

*/