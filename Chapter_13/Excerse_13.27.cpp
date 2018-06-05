 
#include <iostream>
using namespace std;
class HasPtr
{
    friend int main();
private:
    string *ps;
    int i;
    unsigned *shared_count;
public:
    explicit HasPtr(const string &s = string()) : ps(new std::string(s)), i(0), shared_count(new unsigned(1)) { }

    // 拷贝构造函数
    HasPtr(const HasPtr& ori):ps(ori.ps),i(ori.i),shared_count{ori.shared_count}
    {
        ++*shared_count;
    }

    // 拷贝赋值运算符
    HasPtr&operator=(const HasPtr& ori)
    {
        if(--*shared_count==0)
        {
            (*this).~HasPtr();
        }
        shared_count=ori.shared_count;
        ++*shared_count;
        ps=ori.ps;
        i=ori.i;
        return *this;
    }

    //拷贝赋值运算符
    HasPtr&operator=(const string& ori)
    {
        if(--*shared_count==0)
        {
            (*this).~HasPtr();
        }

        ps = new string(ori);
        shared_count = new unsigned(1);
        return *this;
    }

    // 解引用运算符
    string&operator*()
    {
        return *ps;
    }

    //析构
    ~HasPtr()
    {
        if(--*shared_count==0)
        {
            delete ps;
            delete shared_count;
        }
    }

};

int main()
{
    HasPtr h1("abc");
    std::cout<< *h1.shared_count <<std::endl;
    HasPtr h2(h1);
    std::cout<< *h1.shared_count <<std::endl;
    std::cout<< *h2.shared_count <<std::endl;
    HasPtr h3("abc");
    h2 = h3;
    std::cout<< *h3.shared_count <<std::endl;
    h2="abc";
    std::cout<< *h3.shared_count <<std::endl;
    return 0;
}