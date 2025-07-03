#pragma once

#include <cstddef> // for std::size_t
#include <initializer_list> // for std::initializer_list
#include <utility>
#include <optional>
#include <stdexcept>

#include "Judy.h"

namespace judy {

/*************************************JUDY L************************************* 
    Обёртка для класса JudyL (для удобства использования)

    ОК:
    
    for(auto it : j) { }                        
    for(const auto& it : j) { }             
    for(auto [key, val] : j) { }            
    for(const auto& [key, val] : j) { }     

НЕ ОК:
    
    for(auto& it : j) { }                   
    for(auto& [key, val] : j) { }       
    
********************************************************************************/

class JudyL {
private:

//*************************************PRIVATE MEMBERS*************************************//

    using size_type = std::size_t;

    using Word_t = unsigned long;
    using PWord_t = Word_t*;
    using PPWord_t = PWord_t*;
    using Pvoid_t = void*;
    using PPvoid_t = Pvoid_t*;

    mutable int rc_int_;     // код возврата функций
    mutable Word_t rc_word_; // слово возврата функций
    mutable Word_t index_;   // индекс для поиска

    mutable PWord_t pvalue_; // указатель на значения
    mutable Pvoid_t ptr_;      // void* указатель для совместимости с макросами

    Pvoid_t arr_;    // Указатель на корень массива

    // Большого смысла пока не имеет, просто вывод в деструкторе количества освобождённой памяти
    inline static bool debug_ = false;

public:

//*************************************CONSTURCTORS*************************************//

    // Базовый конструктор
    JudyL() 
        : rc_int_(0)
        , rc_word_(0)
        , index_(0)
        , pvalue_(nullptr)
        , ptr_(nullptr)
    { 
        arr_ = (Pvoid_t) NULL;
    }

    // Конструктор на основе списка инициализации
    JudyL(std::initializer_list<std::pair<Word_t, Word_t>> init_list) : JudyL()
    {
        for(const auto& [key, value] : init_list) {
            if(get(key))
                continue;
            insert(key);
            *pvalue_ = value;
        }
    }
    
    // Конструктор для контейнеров с value_type - интегральный тип (под key будем тут принимать просто index)
    // std::array, std::vector, std::deque, std::list, std::forward_list, std::set, std::multiset, std::unordered_set,
    // std::unordered_multiset, std::string, std::wstring  
    template<typename Container, std::enable_if_t<std::is_integral_v<typename Container::value_type>, int> = 0>
    JudyL(const Container& container) 
        : JudyL()
    {
        std::size_t i = 0;
        for(const auto& value : container) {
            insert(i);
            *pvalue_ = value;
            ++i;
        }
    }
    
    // Чуть-чуть SFINAE для прокачки скиллов(необязательна тут, ошибка компиляции если нет first_second будет и без них)
    // Конструктор для итераторов для контейнеров пар
    template<typename It, typename = decltype(std::declval<It>()->first, std::declval<It>()->second, void())>
    JudyL(It first, It last) 
        : JudyL()
    {
        for(; first != last; ++first) {
            if(get((*first).first))
                continue;
            insert((*first).first);
            *pvalue_ = (*first).second;
        }
    }

    // deep copy constuctor
    JudyL(const JudyL& other)   
        : JudyL()
    {
        const_iterator it = other.cbegin();
        for(; it != other.cend(); ++it)
            *insert(it->first) = it->second;
    }

    // Оператор присваивания
    JudyL& operator=(const JudyL& other)
    {
        if(this != &other) {
            clear();
            const_iterator it = other.begin();
            for(; it != other.end(); ++it)
                *insert(it->first) = it->second;
        }

        return *this;
    }
    
    // move-присваивание
    JudyL& operator=(JudyL&& other) noexcept
    {
        if(this != &other) {
            arr_ = other.arr_;
            rc_int_ = other.rc_int_;
            rc_word_ = other.rc_word_;
            index_ = other.index_;
            pvalue_ = other.pvalue_;
            ptr_ = other.ptr_;
            
            other.arr_ = nullptr;
            other.rc_int_ = other.rc_word_ = other.index_ = 0;
            other.pvalue_ = nullptr;
            other.ptr_ = nullptr;
        }
        
        return *this;
    }

