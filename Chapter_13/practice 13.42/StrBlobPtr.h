//
// Created by mustang on 18-6-13.
//

#ifndef INC_12_3_STRBLOBPTR_H
#define INC_12_3_STRBLOBPTR_H
#include <string>
#include <memory>
#include "algorithm"
#include "queryResult.h"
#include "StrVec.h"
class StrBlobPtr;

class StrBlob
{
    friend class StrBlobPtr;
    friend class QueryResult;
public:
    using size_type=string::size_type;

    StrBlob();

    StrBlob(std::initializer_list<std::string> x);

    StrBlobPtr begin();

    StrBlobPtr end();

    const StrBlobPtr begin() const;

    const StrBlobPtr end() const;


    size_type size() const
    {
        return data->size();
    }


    //add and delete element
    void push_back(const std::string &s)
    {
        data->push_back(s);
    }

public:
    void debugPrint()
    {
        for_each(data->begin(), data->end(), [](const std::string &fuck)
        { std::cout << fuck << std::endl; });
    }


private:
    std::shared_ptr<StrVec> data;

    void check(size_type l, const std::string &msg) const
    {
        using namespace std;
        if (l >= data->size())
        {
            throw out_of_range(msg);
        }
    }
};

//默认构造函数,初始化一个空的shared_ptr
inline StrBlob::StrBlob() : data(std::make_shared<StrVec>())
{};

//列表初始化一个由shared_ptr控制生命周期的vector<string>
inline StrBlob::StrBlob(std::initializer_list<std::string> x) :
        data(std::make_shared<StrVec>(x))
{};


/*------------------------------------------------------------------------------------------------*/
class StrBlobPtr
{
    friend bool eq(const StrBlobPtr &s1, const StrBlobPtr &s2);
public:
    StrBlobPtr() : curr(0)
    {}

    StrBlobPtr(StrBlob &strb, size_t t = 0) : wptr{strb.data}, curr(t)
    {}

    StrBlobPtr(const StrBlob &strb, size_t t = 0) : wptr{strb.data}, curr(t)
    {}

    std::string &redef() const;

    std::string&redef(unsigned i) const
    {
        auto ret{check(curr+i, "deRef-ing and dereference past end")};
        return (*ret)[curr+i];
    }



    //这两个都提供了越界检查
    StrBlobPtr &incurr(); //前缀递增
    StrBlobPtr &recurr(); //前缀递减

private:
    std::size_t curr; //curr的语义是指示当前指针指向vector的位置
    std::weak_ptr<StrVec> wptr;

    std::shared_ptr<StrVec> check(std::size_t i, const std::string &msg) const;
};


/*------------------------------------------------------------------------------------------------*/
inline StrBlobPtr StrBlob::begin() //c++中begin和end的语义
{
    auto ret{StrBlobPtr(*this)};
    return ret;
}

inline StrBlobPtr StrBlob::end()
{
    auto ret{StrBlobPtr(*this, data->size())};
    return ret;
}

inline const StrBlobPtr StrBlob::begin() const
{
    auto ret{StrBlobPtr(*this)};
    return ret;
}


inline const StrBlobPtr StrBlob::end() const
{
    auto ret{StrBlobPtr(*this, data->size())};
    return ret;
}

/*------------------------------------------------------------------------------------------------*/


inline std::shared_ptr<StrVec> StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    using namespace std;
    auto ret{wptr.lock()};
    if (!ret)
    {
        throw runtime_error("unbound StrBlob");
    }

    //check每次都把传递进来的i参数和vector实际的最新长度(vector可能进行了push或pop操作)进行比较
    //i形参被不同的函数调用时,实际进行了不同含义的检测
    if (i >= (*ret).size())
    {
        throw out_of_range(msg);
    }

    return ret;
}

inline std::string &StrBlobPtr::redef() const
{
    //解引用时,curr不能大于等于vector的长度,因为该下标标示的是vector的下一个位置
    auto ret{check(curr, "deRef-ing and dereference past end")};
    return (*ret)[curr];
}

inline StrBlobPtr &StrBlobPtr::incurr()
{
    //递增时,curr不能大于等于vector的长度,因为该下标标示的是end位置的语义,该位置既不能再递增也不能解引用
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

inline StrBlobPtr &StrBlobPtr::recurr()
{
    //如果curr已经为0,那么再递减就会产生-1这个非法下标,而check的第一个参数是size_t
    //size_t是无符号整型,-1转换成无符号整型会变得很大,一定不能通过check的检测
    --curr;
    check(curr, "index less than 0");
    return *this;
}

/*------------------------------------------------------------------------------------------------*/
inline bool eq(const StrBlobPtr &s1, const StrBlobPtr &s2)
{
    auto sh1{s1.wptr.lock()};
    auto sh2{s2.wptr.lock()};
    if (sh1 == sh2)
    {
        return (!sh1 || s1.curr == s2.curr);
    } else
    {
        return false;
    }
}

inline bool neq(const StrBlobPtr &s1, const StrBlobPtr &s2)
{
    return eq(s1, s2);
}
#endif //INC_12_3_STRBLOBPTR_H
