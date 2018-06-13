//
// Created by mustang on 18-6-13.
//

#include <memory>
#include <newt.h>
#include "StrVec.h"
// 添加元素
void StrVec::push_back(const string &str)
{
    check_cap();
    alloc.construct(first_free++, str);
}

// 检查是否有足够的空间接纳元素
void StrVec::check_cap()
{
    if (size() == capacity())
    {
        re_alloc_2n();
    }
}

// 拷贝构造
StrVec::StrVec(const StrVec &ori)
{
    auto new_data{copy_n(ori.begin(), ori.end())};
    element = new_data.first;
    first_free = cap = new_data.second;
}

// 赋值运算符
StrVec& StrVec::operator=(const StrVec &ori)
{
    auto new_data{copy_n(ori.begin(),ori.end())};
    free();
    element = new_data.first;
    first_free = cap = new_data.second;
    return *this;
}

StrVec::~StrVec()
{
    free();
}

unsigned long StrVec::size() const
{
    return first_free - element;
}

unsigned long StrVec::capacity() const
{
    return cap - element;
}

void StrVec::re_alloc_2n()
{
    auto newCapacity{size() ? 2 * size() : 1};
    auto new_element{alloc.allocate(newCapacity)};
    auto head{element};
    auto tmp{new_element};
    while (head != first_free)
    {
        alloc.construct(tmp++, std::move(*head++)); //如果没有写move则导致使用string的拷贝构造函数,有性能损耗
    }
    free();
    element = new_element;
    first_free = tmp;
    cap = element + newCapacity;
};


//
pair<string *, string *> StrVec::copy_n(const string *b, const string *e)
{
    auto new_element{alloc.allocate(e - b)};
    return {new_element, std::uninitialized_copy(b, e, new_element)};
};

// 实现resize只管和现在的size()做比较即可,无需和capacity进行比较
// 和capacity进行比较的工作由push_back完成
void StrVec::resize(string::size_type L, const string &str)
{
    if (L > size())
    {
        while (L>size())
        {
            push_back(str);
        }
    } else if (L < size())
    {
        while (L < size())
        {
            alloc.destroy(--first_free);
        }
    }
}

void StrVec::resize(string::size_type L)
{
    if (L > size())
    {
        while (L>size())
        {
            push_back("");
        }
    } else if (L < size())
    {
        while (L < size())
        {
            alloc.destroy(--first_free);
        }
    }
}



void StrVec::free()
{
    // 一定注意检查deallocate函数调用时的参数合法性
    if (element)
    {
        auto tmp{first_free};
        while (tmp != element)
        {
            alloc.destroy(--tmp);
        }
        alloc.deallocate(element, cap - element);
    }
}
