//
// Created by mustang on 18-6-13.
//

#ifndef INC_12_3_TEXTSEARCH_H
#define INC_12_3_TEXTSEARCH_H
#include <string>
#include <vector>
#include <sstream>
#include "istream"
#include "iterator"
#include "map"
#include "fstream"
#include "set"
#include "memory"
#include "queryResult.h"
#include "StrBlobPtr.h"

class TextSearch_Init
{

public:
    explicit TextSearch_Init(std::ifstream &ifs);

    QueryResult TextQuery(const std::string &) const;

private:
    std::map<std::string,
            std::shared_ptr<std::pair
                    <std::string::size_type, std::set<int>>>> words_line;
    StrBlob line_string;
};


TextSearch_Init::TextSearch_Init(std::ifstream &ifs)
{
    using namespace std;
    unsigned line_number{1};
    if (!ifs)
    {
        throw runtime_error("file opening failed");
    }

    std::string line;
    while (getline(ifs, line))
    {
        istringstream istr(line);
        istream_iterator<string> isiter(istr), eof;
        while (isiter != eof)
        {
            std::string word{*isiter++};

            auto &words_line_Pair{words_line[word]};
            if (!words_line_Pair)
            {
                words_line_Pair.reset(new pair<string::size_type, set<int>>);
            }
            if (words_line_Pair->second.find(line_number) == words_line_Pair->second.end())
            {
                words_line_Pair->second.emplace(line_number);
            }
            ++words_line_Pair->first;
        }
        line_string.push_back(line);
        ++line_number;
    }

}

QueryResult TextSearch_Init::TextQuery(const std::string &word) const
{
    using namespace std;
    static shared_ptr<pair<string::size_type, set<int>>> nodata(new pair<string::size_type, set<int>>);
    auto loc{words_line.find(word)};
    if (loc == words_line.end())
    {
        return QueryResult(word, nodata, line_string);
    } else
    {
        return QueryResult(word, loc->second, line_string);
    }
}
#endif //INC_12_3_TEXTSEARCH_H