    // move-конструктор
    JudyL(JudyL&& other) noexcept
        : rc_int_(other.rc_int_)
        , rc_word_(other.rc_word_)
        , index_(other.index_)
        , pvalue_(other.pvalue_)
        , ptr_(other.ptr_)
        , arr_(other.arr_)
    {
        other.arr_ = nullptr;
        other.rc_int_ = other.rc_word_ = other.index_ = 0;
        other.pvalue_ = nullptr;
        other.ptr_ = nullptr;
    }

/*************************************JUDY MACROS FUNCS*************************************
    Я решил их оставить в публичном доступе на усмотрение пользователя(вдруг он хочет 
    собственноручно что-нибудь сделать, да и обёртка класса не использует некоторые ПОЛЕЗНЫЕ
    методы)
********************************************************************************************/

   // Вставляет index в массив, возвращает указатель на вставленное значение(для того, чтобы его можно было изменить)
   // Если успешно вставлен, то значение инициализируется 0. Если index уже был, то ничего не меняется.
   // Возвращает указатель на JERR(-1), если ошибка в malloc()
   PWord_t insert(const Word_t& index)
   {
        index_ = index;
        JLI(ptr_, arr_, index_);
        pvalue_ = static_cast<PWord_t>(ptr_);
        
        return pvalue_;
    }
    
    // удаление по индексу из массива. Возвращает 1 если успешно, 0 - если индекса не было, -1 если ошибка в malloc()
    int del(const Word_t& index) 
    {
        JLD(rc_int_, arr_, index);
        return rc_int_;
    }
    
    // возвращает указатель на элемент index, либо если его нет указатель на 0
    PWord_t get(const Word_t& index)    const   noexcept
    {
        JLG(ptr_, arr_, index);
        pvalue_ = static_cast<PWord_t>(ptr_);
        return pvalue_;
    }
    
    // Вовзаращет количество занятых индексов между index1 и index2 включительно
    // Для подсчёта всех - 0 и -1
    Word_t count(const Word_t& index1, const Word_t& index2)    const   noexcept
    {  
        JLC(rc_word_, arr_, index1, index2);
        return rc_word_;
    }

    // возвращает n-й занятый элемент в массиве (n = 1 - первый)
    std::pair<PWord_t, Word_t> ncount(const Word_t& n)  const   noexcept
    {
        JLBC(ptr_, arr_, n, index_);
        pvalue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(pvalue_, index_);
    }
    
    // Возвращает количество байт которые в данный момент занимает массив
    // (очень быстрый, особенно до/после Insert/Delete)
    Word_t memused()    const   noexcept
    {
        JLMU(rc_word_, arr_);
        return rc_word_;
    }
    
    // Возвращает первый попавшийся бит начиная с index(начать с 0 чтобы найти в массиве в целом первый бит)
    // Если не нашёл, то first.first указывает на 0, а first.second - мусор
    std::pair<PWord_t, Word_t> first(const Word_t& index)   const   noexcept
    {
        index_ = index;
        JLF(ptr_, arr_, index_);
        pvalue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(pvalue_, index_);
    }

    // Возвращает первый попавшийся бит начиная с index+1
    // Если не нашёл, то next.first указывает на 0, а next.second - мусор
    std::pair<PWord_t, Word_t> next(const Word_t& index)    const   noexcept
    {
        index_ = index;
        JLN(ptr_, arr_, index_);
        pvalue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(pvalue_, index_);
    }

    // ищет начиная с index первый бит (в обратном порядке, т.е. справа налево)
    // Если не нашёл, то last.first указывает на 0, а last.second - мусор
    std::pair<PWord_t, Word_t> last(const Word_t& index)    const   noexcept
    {
        index_ = index;
        JLL(ptr_, arr_, index_);
        pvalue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(pvalue_, index_);
    }

    // ищет начиная с index-1 первый бит
    // Если не нашёл, то prev.first указывает на 0, а prev.second - мусор
    std::pair<PWord_t, Word_t> prev(const Word_t& index)    const   noexcept
    {
        index_ = index;
        JLP(ptr_, arr_, index_);
        pvalue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(pvalue_, index_);
    }

