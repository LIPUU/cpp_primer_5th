//
// Created by mustang on 18-6-14.
//

#ifndef STRING_STRING_I_H
#define STRING_STRING_I_H

#include <memory>

class string_i
{
    friend int main();
private:
    std::allocator<char> alloca;
    char *element;
    char *first_free;
    char *cap;

// tool function
private:
    unsigned char_data_length(const char*);
    char* begin() const;
    char* end() const;
    void free();
    void realloc();
// function
public:
    // 默认构造
    string_i()
    {
        first_free=element = alloca.allocate(15);
        cap = element + 15;
    }

    // c风格字符串指针参数构造函数
    string_i(const char* data);

    // 接受string_i参数的拷贝构造函数
    string_i(const string_i&);



    std::ostream& debug_print(std::ostream&) const;
    unsigned long size() const;

    // 重载赋值运算符,从一个 char* 复制数据
    string_i&operator=(const char*);

    // 重载赋值运算符,从一个string_i复制数据
    string_i&operator=(const string_i&);

    unsigned long capacity()
    {
        return cap - element;
    }

    // 移动构造函数
    string_i(string_i&& that) noexcept ;

    // 移动赋值运算符
    string_i&operator=(string_i&& that) noexcept ;

    char&operator[](std::size_t n)
    {
        return *(element+n);
    }

    const char&operator[](std::size_t n) const
    {
        return *(element+n);
    }

    void swap(string_i &, string_i &);

    void check_idle_position();

    void push_back(char);

    ~string_i();
};

#endif //STRING_STRING_I_H
