#include "Judy.h"
#include <utility>          // for std::pair
#include <stdexcept>        // for std::out_of_range
#include <cstring>          // for std::memcpy
#include <initializer_list> // for std::initializer_list
#include <iostream>         // for std::cout
#include <optional>         // for std::optional
#include <string>           // for std::string
#include <memory>   // for std::unique_ptr

namespace judy {

/*************************************JUDY L************************************* 
    Обёртка для класса JudyL (для удобства использования)

    можно добавить через type_traits StringType
    так же можно попробовать переписать под std::string_view

    ОК:
    
    for(auto it : j) { }                        
    for(const auto& it : j) { }             
    for(auto [key, val] : j) { }            
    for(const auto& [key, val] : j) { }     

НЕ ОК:
    
    for(auto& it : j) { }                   
    for(auto& [key, val] : j) { }       
    
    
********************************************************************************/

class JudySL {
private:

/***********************PRIVATE MEMBERS*******************************/

    using size_type = std::size_t;

    using Word_t = unsigned long;
    using PWord_t = Word_t*;
    using PPWord_t = PWord_t*;
    using Pvoid_t = void*;
    using PPvoid_t = Pvoid_t*;
    
    inline static constexpr size_type MAXLINELEN = 1'000'000; // Максимальный размер ключа
    // вообще MAXLINELEN нужно задавать либо через ограничения memset, либо через ограничения std::string
    
    // mutable члены как внутреннее состояние, нужны для работы judy функций и макросов
    mutable int rc_int_;      // код возврата функций
    mutable Word_t rc_word_;  // возврат слова
    mutable uint8_t* index_;  // буфер для поиска
    
    mutable PWord_t pvalue_;   // указатель на значение
    mutable Pvoid_t ptr_;      // указатель для совместимости с Cшными преобразованиями void*

    size_type population_;     // количество занятых индексов дерева
    mutable size_type current_max_len_;   // текущая максимальная длина строки(оптимизация для поиска last) 

    Pvoid_t arr_;    // Указатель на корень массива

    // Большого смысла пока не имеет, просто вывод в деструкторе количества освобождённой памяти
    inline static bool debug_ = false;

    size_type last_str_size_;   // текущий размер максимальной строки
    char* last_str_;            // максимальная строка
    
/***********************PRIVATE FUNCTIONS*******************************/

    // Вспомогательный метод для копирования std::string строк в наш uint8_t* index_
    void copy_str_to_uint(const std::string& index) const
    {
        const std::size_t len = index.size();
        
        // либо делаем так
        if (len > MAXLINELEN) 
            throw std::invalid_argument("JudySL::index is too large");
        // Либо потом можно поменять логику на: первые MAXLENLINE символов прочитали, а остальное игнорим
        
        // возможно стоит сделать в стиле c++ и выполнять std::copy
        std::memcpy(index_, index.data(), len);
        index_[len] = '\0';
    }

    // Вспомогательный метод для копирования char* строк
    void prepare_str(const char* index) const
    {
        const std::size_t len = strlen(index) + 1;
        current_max_len_ = std::max(current_max_len_, len + static_cast<size_type>(1)); 
        if (len > MAXLINELEN)
            throw std::invalid_argument("JudySL::index is too large");
        std::memcpy(index_, index, len);
    }

    // Вспомогательный метод для копирования std::string строк
    void prepare_str(const std::string& index)  const
    {
        copy_str_to_uint(index);
    }

    // реализация метода at()
    template<typename StringType>
    Word_t& at_impl_(StringType&& index)    const
    {
        get(std::forward<StringType>(index));
        if(pvalue_ == nullptr)
            throw std::out_of_range("JudySL::at");
        return *pvalue_;
    }

    // Базовая инициализация максимальной строки 
    void init_last_str_()
    {
        last_str_size_ = 1;
        last_str_ = new char[2];
        last_str_[0] = '\xff'; last_str_[last_str_size_] = '\0';
    }

