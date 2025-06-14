#include "Judy.h"
#include <utility>          // for std::pair
#include <stdexcept>        // for std::out_of_range
#include <cstring>          // for std::memcpy
#include <initializer_list> // for std::initializer_list
#include <iostream>         // for std::cout
#include <optional>         // for std::optional
#include <string>           // for std::string

namespace judy {

// JudySL - map<const char*, Word_t>

// Обёртка для класса JudySL (для удобства использования)

// Мб добавить StringType через type_traits?

class JudySL {
private:

/***********************PRIVATE MEMBERS*******************************/

    using size_type = std::size_t;
    #define MAXLINELEN 1000000
    // inline static constexpr int MAXLINELEN = 1000000;
    // вообще MAXLINELEN нужно задавать либо через ограничения memset, либо через ограничения std::string
    
    mutable int Rc_int_;                 // код возврата функций
    mutable Word_t Rc_word_;             // число возврата(колво байт)
    mutable uint8_t index_[MAXLINELEN + 1];  // буфер для поиска
    
    mutable PWord_t PValue_;
    mutable void* ptr_;

    size_type population_; // количество занятых индексов дерева
    mutable size_type current_max_len_;   // текущая максимальная длина строки(оптимизация для last) 

    Pvoid_t arr_;    // Указатель на корень массива

    // Большого смысла пока не имеет, просто вывод в деструкторе количества освобождённой памяти
    inline static bool debug_ = false;

    // Думал про static, но непонятно как автоматизировать сборку мусора
    size_type last_str_cap_;    // текущий размер максимальной строки
    char* last_str_;            // максимальная строка
    
/***********************PRIVATE FUNCTIONS*******************************/

    // Вспомогательный метод для копирования std::string строк в наш uint8_t index_
    void copy_str_to_uint(const std::string& index) const
    {
        const std::size_t len = index.size();
        
        // либо делаем так
        if (len > MAXLINELEN) 
            throw std::invalid_argument("JudySL::index is too large");
        // Либо потом можно поменять логику на: первые MAXLENLINE-1 символов прочитали, а остальное игнорим
        
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
        if(PValue_ == nullptr)
            throw std::out_of_range("JudySL::at");
        return *PValue_;
    }

    void init_last_str_()
    {
        last_str_cap_ = 1;
        last_str_ = new char[2];
        last_str_[0] = '\xff'; last_str_[last_str_cap_] = '\0';
    }

    void last_str_realloc_(const std::size_t new_len)
    {
        if(new_len <= last_str_cap_)
            return;
        
        std::size_t new_cap = last_str_cap_;
        while(new_cap <= new_len)
            new_cap *= 2;

        char* new_str = new char[new_cap + 1];
        std::memcpy(new_str, last_str_, last_str_cap_);
        std::memset(new_str + last_str_cap_, 0xff, new_cap - last_str_cap_);
        new_str[new_cap] = '\0';
        
        delete[] last_str_;
        last_str_cap_ = new_cap;
        last_str_ = new_str;
    }

    size_type get_len_(const char* str)
    {
        return strlen(str) + 1;
    }

    size_type get_len_(const std::string& str)
    {
        return str.size();
    }

/***********************PUBLIC FUNCTIONS*******************************/

public:

    // Включает/выключает debug_
    static void set_debug_mode(const bool value)
    {
        debug_ = value;
    }
    
    // Базовый конструктор
    JudySL() 
        : Rc_int_(0)
        , Rc_word_(0)
        , PValue_(nullptr)
        , ptr_(nullptr)
        , population_(0)
        , current_max_len_(1)
        
    { 
        arr_ = (Pvoid_t) NULL;
        init_last_str_();
    }   
    
    // Конструктор на основе initializer_list
    JudySL(std::initializer_list<std::pair<const std::string, Word_t>> init_list) 
        : JudySL()
    {
        for(const auto& it : init_list) {
            insert(it.first);
            *PValue_ = it.second;
        }
    }

