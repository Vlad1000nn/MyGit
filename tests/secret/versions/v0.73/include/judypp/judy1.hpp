#include "Judy.h"

#include <iterator> // for std::bidirectional_iterator_tag, std::reverse_iterator
#include <utility>  // for std::pair
#include <cstddef>  // for std::ptr_diff_t, std::size_t
#include <iostream> // for std::ostream, std::istream
#include <optional> // for std::optional

// Для конструкторов
#include <bitset>   // for std::bitset

#include <queue>

// проблема с заголовками
// возможно ещё std::bad_alloc

namespace judy {

    using Word_t = unsigned long;
    using PWord_t = Word_t*;
    using PPWord_t = PWord_t*;
    using Pvoid_t = void*;
    using PPvoid_t = Pvoid_t*;

/*************************************JUDY 1*************************************
// Обёртка для класса Judy1 (для удобства использования) (С++17)

ОК:
    
    for(auto it : j) { }                        
    for(const auto& it : j) { }             
    for(auto [key, val] : j) { }            
    for(const auto& [key, val] : j) { }     

НЕ ОК:
    
    for(auto& it : j) { }                   
    for(auto& [key, val] : j) { }           

********************************************************************************/


class Judy1 {
private:

//*************************************PRIVATE MEMBERS*************************************//
    using size_type = std::size_t;
    
    // при каждой вставке меняются приватные члены, мешает параллельности

    mutable int rc_int_;     // код возврата функций
    mutable Word_t rc_word_; // слово возврата функций
    mutable Word_t index_;   // индекс для поиска

    Pvoid_t arr_;    // Указатель на корень массива

    // Большого смысла не имеет, просто вывод в деструкторе количества освобождённой памяти
    inline static bool debug_ = false;
    
public:

//*************************************CONSTRUCTORS*************************************//

    // Базовый конструктор
    Judy1() 
        : rc_int_(0)
        , rc_word_(0)
        , index_(0)
        { 
            arr_ = (Pvoid_t) NULL;
        }
        
    // Конструктор для контейнеров с value_type - интегральный тип. элементы -> номера ключей
    // std::array, std::vector, std::deque, std::list, std::forward_list, std::set, std::multiset, std::unordered_set,
    // std::unordered_multiset, std::string, std::wstring  
    template<typename Container, std::enable_if_t<std::is_integral_v<typename Container::value_type>, int> = 0>
    explicit Judy1(const Container& container) 
        : Judy1()
    {
        for(const auto& value : container)  
            set(value);
    }

    // ещё можно перегружать для std::priority_queue, std::queue, std::stack
    
    // Конструктор на основе списка инициализации(устанавливает 1 в указанные индексы)
    Judy1(std::initializer_list<Word_t> init_list) 
        : Judy1()
    {
        for(const auto& it : init_list)
            set(it);
    }

    // Конструктор на основе std::bitset
    template<std::size_t Nb>
    explicit Judy1(const std::bitset<Nb>& bits) 
        : Judy1()
    {
        std::size_t i;
        for(i = 0; i < Nb; ++i)
            if(bits[i])
                set(i);
    }
    
    // deep copy constuctor
    Judy1(const Judy1& other)   
        : Judy1()
    {
        const_iterator it = other.cbegin();
        for(; it != other.cend(); ++it)
            set(it->first);
    }
    
    // Move constructor
    Judy1(Judy1&& other) noexcept 
        : Judy1()  
    {
        arr_ = other.arr_;
        rc_int_ = other.rc_int_;
        rc_word_ = other.rc_word_;
        index_ = other.index_;
        
        other.arr_ = nullptr;
        other.rc_int_ = other.rc_word_ = other.index_ = 0;
    }
    
    // Оператор присваивания=
    Judy1& operator=(const Judy1& other) 
    {
        if(this != &other) {
            clear();
            const_iterator it = other.begin();
            for(; it != other.end(); ++it)
                set(it->first);
        }
        
        return *this;
    }
    