    // Увеличение размера максиамльной строки
    void last_str_realloc_(const std::size_t new_len)
    {
        if(new_len <= last_str_size_)
            return;
        
        std::size_t new_size = last_str_size_;
        while(new_size <= new_len)
            new_size *= 2;

        char* new_str = new char[new_size + 1];
        std::memcpy(new_str, last_str_, last_str_size_);
        std::memset(new_str + last_str_size_, 0xff, new_size - last_str_size_);
        new_str[new_size] = '\0';
        
        delete[] last_str_;
        last_str_size_ = new_size;
        last_str_ = new_str;
    }

    // метод получения длины const char* строки
    size_type get_len_(const char* str)
    {
        return strlen(str) + 1;
    }

    // метод получения длины std::string строки
    size_type get_len_(const std::string& str)
    {
        return str.size() + 1;
    }

public:

//*************************************CONSTURCTORS*************************************//
    
    // Базовый конструктор
    JudySL() 
        : rc_int_(0)
        , rc_word_(0)
        , pvalue_(nullptr)
        , ptr_(nullptr)
        , population_(0)
        , current_max_len_(1)
        
    { 
        arr_ = (Pvoid_t) NULL;
        index_ = new uint8_t[MAXLINELEN + 1]; // выделим в куче
        init_last_str_();
    }   
    
    // Конструктор на основе initializer_list
    JudySL(std::initializer_list<std::pair<const std::string, Word_t>> init_list) 
        : JudySL()
    {
        for(const auto& it : init_list) {
            insert(it.first);
            *pvalue_ = it.second;
        }
    }

    // Конструктор на итераторах
    template<typename It>
    JudySL(It first, It last)
        : JudySL()
    {
        for(;first != last; ++first)
        {  
            if(get(first->first)) continue;
            insert(first->first);
            *pvalue_ = (*first).second;
        }
    }

    // deep-copy constructor
    JudySL(const JudySL& other)
        : JudySL()
    {
        const_iterator it = other.cbegin();
        for(; it != other.cend(); ++it)
            *insert(it->first) = it->second;    
    }

    // move-конструктор
    JudySL(JudySL&& other) noexcept
        : rc_int_(other.rc_int_)
        , rc_word_(other.rc_word_)
        , pvalue_(other.pvalue_)
        , ptr_(other.ptr_)
        , arr_(other.arr_)
        , population_(other.population_)
        , current_max_len_(other.current_max_len_)
        , last_str_(other.last_str_)
        , last_str_size_(other.last_str_size_)
        , index_(other.index_)
    {
        other.arr_ = nullptr;
        other.index_ = nullptr;
        other.ptr_ = nullptr;
        other.pvalue_ = nullptr;

        // можно  кстати не делать, итак уже невалидный
        other.rc_int_ = other.rc_word_ = other.population_ = other.last_str_size_ = 0;
    }

    // оператор присваивания
    JudySL& operator=(const JudySL& other)
    {
        if(this != &other) {
            JudySL tmp(other);
            swap(tmp);
        }
        return *this;
    }

    // move-присваивание
    JudySL& operator=(JudySL&& other) noexcept
    {
        if(this != &other) {

            JSLFA(rc_word_, arr_);
            delete[] index_;
            delete[] last_str_;

            arr_ = other.arr_;
            rc_int_ = other.rc_int_;
            rc_word_ = other.rc_word_;
            pvalue_ = other.pvalue_;
            ptr_ = other.ptr_;
            population_ = other.population_;
            current_max_len_ = other.current_max_len_;
            last_str_size_ = other.last_str_size_;
            index_ = other.index_;
            last_str_ = other.last_str_;
        

            other.arr_ = nullptr;
            other.index_ = nullptr;
            other.last_str_ = nullptr;
            other.pvalue_ = nullptr;
            other.ptr_ = nullptr;

            other.rc_int_ = other.rc_word_ = other.population_ = other.last_str_size_ = 0;
        }
        return *this;
    }

/*************************************JUDY MACROS FUNCS*************************************
    Я решил их оставить в публичном доступе на усмотрение пользователя(вдруг он хочет 
    собственноручно что-нибудь сделать, да и обёртка класса не использует некоторые ПОЛЕЗНЫЕ
    методы)
********************************************************************************************/
    
