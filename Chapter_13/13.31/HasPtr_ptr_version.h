//
// Created by mustang on 18-6-7.
//

#ifndef CHAPTER_13_HASPTR_PTR_VERSION_H
#define CHAPTER_13_HASPTR_PTR_VERSION_H

//这是不好的,这里使用只是为了方便
using namespace std;

class HasPtr_ptr_version
{
    friend int main();
private:
    string *ps;
    int i;
    unsigned *shared_count;
public:

    //构造函数
    explicit HasPtr_ptr_version(const string &s = string()) : ps(new std::string(s)), i(0), shared_count(new unsigned(1)) { }

    // 拷贝构造函数
    HasPtr_ptr_version(const HasPtr_ptr_version& ori):ps(ori.ps),i(ori.i),shared_count{ori.shared_count}
    {
        ++*shared_count;
    }

    // 拷贝赋值运算符
    HasPtr_ptr_version&operator=(const HasPtr_ptr_version& ori)
    {
        if(--*shared_count==0)
        {
            this->.~HasPtr_ptr_version();
        }
        shared_count=ori.shared_count;
        ++*shared_count;
        ps=ori.ps;
        i=ori.i;
        return *this;
    }

    //拷贝赋值运算符
    HasPtr_ptr_version&operator=(const string& ori)
    {
        if(--*shared_count==0)
        {
            this->~HasPtr_ptr_version();
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
    ~HasPtr_ptr_version()
    {
        if(--*shared_count==0)
        {
            delete ps;
            delete shared_count;
        }
    }

};

#endif //CHAPTER_13_HASPTR_PTR_VERSION_H