    // move-присваивание
    Judy1& operator=(Judy1&& other) noexcept
    {
        if(this != &other) {
            arr_ = other.arr_;
            rc_int_ = other.rc_int_;
            rc_word_ = other.rc_word_;
            index_ = other.index_;
            
            other.arr_ = nullptr;
            other.rc_int_ = other.rc_word_ = other.index_ = 0;
        }
        
        return *this;
    }

//*************************************CONTAINER FUNCS*************************************//
    
    // Возвращает количество занятых индексов
    size_type size()  const noexcept
    {
        return count(0, -1);
    }

    // очищает весь массив, количество очищенных байт в Rc_word_
    void clear()    noexcept
    {
        J1FA(rc_word_, arr_);
    }

    // Проверка на пустоту
    bool empty()    const   noexcept
    {
        return size() == 0;
    }

    // Обмен с другим Judy1
    void swap(Judy1& other) noexcept
    {
        std::swap(arr_, other.arr_);
        std::swap(rc_int_, other.rc_int_);
        std::swap(rc_word_, other.rc_word_);
        std::swap(index_, other.index_);
    }

    size_type count(const Word_t& index) const noexcept
    {
        return test(index);
    }
    
    // Проверяет содержится ли индекс в Judy1
    bool contains(const Word_t& index)  const noexcept
    {
        return test(index);
    }
    
    // Включает/выключает debug_
    static void set_debug_mode(const bool value)
    {
        debug_ = value;
    }

/*************************************JUDY MACRO FUNCS*************************************
    Я решил их оставить в публичном доступе на усмотрение пользователя(вдруг он хочет 
    собственноручно что-нибудь сделать, да и обёртка класса не использует некоторые ПОЛЕЗНЫЕ
    методы)
******************************************************************************************/

    // Включает бит по индексу index (возвращает 0 если бит уже был включён)
    int set(const Word_t& index)
    {
        J1S(rc_int_, arr_, index);
        return rc_int_;
    }
    
    // Выключает бит по индексу index (возвращает 0, если бит уже был выключен)
    int unset(const Word_t& index) 
    {
        J1U(rc_int_, arr_, index);
        return rc_int_;
    }
    
    // Возвращает значение бита по индексу index(если такой не существует то 0)
    int test(const Word_t& index)    const  noexcept
    {
        J1T(rc_int_, arr_, index);
        return rc_int_;
    }
    
    // Возвращает количество битов в диапазоне [Index_1, Index_2]
    // [0, -1] - возвращает количество вообще всех битов установленных (-1 в unsigned = 111..111)
    // ***Протестировать невалидные значения
    Word_t count(const Word_t& index1, const Word_t& index2) const noexcept
    {
        J1C(rc_word_, arr_, index1, index2);
        return rc_word_;
    }
    