    // Вставляет index, возвращает указатель на значение
    template<typename StringType>
    PWord_t insert(StringType&& index)
    {
        prepare_str(std::forward<StringType>(index));
        last_str_realloc_(get_len_(std::forward<StringType>(index)));

        // чисто для population_, можно убрать в целом
        JSLG(ptr_, arr_, index_);
        if(!ptr_) {
            ++population_; 
            JSLI(ptr_, arr_, index_);
        }
        pvalue_ = static_cast<PWord_t>(ptr_);
        return pvalue_;
    }

    // Удаляет индекс, возвращает 1 если успешно, 0 если ничего не было
    template<typename StringType>
    int del(StringType&& index)
    {
        prepare_str(index);
        JSLD(rc_int_, arr_, index_);
        population_ -= rc_int_; 
        return rc_int_;
    }

    // Возвращает указатель на arr_[index], NULL если такого нет
    template<typename StringType>
    PWord_t get(StringType&& index) const
    {
        prepare_str(index);
        JSLG(ptr_, arr_, index_);
        pvalue_ = static_cast<PWord_t>(ptr_);
        return pvalue_;
    }
    
    // Пустая строка(то есть '\0') ищет самый первый
    template<typename StringType>
    std::pair<std::string, PWord_t> first(StringType&& index)   const
    {
        prepare_str(index);
        JSLF(ptr_, arr_, index_);
        pvalue_ = static_cast<PWord_t>(ptr_);

        return std::make_pair(std::string(reinterpret_cast<const char*>(index_)), pvalue_);
    }
    
    // index + 1
    template<typename StringType>
    std::pair<std::string, PWord_t> next(StringType&& index)   const
    {
        prepare_str(index);
        JSLN(ptr_, arr_, index_);
        pvalue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(std::string(reinterpret_cast<const char*>(index_)), pvalue_);
    }
    
    // ищем вхождение начиная с index включительно
    template<typename StringType>
    std::pair<std::string, PWord_t> last(StringType&& index)   const
    {
        prepare_str(index);
        JSLL(ptr_, arr_, index_);
        pvalue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(std::string(reinterpret_cast<const char*>(index_)), pvalue_);
    }

    // index-1
    template<typename StringType>
    std::pair<std::string, PWord_t> prev(StringType&& index)   const
    {
        prepare_str(index);
        JSLP(ptr_, arr_, index_);
        pvalue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(std::string(reinterpret_cast<const char*>(index_)), pvalue_);
    }


//*************************************CONTAINER FUNCS*************************************//

    // Количество занятых индексов
    size_type size() const noexcept
    {
        return population_;
    }

    // Проверка на пустоту массива
    bool empty() const noexcept
    {
        return size() == 0;
    }

    // Сбрасываем в начальное состояние
    void clear()
    {
        JSLFA(rc_word_, arr_);
        population_ = 0;
        delete[] last_str_;
        init_last_str_(); 
    }  
    
    // обмен с other
    void swap(JudySL& other) noexcept
    {
        std::swap(arr_, other.arr_);
        std::swap(rc_int_, other.rc_int_);
        std::swap(rc_word_, other.rc_word_);
        std::swap(index_, other.index_);
        std::swap(pvalue_, other.pvalue_);
        std::swap(ptr_, other.ptr_);
        std::swap(population_, other.population_);
        std::swap(current_max_len_, other.current_max_len_);
        std::swap(last_str_size_, other.last_str_size_);
        std::swap(last_str_, other.last_str_);
    }

