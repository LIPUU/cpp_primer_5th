#include <iostream>
#include "string_i.h"
#include "vector"

using std::string;
using std::ostream;
using std::cout;
using std::endl;

ostream &operator<<(ostream &, string_i &obj);

// 测试来自陈硕的文章
void foo(string_i x)
{
}

void bar(const string_i &x)
{
}

string_i baz()
{
    string_i ret("world");
    return ret;
}

int main()
{
    string_i s0;
    string_i s1("hello");
    string_i s2(s0);
    string_i s3 = s1;
    s2 = s1;

    foo(s1);
    bar(s1);
    foo("temporary");
    bar("temporary");
    string_i s4 = baz();
    s4.debug_print(cout)<<endl;


    std::vector<string_i> svec;
    svec.push_back(s0);
    svec.push_back(s1);
    svec.push_back(baz());
    svec.push_back("good job");
    for (const auto &it:svec)
    {
        it.debug_print(cout)<<endl;
    }

    string_i fuck("12456456456ssss4653");
    string_i shit;
    std::cout<< shit.size() <<std::endl;
    shit = fuck;
    std::cout<< shit.size() <<std::endl;
    std::cout<< shit.capacity() <<std::endl;
    shit.debug_print(cout)<<endl;


    string_i ss1("798");
    string_i ss2;
    ss2 = std::move(ss1);
    ss2.debug_print(cout)<<endl;

    string_i ss3("123456789");
    string_i ss4(std::move(ss3));
    ss4.debug_print(cout)<<endl;

    ss4[1] = 'v';
    for (auto i(0); i != ss4.size(); ++i)
    {
        std::cout << ss4[i];
    }std::cout<<std::endl;

    const string_i ss5("abcdefg");
    // 这句代码是错误的,因为ss5是一个const对象,也就是说对它使用下标运算符将返回一个const char&,不允许对其赋值
    // ss5[1]='c';



}