    // Возвращает n-й установленный бит (либо -1 если не найден такой)
    // непонятно ещё если n = 0, чтото про fully populated array
    std::optional<Word_t> ncount(const Word_t& n)  const    noexcept
    {
        J1BC(rc_int_, arr_, n, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    // Возвращает количество байт которые в данный момент занимает массив
    // (очень быстрый, особенно после set/unset)
    Word_t memused()    const   noexcept
    {
        J1MU(rc_word_, arr_);
        return rc_word_;
    }
    
    // Возвращает первый попавшийся бит начиная с index(начать с 0 чтобы найти в массиве в целом первый бит)
    std::optional<Word_t> first(const Word_t& index = 0)   const    noexcept
    {
        index_ = index;
        J1F(rc_int_, arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    // Возвращает первый попавшийся бит начиная с index+1
    std::optional<Word_t> next(const Word_t& index)    const    noexcept
    {
        index_ = index;
        J1N(rc_int_, arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }
    
    // ищет начиная с index первый бит в обратном порядке (т.е. справа налево)
    // -1 для поиска последнего в целом
    std::optional<Word_t> last(const Word_t& index)    const    noexcept
    {
        index_ = index;
        J1L(rc_int_, arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    // ищет начиная с index-1 первый бит
    std::optional<Word_t> prev(const Word_t& index)    const    noexcept
    {
        index_ = index;
        J1P(rc_int_, arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    // начиная с index находит первый 0
    std::optional<Word_t> first_empty(const Word_t& index) const    noexcept
    {
        index_ = index;
        J1FE(rc_int_, arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    // начиная с index+1 находит первый 0
    std::optional<Word_t> next_empty(const Word_t& index)  const    noexcept
    {
        index_ = index;
        J1NE(rc_int_, arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    // начиная с index находит первый 0 в обратном порядке (справа налево)
    std::optional<Word_t> last_empty(const Word_t& index)  const    noexcept
    {
        index_ = index;
        J1LE(rc_int_, arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }
    
    // начиная с index-1 находит первый 0 в обратном порядке (справа налево)
    std::optional<Word_t> prev_empty(const Word_t& index)  const    noexcept
    {
        index_ = index;
        J1PE(rc_int_, arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

/*************************************REFERENCE*************************************
    Здесь используется класс reference как имитация доступа к отдельным битам
    (для функционирования оператора [])
***********************************************************************************/
    // Класс-имитация доступа к отдельным битам
    class reference {
    private:

        friend class Judy1;
        
        Judy1& tree_;    // Ссылка на родительский Judy1
        Word_t index_;   // Индекс бита
        
        reference();
        
    public:
        
        explicit reference(Judy1& tree, const Word_t index) 
            : tree_(tree)
            , index_(index) 
        { }
        
        reference(const reference&) = default;
        
        // Перегрузка оператора= для int
        reference& operator=(int value)
        {
            value ? tree_.set(index_) : tree_.unset(index_);
            return *this;
        }
        
        // Оператор присваивания (для tree[Index_] = tree_[other])
        reference& operator=(const reference& other) 
        {
            tree_[index_] = static_cast<bool>(other);
            return *this;
        }
        
        // Оператор для приведения в тип int
        operator int()  const   noexcept
        {
            return tree_.test(index_);
        }

        reference& operator|=(int value)
        {
            if(value)
                tree_.set(index_);
            return *this;
        }

        reference& operator&=(int value)
        {
            if(!value)
                tree_.unset(index_);
            return *this;
        }

        reference& operator^=(int value)
        {
            if(value) 
                tree_.test(index_) ? tree_.unset(index_) : tree_.set(index_);

            return *this;
        }
        
        // Оператор инвертирования
        bool operator~()    const   noexcept
        {
            return !tree_.test(index_);
        }
        
        ~reference() = default;
        
    };
    // reference
    
    // Оператор [] 
    reference operator[](const Word_t& index) 
    {
        return reference(*this, index);
    }

//*************************************ITERATORS*************************************//

private:

    // Класс-родитель для Judy1 итераторов
    template<typename Treeptr>
    class iterator_base {
    public:
    
        using iterator_category = std::bidirectional_iterator_tag;  // Категория итераторов(на основе нашего контейнера)
        using value_type =  std::pair<const Word_t, int>;
        using difference_type = std::ptrdiff_t;    // необходимо определить, не используется, будет std::distance O(n)
        using pointer = value_type*;
        using reference = value_type; // с ссылкой проблемы, но наш контейнер и не предоставляет доступ по ссылке к элементам, поэтому ОК
        
    protected:
        
        Treeptr tree_;
        std::optional<Word_t> current_index_;
        
        mutable std::optional<value_type> cached_value_;
    
        iterator_base(Treeptr tree, const std::optional<Word_t> index)
            : tree_(tree)
            , current_index_(index)
            , cached_value_()
        { }
        
    public:
    
        iterator_base()
            : tree_(nullptr)
            , current_index_(std::nullopt)
            , cached_value_()
        { }
        
        iterator_base(const iterator_base& other)
            : iterator_base()
        {
            tree_ = other.tree_;
            current_index_ = other.current_index_;
        }

        iterator_base& operator=(const iterator_base& other)
        {
            if (this != &other) {
                tree_ = other.tree_;
                current_index_ = other.current_index_;
            }
            return *this;
        }
        
        iterator_base& operator++()
        {
            if(tree_ && current_index_.has_value()) 
                current_index_ = tree_->next(current_index_.value());
            // else UB
            return *this;
        }

        iterator_base& operator--()
        {
            if(tree_) {
                if(current_index_.has_value())
                    current_index_ = tree_->prev(current_index_.value());
                else
                    current_index_ = tree_->last(static_cast<Word_t>(-1));
            }
            // else UB
            
            return *this;
        }
        
        reference operator*()  const
        {
            if(tree_ && current_index_.has_value())
                return value_type(current_index_.value(), tree_->test(current_index_.value()));
    
            throw std::runtime_error("Dereference invalid iterator");
        }

        pointer operator->() const 
        {
            cached_value_.emplace(operator*());
            return &(*cached_value_);
        }

        bool operator==(const iterator_base& other)  const  noexcept
        {
            return tree_ == other.tree_ && current_index_ == other.current_index_;
        }
        
        bool operator!=(const iterator_base& other)  const  noexcept
        {
            return !(*this == other);
        }

        ~iterator_base() = default;
        
    };
    // iterator_base
    
public:
    
    // Классический итератор по Judy1 дереву
    class iterator : public iterator_base<Judy1*> {
    private:
    
        friend class Judy1;
        friend class const_iterator; // для возможности переводить обычный в const
        
        explicit iterator(Judy1* tree, const std::optional<Word_t> index) 
            : iterator_base<Judy1*>(tree, index)
        { }
    
    public:
    
        iterator() = default;
    
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;
        
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

    
    // Константный итератор
    class const_iterator : public iterator_base<const Judy1*> {
    private:
    
        friend class Judy1;
        
        explicit const_iterator(const Judy1* tree, const std::optional<Word_t> Index_) 
            : iterator_base<const Judy1*>(tree, Index_)
        { }
        
    public:
    
        const_iterator() = default;
        
        const_iterator(const const_iterator&)= default;
        const_iterator& operator=(const const_iterator&) = default;
        
        const_iterator(const iterator& other) 
            : iterator_base<const Judy1*>(other.tree_, other.current_index_)
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
    
    // Для reverse версий итераторов просто воспользуемся std::reverse_iterator
    // Нам это позволяет сделать полная реализация итераторов
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
    // type_traits на проверку является ли тип указателем Judy1
    template<typename T>
    static constexpr bool is_Judy1_iterator = 
    std::is_same_v<T, Judy1::iterator>          ||
    std::is_same_v<T, Judy1::const_iterator>    || 
    std::is_same_v<T, Judy1::reverse_iterator>  ||
    std::is_same_v<T, Judy1::const_reverse_iterator>;
    
    // Конструктор на основе итераторов контейнеров
    template<typename It, std::enable_if_t<!is_Judy1_iterator<It>, int> = 0>
    Judy1(It first, It last) : Judy1()
    {
        for(; first != last; ++first)
            set(*first);
    }
     
    // Конструктор на основе итераторов Judy1
    template<typename It, std::enable_if_t<is_Judy1_iterator<It>, int> = 0>
    Judy1(It first, It last) : Judy1()
    {
        for(; first != last; ++first)
            set((*first).first);
    }
        
    // Все итераторы типа begin(), end()
    iterator begin()
    {
        return iterator(this, this->first(0));
    }

    const_iterator begin()  const
    {
        return const_iterator(this, this->first(0));
    }

    iterator end()
    {
        return iterator(this, std::nullopt);
    }
    
    const_iterator cbegin() const
    {
        return const_iterator(this, this->first(0));
    }
    
    const_iterator end()    const
    {
        return const_iterator(this, std::nullopt);
    }
    
    const_iterator cend()   const
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
    

/*************************************STL-LIKE FUNCS*************************************
    Методы с названиями от STL-функций как у std::map 
    Добавлено только для совместимости, чтобы контейнеры можно было заменить друг на друга
    "Опимальность" методов не гарантируется
****************************************************************************************/

    iterator lower_bound(const Word_t& index)
    {
        return iterator(this, first(index));
    }

    const_iterator lower_bound(const Word_t& index) const
    {
        return const_iterator(this, first(index));
    }

    iterator upper_bound(const Word_t& index)
    {
        return iterator(this,  next(index));
    }

    const_iterator upper_bound(const Word_t& index) const
    {
        return const_iterator(this, next(index));
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
        return (test(index) ? iterator(this, index) : end());
    }

    const_iterator find(const Word_t& index)    const
    {
        return (test(index) ? const_iterator(this, index) : cend());
    }

    // для совместимости, смысловой нагрузки особо не имеет(обычное выключение битов)
    iterator erase(iterator pos)
    {
        if(pos == end())
            throw std::invalid_argument("JudyL::Cannot erase end() iterator");
        if(pos.tree_ != this)
            throw std::invalid_argument("JudyL::Cannot erase iterator from different array");

        iterator next_it = pos;
        ++next_it;
        unset(pos->first);

        return next_it;
    }        

    iterator erase(const_iterator pos)
    {
        if(pos == cend())
            throw std::invalid_argument("JudyL::Cannot erase cend() const_iterator");
        if(pos.tree_ != this)
            throw std::invalid_argument("JudyL::Cannot erase const_iterator from different array");

        const_iterator next_it = pos;
        ++next_it;
        unset(pos->first);

        return (next_it == cend() ? end() : iterator(this, next_it->first));
    }

    iterator erase(iterator first, iterator last)
    {
        while(first != last)
            first = erase(first);
        
        return first;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        while((first != last))
            first = erase(first);

        return iterator(this, first.current_index_);
    }

    size_type erase(const Word_t& index)
    {
        unset(index);
        return rc_int_;
}

//*************************************CLASS FUNCS*************************************//

    // Оператор сравнения
    bool operator==(const Judy1& other) const
    {
        if(size() != other.size())
            return false;

        const_iterator it = cbegin();
        for(; it != cend(); ++it)
            if(!other.test(it->first))
                return false;

        return true;
    }

    // Оператор неравенства
    bool operator!=(const Judy1& other) const
    {
        return !(*this == other);
    }

    // операции над Judy1 деревьями, как над множествами
    Judy1 operator|(const Judy1& other) const
    {
        Judy1 res(*this);
        const_iterator it = other.cbegin();
        for(; it != other.cend(); ++it)
            res.set(it->first);

        return res;
    }

    // Разность множеств
    Judy1 operator-(const Judy1& other) const {
        Judy1 result(*this);
        const_iterator it = other.begin();
        for (; it != other.end(); ++it) 
            result.unset(it->first);
        
        return result;
    }

    // Симметрическая разность
    Judy1 operator^(const Judy1& other) const {
        Judy1 result(*this);
        const_iterator it = other.cbegin();
        for (; it != other.cend(); ++it) 
            test(it->first) ? result.unset(it->first) : result.set(it->first);
            
        return result;
    }

    Judy1 operator&(const Judy1& other) const
    {
        Judy1 res;
        const_iterator it = cbegin();
        for(; it != cend(); ++it)
            if(other.test(it->first))
                res.set(it->first);

        return res;
    }

    Judy1& operator|=(const Judy1& other)
    {
        const_iterator it = other.begin();
        for(; it != other.cend(); ++it)
            set(it->first);

        return *this;
    }

    Judy1& operator&=(const Judy1& other)
    {
        const_iterator it = cbegin();
        for(; it != cend(); ++it)
            if(!other.test(it->first))
                unset(it->first);

        return *this;
    }

    Judy1& operator-=(const Judy1& other)
    {
        const_iterator it = other.begin();
        for(; it != other.end(); ++it)
            unset(it->first);
        
        return *this;
    }

    Judy1& operator^=(const Judy1& other)
    {
        const_iterator it = other.cbegin();
        for(; it != other.cend(); ++it) {
            if(test(it->first))
                unset(it->first);
            else
                set(it->first);
        }
        
        return *this;
    }
    
    // Деструктор для очищения данных
    ~Judy1() noexcept
    {
        clear();
        if(debug_)
            std::clog << "Free " << rc_word_ << " bytes" << std::endl;
    }
    
};
// Judy1

void swap(Judy1& j1, Judy1& j2) noexcept
{
    j1.swap(j2);
}

std::ostream& operator<<(std::ostream& out, const Judy1::reference& obj) 
{
    return out << static_cast<int>(obj);
}

std::istream& operator>>(std::istream& in, Judy1::reference obj)
{
    int tmp; in >> tmp;
    obj = tmp;
    return in;
}


}
// namespace judy