    // подсчёт количества текущего индекса(либо 0 либо 1)
    template<typename StringType>
    size_type count(StringType&& index) const noexcept
    {
        return (get(std::forward<StringType>(index)) ? 1 : 0);
    }

    // проверка содержится ли индекс
    template<typename StringType>
    bool contains(StringType&& index) const noexcept
    {
        return get(std::forward<StringType>(index)) != nullptr;
    }

    // Включает/выключает debug_
    static void set_debug_mode(const bool value)
    {
        debug_ = value;
    }


/*************************************REFERENCE*************************************
    Здесь используем класс reference, потому что JudySL перестраивается при вставках
    или удалениях, соответственно строки типа tree[1] = tree[2] + tree[3] имеют
    неопределённое поведение при отсутствии индексов 1,2,3 в tree.
    Почему? Оператор [] при отсутствии индекса автоматически вставляет его в дерево. 
    А после каждой новой вставки, старый указатель из метода get теряет свою 
    актуальность и потребуется заново выполнять get
***********************************************************************************/

    class reference {
    private:
    
        friend class JudySL;
        
        JudySL& tree_;
        std::string index_;
        
        reference();

    public:
    
        template<typename StringType>
        reference(JudySL& tree, StringType&& index)
            : tree_(tree)
            , index_(std::forward<StringType>(index))
        { 
            if(!tree_.get(index_))
                tree_.insert(index_);
        }
            
        reference(const reference&) = default;
        
        reference& operator=(Word_t value)
        {
            PWord_t current = tree_.get(index_);
            *current = value;
            return *this;
        }
        
        reference& operator=(const reference& other)
        {
            tree_[index_] = static_cast<Word_t>(other);
            return *this;
        }
        
        reference& operator+=(Word_t value) 
        {
            PWord_t current = tree_.get(index_);
            *current += value;
            return *this;
        }
        
        reference& operator-=(Word_t value) 
        {
            PWord_t current = tree_.get(index_);
            *current -= value;
            return *this;
        }
        
        reference& operator*=(Word_t value) 
        {
            PWord_t current = tree_.get(index_);
            *current *= value;
            return *this;
        }

        reference& operator/=(Word_t value) 
        {
            PWord_t current = tree_.get(index_);
            *current /= value;
            return *this;
        }
        
        reference& operator&=(Word_t value) 
        {
            PWord_t current = tree_.get(index_);
            *current &= value;
            return *this;
        }
        
        reference& operator|=(Word_t value) 
        {
            PWord_t current = tree_.get(index_);
            *current |= value;
            return *this;
        }
        
        reference& operator^=(Word_t value) 
        {
            PWord_t current = tree_.get(index_);
            *current ^= value;
            return *this;
        }
        
        reference& operator++()
        {
            PWord_t current = tree_.get(index_);
            ++(*current);
            return *this;
        }
        
        Word_t operator++(int)
        {
            PWord_t current = tree_.get(index_);
            Word_t tmp = *current;
            ++(*current);
            return tmp;
        }
        
        operator Word_t()   const
        {
            return *tree_.get(index_);
        }
        
        ~reference() = default;
    
    };
        
    // перегрузка оператора []
    template<typename StringType>
    reference operator[](StringType&& index) &
    {
        return reference(*this, std::forward<StringType>(index));
    }

    // Функция at() для доступа по ключу версии non-const и const
    template<typename StringType>
    Word_t& at(StringType&& index) &
    {
        return at_impl_(std::forward<StringType>(index));
    }
    
    template<typename StringType>
    const Word_t& at(StringType&& index) const &
    {
        return at_impl_(std::forward<StringType>(index));
    }


//*************************************ITERATORS*************************************//

private:

    // Класс-родитель для итераторов
    template<typename Treeptr>
    class iterator_base {
    public:
        
        using iterator_category = std::bidirectional_iterator_tag;  // Категория итераторов(на основе нашего контейнера)
        using value_type =  std::pair<const std::string, Word_t>;
        using difference_type = std::ptrdiff_t;    // необходимо определить, не используется, будет std::distance O(n)
        using pointer = value_type*;
        using reference = value_type; 
        
