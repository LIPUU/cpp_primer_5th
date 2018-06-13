#include <iostream>
#include <fstream>
#include "TextSearch.h"
#include "StrBlobPtr.h"
#include "queryResult.h"

using namespace std;

int main()
{
    ifstream ifs("text.txt");
    TextSearch_Init fuck(ifs);
    print(cout, fuck.TextQuery("fuck"));
    return 0;
}