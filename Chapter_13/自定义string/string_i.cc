//
// Created by mustang on 18-6-14.
//
#include <iostream>
#include <algorithm>
#include "string_i.h"

string_i::string_i(const char *data):element(nullptr),first_free(nullptr),cap(nullptr)
{
    auto char_length(char_data_length(data));
    for (auto p = data; p != data + char_length; ++p)
    {
        push_back(*p);
    }
}

// 从另外一个string_i类型的参数构造本string_i
string_i::string_i(const string_i &ori)
{

    if (ori.size() > 15)
    {
        element = alloca.allocate(ori.size());
        std::uninitialized_copy(ori.begin(), ori.end(), element);
        first_free = cap = element + ori.size();
    } else if (ori.size() <= 15)
    {
        element = alloca.allocate(15);
        first_free = std::uninitialized_copy(ori.begin(), ori.end(), element);
        cap = element + 15;
    }
}

// 从一个char*通过=赋值将本string_i中的数据覆盖
string_i &string_i::operator=(const char *ori_char)
{

    auto data_length{char_data_length(ori_char)};
    bool need_new_memory{data_length > size()};

    if (need_new_memory)
    {
        free();
        element = alloca.allocate(data_length);
        std::uninitialized_copy(ori_char, ori_char + data_length, element);
        first_free = cap = element + data_length;
    } else
    {
        std::for_each(element, first_free, [this](const char &c)
        { alloca.destroy(&c); });
        first_free = std::uninitialized_copy(ori_char, ori_char + data_length, element);
    }
    return *this;
}

// 从另一个string_i通过=赋值将本string_i中的数据覆盖
string_i &string_i::operator=(const string_i &ori_string_i)
{
    /*
     * Sometimes within functions we dont need to reallocate menory,we can pass-by-value then use swap to implement operator= function.
     * But consider a String assignment operator,which releases old memory and allocates new memory only if the existing memory is
     *      insufficients to hold a copy of the right hand side String object.
     * So we can only discard pass-by-values,and in this case, in particular would need to accept its parameter by const reference,
     *      just like this section of the code.
     * */

    if (&ori_string_i == this)
    {
        return *this;
    }

    bool need_new_memory{ori_string_i.size() > size()};

    if (need_new_memory)
    {
        free();
        auto data_length{ori_string_i.size()};
        element = alloca.allocate(data_length);
        first_free = cap = std::uninitialized_copy(ori_string_i.begin(), ori_string_i.end(), element);
    } else if (!need_new_memory)
    {
        std::for_each(element, first_free, [this](const char &c)
        { alloca.destroy(&c); });
        std::uninitialized_copy(ori_string_i.begin(), ori_string_i.end(), element);
        first_free = element + ori_string_i.size();
    }

    return *this;
}

string_i::string_i(string_i&& that)noexcept :element(that.element),first_free(that.first_free),cap(that.cap)
{
    std::cout<< "使用了移动构造函数" <<std::endl;
    that.first_free = that.element = that.cap = nullptr;
}


string_i&string_i::operator=(string_i&& that) noexcept
{
    std::cout<< "使用了移动赋值运算符" <<std::endl;
    swap(*this, that);
    return *this;
}

void string_i::swap(string_i & lhs, string_i & rhs)
{
    std::swap(lhs.element, rhs.element);
    std::swap(lhs.first_free, rhs.first_free);
    std::swap(lhs.cap, rhs.cap);
}

char *string_i::begin() const
{
    return element;
}

char *string_i::end() const
{
    return begin() + size();
}

unsigned string_i::char_data_length(const char *data)
{
    unsigned l{0};
    auto shit{data};
    while (*shit++ != '\0')
    {
        ++l;
    }

    return l;
}

std::ostream &string_i::debug_print(std::ostream &os) const
{
    for (auto tmp{element}; tmp != first_free;)
    {
        os << *tmp++;
    }
    return os;
}

unsigned long string_i::size() const
{
    if(first_free==nullptr&&element==nullptr)
    {
        return 0;
    }
    return first_free - element;
}

string_i::~string_i()
{
    free();
}

void string_i::free()
{
    std::for_each(begin(), end(), [this](const char &c)
    { alloca.destroy(&c); });
    alloca.deallocate(element, capacity());
    element = first_free = cap = nullptr;
}

void string_i::push_back(char c)
{
    check_idle_position();
    alloca.construct(first_free++, c);
}

void string_i::check_idle_position()
{
    bool need_new_memory(size() == capacity());

    if (!need_new_memory)
    {
        return;
    }

    realloc();
}

void string_i::realloc()
{
    auto new_memory_length(size() == 0 ? 1 : 2 * size());

    if(size()!=0)
    {
        auto old_element(element);
        auto old_first_free(first_free);
        auto old_capacity(capacity());

        element = alloca.allocate(new_memory_length);
        first_free=std::uninitialized_copy(old_element, old_first_free, element);
        cap = element + new_memory_length;

        std::for_each(old_element, old_first_free, [this](const char &c)
        { alloca.destroy(&c); });
        alloca.deallocate(old_element,old_capacity);

        return;
    }else if(size()==0)
    {
         first_free= element = alloca.allocate(new_memory_length);
         cap = element + new_memory_length;
    }
}