    protected:
        
        Treeptr tree_;
        std::optional<std::string> current_index_;

        mutable std::optional<value_type> cached_value_;
        
        iterator_base(Treeptr tree, const std::optional<std::string> index)
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
            if(tree_ && current_index_.has_value())  {
                std::pair<std::string, PWord_t> next_val = tree_->next(current_index_.value());
                current_index_ = (next_val.second ? std::optional<std::string>(next_val.first) : std::nullopt);
            }
            // else UB
            return *this;
        }
        
        iterator_base& operator--()
        {
            if(tree_) {
                if(current_index_.has_value()) {
                    std::pair<std::string, PWord_t> prev_val = tree_->prev(current_index_.value());
                    current_index_ = (prev_val.second ? std::optional<std::string>(prev_val.first) : std::nullopt);
                }
                else {
                    std::pair<std::string, PWord_t> last_val = tree_->last(tree_->last_str_);
                    current_index_ = (last_val.second ? std::optional<std::string>(last_val.first) : std::nullopt);
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
        
        pointer operator->() const 
        {
            cached_value_.emplace(operator*());
            return &(*cached_value_);
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

public:

    // обычный итератор
    class iterator : public iterator_base<JudySL*> {
    private:

        friend class JudySL;
        friend class const_iterator;

        explicit iterator(JudySL* tree, const std::optional<std::string> index) 
            : iterator_base<JudySL*>(tree, index)
        { }

    public:

        iterator() = default;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;

        using iterator_base<JudySL*>::operator++;
        using iterator_base<JudySL*>::operator--;

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

    // константный итератор
    class const_iterator : public iterator_base<const JudySL*>{
    private:

        friend class JudySL;

        explicit const_iterator(const JudySL* tree, const std::optional<std::string> index) 
            : iterator_base<const JudySL*>(tree, index)
        { }

    public:

        const_iterator() = default;
        
        const_iterator(const iterator& other) 
            : iterator_base<const JudySL*>(other.tree_, other.current_index_)
        { }

        const_iterator& operator=(const const_iterator&) = default;

        using iterator_base<const JudySL*>::operator++;
        using iterator_base<const JudySL*>::operator--;
    
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

    // begin() итераторы
    iterator begin()   
    {
        std::pair<std::string, PWord_t> first_val = first("\0");
        return iterator(this, first_val.second ? std::optional<std::string>(first_val.first) : std::nullopt);
    }

    const_iterator begin()  const
    {
        std::pair<std::string, PWord_t> first_val = first("\0");
        return const_iterator(this, first_val.second ? std::optional<std::string>(first_val.first) : std::nullopt);
    }

    const_iterator cbegin() const
    {
        std::pair<std::string, PWord_t> first_val = first("\0");
        return const_iterator(this, first_val.second ? std::optional<std::string>(first_val.first) : std::nullopt);
    }

    // end() итераторы
    iterator end()
    {
        return iterator(this, std::nullopt);
    }

    const_iterator end()    const
    {
        return const_iterator(this, std::nullopt);
    }

    const_iterator cend()   const
    {
        return const_iterator(this, std::nullopt);
    }
    
    // rbegin() итераторы
    reverse_iterator rbegin()  
    {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crbegin()    const
    {
        return const_reverse_iterator(cend());
    }
    
    // rend() итераторы
    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend()   const
    {
        return const_reverse_iterator(begin());
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

    template<typename StringType>
    iterator lower_bound(StringType&& index)
    {
        first(std::forward<StringType>(index));
        return iterator(this, pvalue_ ? std::optional<std::string>(reinterpret_cast<const char*>(index_)) : std::nullopt);
    }

    template<typename StringType>
    const_iterator lower_bound(StringType&& index) const
    {
        first(std::forward<StringType>(index));
        return const_iterator(this, pvalue_ ? std::optional<std::string>(reinterpret_cast<const char*>(index_)) : std::nullopt);
    }

    template<typename StringType>
    iterator upper_bound(StringType&& index)
    {
        next(std::forward<StringType>(index));
        return iterator(this, pvalue_ ? std::optional<std::string>(reinterpret_cast<const char*>(index_)) : std::nullopt);
    }

    template<typename StringType>
    const_iterator upper_bound(StringType&& index)  const
    {
        next(std::forward<StringType>(index));
        return const_iterator(this, pvalue_ ? std::optional<std::string>(reinterpret_cast<const char*>(index_)) : std::nullopt);
    }

    template<typename StringType>
    std::pair<iterator, iterator> equal_range(StringType&& index)
    {
        return std::make_pair(lower_bound(std::forward<StringType>(index)), upper_bound(std::forward<StringType>(index)));
    }

    template<typename StringType>
    std::pair<const_iterator, const_iterator> equal_range(StringType&& index) const
    {
        return std::make_pair(lower_bound(std::forward<StringType>(index)), upper_bound(std::forward<StringType>(index)));
    }

    template<typename StringType>
    iterator find(StringType&& index)
    {
        get(index);
        return iterator(this, pvalue_ ? std::optional<std::string>(reinterpret_cast<const char*>(index_)) : std::nullopt);
    }

    template<typename StringType>
    const_iterator find(StringType&& index) const
    {
        get(index);
        return iterator(this, pvalue_ ? std::optional<std::string>(reinterpret_cast<const char*>(index_)) : std::nullopt);
    }

    iterator erase(iterator pos)
    {
        if(pos == end())
            throw std::invalid_argument("JudySL::Cannot erase end() iterator");
        if(pos.tree_ != this)
            throw std::invalid_argument("JudySL::Cannot erase iterator from different array");
    
        iterator next_it = pos;
        ++next_it;
        del(pos->first);

        return next_it;
    }

    iterator erase(const_iterator pos)
    {
        if(pos == cend())
            throw std::invalid_argument("JudySL::Cannot erase cend() const_iterator");
        if(pos.tree_ != this)
            throw std::invalid_argument("JudySL::Cannot erase const_iterator from different array");

        const_iterator next_it = pos;
        ++next_it;
        del(pos->first);

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
        while(first != last)
            first = erase(first);

        return iterator(this, first.current_index_);
    }

    template<typename StringType>
    size_type erase(StringType&& index)
    {
        return del(std::forward<StringType>(index));
    }

    void merge(JudySL& other) 
    {
        if (this == &other) return;

        iterator it = other.begin();
        while (it != other.end()) {
            if (!contains(it->first)) {
                *insert(it->first) = it->second;
                it = other.erase(it);
            } else 
                ++it;
        }
    }

    bool operator==(const JudySL& other) const
    {
        if(size() != other.size())
            return false;
        const_iterator it = cbegin();
        for(; it != cend(); ++it) {
            PWord_t pval = get(it->first);
            if(!pval || *pval != it->second)
                return false;
        }
        return true;
    }

    bool operator!=(const JudySL& other) const 
    {
        return !(*this == other);
    }
               
    // Деструктор для очищения данных
    ~JudySL()
    {
        JSLFA(rc_word_, arr_);

        delete[] last_str_;
        delete[] index_;
        if(debug_)
            std::cout << "Free " << rc_word_ << " bytes" << std::endl;
    }
    
};
// JudySL

// swap для удобства
void swap(JudySL& j1, JudySL& j2) noexcept
{
    j1.swap(j2);
}

std::ostream& operator<<(std::ostream& out, const JudySL::reference& obj) 
{
    return out << static_cast<Word_t>(obj);
}

std::istream& operator>>(std::istream& in, JudySL::reference obj)
{
    Word_t tmp; in >> tmp;
    obj = tmp;
    return in;
}

}
// judy