    // начиная с index находит первый незанятый
    // Если не нашёл, то first_empty.first указывает на 0, а first_empty.second - мусор
    std::optional<Word_t> first_empty(const Word_t& index) const    noexcept
    {
        index_ = index;
        JLFE(rc_int_, arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    // начиная с index+1 находит первый незанятый
    std::optional<Word_t> next_empty(const Word_t& index)  const    noexcept
    {
        index_ = index;
        JLNE(rc_int_ , arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    // начиная с index находит первый незанятый в обратном порядке (справа налево)
    std::optional<Word_t> last_empty(const Word_t& index)  const    noexcept
    {
        index_ = index;
        JLLE(rc_int_, arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    // начиная с index-1 находит первый незанятый в обратном порядке (справа налево)
    std::optional<Word_t> prev_empty(const Word_t& index)  const    noexcept
    {
        index_ = index;
        JLPE(rc_int_, arr_, index_);
        return (rc_int_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

//*************************************CONTAINER FUNCS*************************************//
    
    // Количество занятых индексов
    size_type size()  const noexcept
    {
        return count(0, -1);
    }
    
    // Проверка на пустоту
    bool empty()    const   noexcept
    {
        return size() == 0;
    }
    
    // Очистка массива (arr_ -> nullptr, rc_word_ хранит количество освобождённых байт)
    void clear()
    {
        JLFA(rc_word_, arr_);
    }
    
    // обмен с другим JudyL
    void swap(JudyL& other) noexcept
    {
        std::swap(arr_, other.arr_);
        std::swap(rc_int_, other.rc_int_);
        std::swap(rc_word_, other.rc_word_);
        std::swap(index_, other.index_);
        std::swap(pvalue_, other.pvalue_);
        std::swap(ptr_, other.ptr_);
    }

    // Подсчёт количества значений для index(0 или 1 для JudyL)
    size_type count(const Word_t& index)  const noexcept
    {   
        return (get(index) ? 1 : 0);
    }

    // Проверка, содержится ли индекс
    bool contains(const Word_t& index)    const noexcept
    {
        return get(index) != nullptr;
    }

    // Включает/выключает debug_
    static void set_debug_mode(const bool value)    noexcept
    {
        debug_ = value;
    }

/*************************************REFERENCE*************************************
    Здесь используем класс reference, потому что JudyL перестраивается при вставках
    или удалениях, соответственно строки типа tree[1] = tree[2] + tree[3] имеют
    неопределённое поведение при отсутствии индексов 1,2,3 в tree.
    Почему? Оператор [] при отсутствии индекса автоматически вставляет его в дерево. 
    А после каждой новой вставки, старый указатель из метода get теряет свою 
    актуальность и потребуется заново выполнять get
***********************************************************************************/

    class reference {
    private:

        friend class JudyL;

        JudyL& tree_;
        Word_t index_;

        reference();

    public:

        explicit reference(JudyL& tree, const Word_t index)
            : tree_(tree)
            , index_(index)
        { 
            if(!tree_.get(index_))
                tree_.insert(index_);
        }

        reference(const reference&) = default;

        reference& operator=(Word_t value)
        {
            *tree_.get(index_) = value;
            return *this;
        }

        reference& operator=(const reference& other)
        {
            *tree_.get(index_) = static_cast<Word_t>(other);
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

        operator Word_t() const noexcept
        {
            return *tree_.get(index_);
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
        if(pvalue_ == nullptr)
            throw std::out_of_range("Judyl::at");
        
        return *pvalue_;
    }
    
    const Word_t& at(const Word_t& index)   const
    {
        get(index);
        if(pvalue_ == nullptr)
            throw std::out_of_range("Judyl::at");
            
        return *pvalue_;
    }

//*************************************ITERATORS*************************************//

private:

    // Класс-родитель для итераторов
    template<typename Treeptr>
    class iterator_base {
        public:
        
        using iterator_category = std::bidirectional_iterator_tag;  // Категория итераторов(на основе нашего контейнера)
        using value_type =  std::pair<const Word_t, Word_t>;
        using difference_type = std::ptrdiff_t;    // необходимо определить, не используется, будет std::distance O(n)
        using pointer = value_type*;
        using reference = value_type; // с ссылкой не знаю что делать, оставлю по значению всё равно
        
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

        pointer operator->() const 
        {
            cached_value_.emplace(operator*());
            return &(*cached_value_);
        }
        
        bool operator==(const iterator_base& other)  const noexcept
        {
            return tree_ == other.tree_ && current_index_ == other.current_index_;
        }
        
        bool operator!=(const iterator_base& other)  const noexcept
        {
            return !(*this == other);
        }
        
        ~iterator_base() = default;
        
    };
    // iterator_base
    
public:

    // Обычный итератор
    class iterator : public iterator_base<JudyL*> {
    private:

        friend class JudyL;
        friend class const_iterator;

        explicit iterator(JudyL* tree, std::optional<Word_t> index) 
            : iterator_base<JudyL*>(tree, index)
        { }

    public:

        iterator() = default;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;

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

    // Константный итератор
    class const_iterator : public iterator_base<const JudyL*>{
    private:

        friend class JudyL;

        explicit const_iterator(const JudyL* tree, const std::optional<Word_t> index) 
            : iterator_base<const JudyL*>(tree, index)
        { }

    public:

        const_iterator() = default;
        
        const_iterator(const iterator& other) 
            : iterator_base<const JudyL*>(other.tree_, other.current_index_)
        { }

        const_iterator& operator=(const const_iterator&) = default;

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

    // Для reverse версий итераторов просто воспользуемся std::reverse_iterator
    // Нам это позволяет сделать полная реализация итераторов
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // begin() итераторы
    iterator begin()
    {
        first(0);
        return iterator(this, (pvalue_ ? std::optional<Word_t>(index_) : std::nullopt));
    }

    const_iterator begin()  const
    {
        first(0);
        return const_iterator(this, (pvalue_ ? std::optional<Word_t>(index_) : std::nullopt));
    }

    const_iterator cbegin() const
    {
        first(0);
        return const_iterator(this, (pvalue_ ? std::optional<Word_t>(index_) : std::nullopt));
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
    
    const_iterator cend()    const
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

    iterator lower_bound(const Word_t& index)
    {
        first(index);
        return iterator(this, pvalue_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    const_iterator lower_bound(const Word_t& index) const
    {
        first(index);
        return const_iterator(this, pvalue_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    iterator upper_bound(const Word_t& index)
    {
        next(index);
        return iterator(this, pvalue_ ? std::optional<Word_t>(index_) : std::nullopt);
    }

    const_iterator upper_bound(const Word_t& index) const
    {
        next(index);
        return const_iterator(this, pvalue_ ? std::optional<Word_t>(index_) : std::nullopt);
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
        return iterator(this, pvalue_ ? std::optional<Word_t>(index) : std::nullopt);
    }

    const_iterator find(const Word_t& index)    const
    {
        get(index);
        return const_iterator(this, pvalue_ ? std::optional<Word_t>(index) : std::nullopt);
    }

    iterator erase(iterator pos)
    {
        // можно просто делать выход, обработку ошибок пока под вопросом оставлю
        if(pos == end())
            throw std::invalid_argument("JudyL::Cannot erase end() iterator");
        if(pos.tree_ != this)
            throw std::invalid_argument("JudyL::Cannot erase iterator from different array");
    
        iterator next_it = pos;
        ++next_it;
        del(pos->first);

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
        while((first != last))
            first = erase(first);

        return iterator(this, first.current_index_);
    }

    size_type erase(const Word_t& index)
    {
        return del(index);
    }

    void merge(JudyL& other) 
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

//**************************CLASS FUNCS*******************************/

    // Оператор сравнения
    bool operator==(const JudyL& other) const
    {
        if(size() != other.size())
            return false;

        const_iterator it = cbegin();
        for(; it != cend(); ++it)
            if(!other.get(it->first) || *(other.pvalue_) != it->second)
                return false;

        return true;
    }

    // Оператор неравенства
    bool operator!=(const JudyL& other) const
    {
        return !(*this == other);
    }

    // Деструктор
    ~JudyL() noexcept
    {
        clear();
        if(debug_)
            std::clog << "Free " << rc_word_ << " bytes" << std::endl;
    }
    
};
// JudyL


// swap для удобства
void swap(JudyL& j1, JudyL& j2) noexcept
{
    j1.swap(j2);
}

std::ostream& operator<<(std::ostream& out, const JudyL::reference& obj) 
{
    return out << static_cast<Word_t>(obj);
}

std::istream& operator>>(std::istream& in, JudyL::reference obj)
{
    Word_t tmp; in >> tmp;
    obj = tmp;
    return in;
}


} // judy
