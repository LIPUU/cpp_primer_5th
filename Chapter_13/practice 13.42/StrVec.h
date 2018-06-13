//
// Created by mustang on 18-6-13.
//

#ifndef INC_12_3_STRVEC_H
#define INC_12_3_STRVEC_H
#include <iostream>
#include "string"

using std::string;
using std::allocator;
using std::pair;

class StrVec
{
    friend int main();
    friend class StrBlob;
    friend class StrBlobPtr;
    // member
private:

    allocator<string> alloc;
    string *element;
    string *first_free;
    string *cap;

    //tool function
private:
    // 检查是否有足够的空间接纳元素
    void check_cap();

    // 重新分配内存
    void re_alloc_2n();

    unsigned long size()const ; // 实际元素数量
    unsigned long capacity()const ; // 实际容量

    pair<string *, string *> copy_n(const string *, const string *);


    // debug
    void debug_print()
    {
        auto b{element};
        auto e(first_free);
        while (b != e)
        {
            std::cout<< *b++ <<" ";
        }
    }

    void resize(string::size_type, const string &str);
    void resize(string::size_type);

    void free();

public:

    // 默认构造
    explicit StrVec() :
            element(nullptr), cap(nullptr), first_free(nullptr)
    {}

    StrVec(std::initializer_list<string> li)
    {
        auto init_data{copy_n(li.begin(), li.end())};
        element = init_data.first;
        first_free = cap=init_data.second;
    }

    // 拷贝构造
    StrVec(const StrVec &);

    // 赋值运算符
    StrVec &operator=(const StrVec &);
    string&operator[](unsigned long curr)
    {
        auto tmp{element + curr};
        return *tmp;
    }
    string* begin() const{ return element; }
    string* end() const { return first_free; }

    void push_back(const string &);

    ~StrVec();
};
#endif //INC_12_3_STRVEC_H
