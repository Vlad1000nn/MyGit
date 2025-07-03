#include "Judy.h"
#include <utility>          // for std::pair
#include <stdexcept>        // for std::out_of_range
#include <cstring>          // for std::memcpy
#include <initializer_list> // for std::initializer_list

#include <iostream>

// JudyHS - хэш-таблица, ключ - массив байт, значение - слово
// ограничения на ключ: возможности malloc(about 2 GB), количество ключей - порядка миллиарда

// Обёртка для класса JudyHS (для удобства использования)
// Мб добавить StringType через type_traits?

// РАЗОБРАТЬСЯ с MAXLINELEN

class JudyHS {
private:

/***********************PRIVATE MEMBERS*******************************/
    
    inline static constexpr int MAXLINELEN = 1000000;
    
    mutable int Rc_int_;                 // код возврата функций
    mutable Word_t Rc_word_;             // число возврата(колво байт)
    mutable uint8_t Index_[MAXLINELEN + 1];  // string
    
    mutable PWord_t PValue_;
    mutable void* ptr_;
    
    Pvoid_t arr_;    // Указатель на корень массива
    
/***********************PRIVATE FUNCTIONS*******************************/

    // Вспомогательный метод для копирования std::string строк в наш uint8_t Index_
    void copy_str_to_uint(const std::string& index, const std::size_t len) const
    {   
        // либо делаем так
        if (len > MAXLINELEN) 
            throw std::invalid_argument("JudyHS::index is too large");
        // Либо потом можно поменять логику на: первые MAXLENLINE-1 символов прочитали, а остальное игнорим
        
        // возможно стоит сделать в стиле c++ и выполнять std::copy
        std::memcpy(Index_, index.data(), len);
    }

    // Вспомогательный метод для копирования char* строк
    void prepare_str(const char* index, const std::size_t len) const
    {
        if (len > MAXLINELEN)
            throw std::invalid_argument("JudyHS::index is too large");
        std::memcpy(Index_, index, len);
    }

    // Вспомогательный метод для копирования std::string строк
    void prepare_str(const std::string& Index_, const std::size_t len)  const
    {
        copy_str_to_uint(Index_, len);
    }

    template<typename T>
    void prepare_str(T) const = delete;

    // реализация метода at()
    template<typename StringType>
    Word_t& at_impl_(StringType&& Index_, const std::size_t len)    const
    {
        get(std::forward<StringType>(Index_), len);
        if(PValue_ == nullptr)
            throw std::out_of_range("JudyHS::at");
        return *PValue_;
    }

    // реализация оператора []
    template<typename StringType>
    Word_t& Index__impl_(StringType&& Index_, const std::size_t len)
    {
        get(std::forward<StringType>(Index_), len);
        if(PValue_ == nullptr)
            insert(std::forward<StringType>(Index_), len);
        return *PValue_;
    }

    static std::size_t str_len_(const std::string& Index_)
    {
        return Index_.size();
    }

    static std::size_t str_len_(const char* Index_)
    {
        return strlen(Index_);
    }

    template<typename T>
    static std::size_t str_len_(T) = delete;


/***********************PUBLIC FUNCTIONS*******************************/

public:
    
    // Базовый конструктор
    JudyHS() 
        : Rc_int_(0)
        , Rc_word_(0)
        , PValue_(nullptr)
        , ptr_(nullptr)
    { 
        arr_ = (Pvoid_t) NULL;
    }
    
    // Конструктор на основе initializer_list
    JudyHS(std::initializer_list<std::pair<const std::string, Word_t>> initList) 
        : JudyHS()
    {
        for(const auto& it : initList) {
            insert(it.first, it.first.size());
            *PValue_ = it.second;
        }
    }

    // мб геттеры вообще убрать(А зачем они обычному пользователю???)

    // Возврашает значение в Rc_int_
    int get_Rc_int_()    const
    {
        return Rc_int_;
    }
    
    // Возврашает значение в Rc_word_
    Word_t get_Rc_word_()    const
    {
        return Rc_word_;
    }


    // ОЧЕНЬ ВАЖНО, после ВСТАВКИ или УДАЛЕНИЯ идёт реорганизация и старые указатели теряются(нужно обновлять их)
    template<typename StringType>
    PWord_t insert(StringType&& index, std::size_t len = -1)
    {
        if(len == -1)
            len = str_len_(index);

        prepare_str(index, len);
        JHSI(ptr_, arr_, Index_, len);
        PValue_ = static_cast<PWord_t>(ptr_);
        return PValue_;
    }
    
    // Удаляет индекс, возвращает 1 если успешно, 0 если ничего не было
    template<typename StringType>
    int del(StringType&& index, std::size_t len = -1)
    {
        if(len == -1)
            len = str_len_(index);

        prepare_str(index, len);
        JHSD(Rc_int_, arr_, Index_, len)
        return Rc_int_;
    }

    // Возвращает указатель на arr_[Index_], NULL если такого нет
    template<typename StringType>
    PWord_t get(StringType&& index, std::size_t len = -1) const
    {
        if(len == -1)
            len = str_len_(index);

        prepare_str(index, len);
        JHSG(ptr_, arr_, Index_, len);
        PValue_ = static_cast<PWord_t>(ptr_);
        return PValue_;
    }
    
    // перегрузка оператора []
    template<typename StringType>
    Word_t& operator[](StringType&& index) &
    {
        const std::size_t len = str_len_(index);
        return Index__impl_(std::forward<StringType>(Index_), len);
    }

    template<typename StringType>
    const Word_t& operator[](StringType&& index) const&
    {
        const std::size_t len = str_len_(index);
        return Index__impl_(std::forward<StringType>(Index_), len);
    }

    // Функция at() для доступа по ключу версии non-const и const
    template<typename StringType>
    Word_t& at(StringType&& index, std::size_t len = -1) &
    {
        if(len == -1)
            len = str_len_(index);
        return at_impl_(std::forward<StringType>(Index_), len);
    }

    // не знаю есть ли смысл дублировать, т.к. в std::map там вообще итераторы и в const методе используются
    // const итераторы
    template<typename StringType>
    const Word_t& at(StringType&& index, std::size_t len = -1) const &
    {
        if(len == -1)
            len = str_len_(index);
        return at_impl_(std::forward<StringType>(Index_), len);
    }
               
    // Деструктор для очищения данных
    ~JudyHS()
    {
        //J1FA(Rc_word_, arr_); 
        JHSFA(Rc_word_, arr_); // очищает весь массив, количество очищенных байт в Rc_word_
        printf("Free %lu bytes\n", Rc_word_);
    }
    
};
// JudyHS
