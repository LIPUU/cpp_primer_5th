//
// Created by mustang on 18-6-13.
//

#ifndef INC_12_3_QUERYRESULT_H
#define INC_12_3_QUERYRESULT_H

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include "StrBlobPtr.h"

class QueryResult
{
    friend std::ostream &print(std::ostream &, const QueryResult &);

public:
    QueryResult(std::string s,
                std::shared_ptr<std::pair<std::string::size_type, std::set<int>>> l,
                StrBlob f) :
            sought_word(s), shPtr_lines(l), str_file(f)
    {}

    std::set<int>::const_iterator begin()
    {
        return shPtr_lines->second.cbegin();
    }

    std::set<int>::const_iterator end()
    {
        return shPtr_lines->second.cend();
    }

    std::shared_ptr<std::vector<std::string>> get_file()
    {
        return str_file.data;
    }

private:
    std::string sought_word;

    std::shared_ptr<std::pair<
            std::string::size_type, std::set<int>>
    > shPtr_lines;

    StrBlob str_file;

};

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    auto &shitPair{qr.shPtr_lines};
    std::cout << qr.sought_word << "出现了" << shitPair->first << "次" << std::endl;
    for (const auto &bitch:shitPair->second)
    {
        std::cout << "第" << bitch << "行:" << qr.str_file.begin().redef(bitch-1) << std::endl;
    }
    return os;
}

#endif //INC_12_3_QUERYRESULT_H