    template<typename It>
    JudySL(It first, It last)
        : JudySL()
    {
        for(;first != last; ++first)
            {
                insert(first->first);
                *PValue_ = (*first).second;
            }
    }

    // ОЧЕНЬ ВАЖНО, после ВСТАВКИ или УДАЛЕНИЯ идёт реорганизация и старые указатели теряются(нужно обновлять их)
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
        PValue_ = static_cast<PWord_t>(ptr_);
        return PValue_;
    }

    // Удаляет индекс, возвращает 1 если успешно, 0 если ничего не было
    template<typename StringType>
    int del(StringType&& index)
    {
        prepare_str(index);
        JSLD(Rc_int_, arr_, index_);
        population_ -= Rc_int_; 
        return Rc_int_;
    }

    // Возвращает указатель на arr_[index_], NULL если такого нет
    template<typename StringType>
    PWord_t get(StringType&& index) const
    {
        prepare_str(index);
        JSLG(ptr_, arr_, index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return PValue_;
    }
    
    // Возникает проблема: возвращаю указатель на огромный буфер данных(и считывание строки непонятно когда останавливать)
    // по той же причине невозможно скляпать std::string
    // Пустая строка(то есть '\0') ищет самый первый
    template<typename StringType>
    std::pair<std::string, PWord_t> first(StringType&& index)   const
    {
        prepare_str(index);
        JSLF(ptr_, arr_, index_);
        PValue_ = static_cast<PWord_t>(ptr_);

        return std::make_pair(std::string(reinterpret_cast<const char*>(index_)), PValue_);
    }
    
    // index + 1
    template<typename StringType>
    std::pair<std::string, PWord_t> next(StringType&& index)   const
    {
        prepare_str(index);
        JSLN(ptr_, arr_, index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(std::string(reinterpret_cast<const char*>(index_)), PValue_);
    }
    
    template<typename StringType>
    std::pair<std::string, PWord_t> last(StringType&& index)   const
    {
        prepare_str(index);
        JSLL(ptr_, arr_, index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(std::string(reinterpret_cast<const char*>(index_)), PValue_);
    }

    template<typename StringType>
    std::pair<std::string, PWord_t> prev(StringType&& index)   const
    {
        prepare_str(index);
        JSLP(ptr_, arr_, index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(std::string(reinterpret_cast<const char*>(index_)), PValue_);
    }
    
    // класс-имитация доступа к элементам по ссылке(потому что происходит реорганизация дерева)
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

      // Класс-родитель для итераторов
    template<typename Treeptr>
    class iterator_base {
    public:
        
        using iterator_category = std::bidirectional_iterator_tag;  // Категория итераторов(на основе нашего контейнера)
        using value_type =  std::pair<std::string, Word_t>;
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
            , current_index_(nullptr)
            , cached_value_()
        { }
        
        iterator_base(const iterator_base&) = default;
        
        iterator_base& operator=(const iterator_base&) = default;
        
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

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // begin() end() итераторы
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

    iterator end()
    {
        return iterator(this, std::nullopt);
    }

    const_iterator end()    const
    {
        return const_iterator(this, std::nullopt);
    }

    const_iterator cbegin() const
    {
        std::pair<std::string, PWord_t> first_val = first("\0");
        return const_iterator(this, first_val.second ? std::optional<std::string>(first_val.first) : std::nullopt);
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

    // очищает весь массив, количество очищенных байт в Rc_word_
    void clear()
    {
        JSLFA(Rc_word_, arr_);
        delete[] last_str_;
        init_last_str_();
    }  
               
    // Деструктор для очищения данных
    ~JudySL()
    {
        clear();
        delete[] last_str_;
        if(debug_)
            std::cout << "Free " << Rc_word_ << " bytes" << std::endl;
    }
    
};
// JudySL

}
// namespace judy
