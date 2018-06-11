//
// Created by mustang on 18-6-7.
//

#ifndef CHAPTER_13_HASPTR_VAL_VERSION_H
#define CHAPTER_13_HASPTR_VAL_VERSION_H



class HasPtr_val_version
{
    friend int main();

    friend void swap(HasPtr_val_version &, HasPtr_val_version &);
private:
    string *ps;
    int i;
public:
    //构造函数
    explicit HasPtr_val_version(const string &s = string()) : ps(new string(s)), i(0)
    {}

    //拷贝构造函数
    HasPtr_val_version(const HasPtr_val_version &ori) : ps(new string(*ori.ps)), i(ori.i)
    {}



    //拷贝赋值运算符 1
    HasPtr_val_version &operator=(const HasPtr_val_version &ori)
    {
        if (this == &ori)
        {
            //自赋值优化
            return *this;
        }

        string *tmp{new string(*ori.ps)};
        delete ps;
        ps=tmp;
        i=ori.i;
        return *this;
    }

    //拷贝赋值运算符 2
    HasPtr_val_version&operator=(const string& s)
    {
        *ps = s;
        return *this;
    }

    //解引用运算符
    const string &operator*()
    {
        return *ps;
    }

    //<运算符
    bool operator<(const HasPtr_val_version &ori)
    {
        //return *this->ps < *ori.ps;
        return stoi(*this->ps) < stoi(*ori.ps);
    }



    //析构
    ~HasPtr_val_version()
    {
        delete ps;
    }

};

//swap
void swap(HasPtr_val_version &lhs,HasPtr_val_version &rhs)
{
    using std::swap;
    std::cout<< "交换: "<<*lhs.ps<<" AND "<<*rhs.ps <<std::endl;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

#endif //CHAPTER_13_HASPTR_VAL_VERSION_H
