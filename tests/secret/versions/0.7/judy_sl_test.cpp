#include "Judy.h"
#include <utility>          // for std::pair
#include <stdexcept>        // for std::out_of_range
#include <cstring>          // for std::memcpy
#include <initializer_list> // for std::initializer_list
#include <iostream> // for std::cout

namespace judy {

// JudySL - сет строк, то есть для каждой строки имеется какое-то word_t значение

// Обёртка для класса JudySL (для удобства использования)
// (нужно ли по ссылке передавать?)
// Index_ поменять Word_t на size_t
// что делать, static_cast или reinterpret_cast
// Вообще надо прям юзать JERR, PJERR, PPJERR
// template<typename Key, typename Type, cmp, alloc> 

// Мб добавить StringType через type_traits?

class JudySL {
private:

/***********************PRIVATE MEMBERS*******************************/
    #define MAXLINELEN 1000000
    // inline static constexpr int MAXLINELEN = 1000000;
    
    mutable int Rc_int_;                 // код возврата функций
    mutable Word_t Rc_word_;             // число возврата(колво байт)
    mutable uint8_t Index_[MAXLINELEN + 1];  // string
    
    mutable PWord_t PValue_;
    mutable void* ptr_;
    
    Pvoid_t arr_;    // Указатель на корень массива

    // Большого смысла пока не имеет, просто вывод в деструкторе количества освобождённой памяти
    inline static bool debug_ = false;
    
/***********************PRIVATE FUNCTIONS*******************************/

    // Вспомогательный метод для копирования std::string строк в наш uint8_t Index_
    void copy_str_to_uint(const std::string& index) const
    {
        const std::size_t len = index.size();
        
        // либо делаем так
        if (len > MAXLINELEN) 
            throw std::invalid_argument("JudySL::index is too large");
        // Либо потом можно поменять логику на: первые MAXLENLINE-1 символов прочитали, а остальное игнорим
        
        // возможно стоит сделать в стиле c++ и выполнять std::copy
        std::memcpy(Index_, index.data(), len);
        Index_[len] = '\0';
    }

    // Вспомогательный метод для копирования char* строк
    void prepare_str(const char* index) const
    {
        const std::size_t len = strlen(index) + 1;
        if (len > MAXLINELEN)
            throw std::invalid_argument("JudySL::index is too large");
        std::memcpy(Index_, index, len);
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
        if(PValue_ == nullptr_)
            throw std::out_of_range("JudySL::at");
        return *PValue_;
    }

    // реализация оператора []
    template<typename StringType>
    Word_t& Index__impl_(StringType&& index)
    {
        get(std::forward<StringType>(index));
        if(PValue_ == nullptr_)
            insert(std::forward<StringType>(index));
        return *PValue_;
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
    { 
        arr_ = (Pvoid_t) NULL;
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

    // ОЧЕНЬ ВАЖНО, после ВСТАВКИ или УДАЛЕНИЯ идёт реорганизация и старые указатели теряются(нужно обновлять их)
    template<typename StringType>
    PWord_t insert(StringType&& Index_)
    {
        prepare_str(Index_);
        JSLI(ptr_, arr_, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return PValue_;
    }
    
    // Удаляет индекс, возвращает 1 если успешно, 0 если ничего не было
    template<typename StringType>
    int del(StringType&& Index_)
    {
        prepare_str(Index_);
        JSLD(Rc_int_, arr_, Index_);
        return Rc_int_;
    }

    // Возвращает указатель на arr_[Index_], NULL если такого нет
    template<typename StringType>
    PWord_t get(StringType&& Index_) const
    {
        prepare_str(Index_);
        JSLG(ptr_, arr_, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return PValue_;
    }
    
    // Возникает проблема: возвращаю указатель на огромный буфер данных(и считывание строки непонятно когда останавливать)
    // по той же причине невозможно скляпать std::string
    // Пустая строка(то есть '\0') ищет самый первый
    template<typename StringType>
    std::pair<const char*, PWord_t> first(StringType&& Index_)   const
    {
        prepare_str(Index_);
        JSLF(ptr_, arr_, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(reinterpret_cast<const char*>(Index_), PValue_);
    }
    
    // Index_ + 1
    template<typename StringType>
    std::pair<const char*, PWord_t> next(StringType&& Index_)   const
    {
        prepare_str(Index_);
        JSLN(ptr_, arr_, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(reinterpret_cast<const char*>(Index_), PValue_);
    }
    
    template<typename StringType>
    std::pair<const char*, PWord_t> last(StringType&& Index_)   const
    {
        prepare_str(Index_);
        JSLL(ptr_, arr_, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(reinterpret_cast<const char*>(Index_), PValue_);
    }

    template<typename StringType>
    std::pair<const char*, PWord_t> prev(StringType&& Index_)   const
    {
        prepare_str(Index_);
        JSLP(ptr_, arr_, Index_);
        PValue_ = static_cast<PWord_t>(ptr_);
        return std::make_pair(reinterpret_cast<const char*>(Index_), PValue_);
    }
    
    // перегрузка оператора []
    template<typename StringType>
    Word_t& operator[](StringType&& Index_) &
    {
        return Index__impl_(std::forward<StringType>(Index_));
    }

    template<typename StringType>
    const Word_t& operator[](StringType&& Index_) const&
    {
        return Index__impl_(std::forward<StringType>(Index_));
    }

    // Функция at() для доступа по ключу версии non-const и const
    template<typename StringType>
    Word_t& at(StringType&& Index_) &
    {
        return at_impl_(std::forward<StringType>(Index_));
    }

    // не знаю есть ли смысл дублировать, т.к. в std::map там вообще итераторы и в const методе используются
    // const итераторы
    template<typename StringType>
    const Word_t& at(StringType&& Index_) const &
    {
        return at_impl_(std::forward<StringType>(Index_));
    }

    void clear()
    {
        JSLFA(Rc_word_, arr_);
    }
               
    // Деструктор для очищения данных
    ~JudySL()
    {
        JSLFA(Rc_word_, arr_); // очищает весь массив, количество очищенных байт в Rc_word_
        if(debug_)
            std::cout << "Free " << Rc_word_ << " bytes" << std::endl;
    }
    
};
// JudySL

}
// namespace judy


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <map>
#include <vector>

int main(int argc, char** argv)
{

    const std::map<std::string, int> mp = {
        {"Igor", 2},
        {"Bursin", 3}
    };

    const judy::JudySL tree = {
        {"Igor", 2},
        {"Bursin", 3}
    };

    std::vector<std::string> vec = {"Igor", "Bursin", "loh", "ebaniy", "test"};
    std::vector<PWord_t> ptr_;
    PWord_t PValue_;
   
    for(auto& it : {"Igor", "Bursin"})
        std::cout << "tree[" << it << "] = " << tree[it] << '\n';

    return 0;
}
