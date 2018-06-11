
#include <iostream>
#include <vector>
#include <algorithm>
#include "HasPtr_ptr_version.h"
#include "HasPtr_val_version.h"
using namespace std;

int main()
{
    HasPtr_ptr_version h1("abc");
    std::cout<< *h1.shared_count <<std::endl;
    HasPtr_ptr_version h2(h1);
    std::cout<< *h1.shared_count <<std::endl;
    std::cout<< *h2.shared_count <<std::endl;
    HasPtr_ptr_version h3("abc");
    h2 = h3;
    std::cout<< *h3.shared_count <<std::endl;
    h2="abc";
    std::cout<< *h3.shared_count <<std::endl;

    HasPtr_val_version k1;
    k1 = "fuck";
    HasPtr_val_version k2("shit");
    k1=k2;
    k2=k2;
    HasPtr_val_version k3(k2);
    k3 = "shit";
    std::cout<< *k1.ps <<std::endl;
    std::cout<< *k2.ps <<std::endl;
    std::cout<< *k3.ps <<std::endl;

    std::cout<< "=-=-=-=-=-=-= 昏 割 线 =-=-=-=-=-=-=" <<std::endl;

    HasPtr_val_version t1("fuck");
    HasPtr_val_version t2("shit");
    swap(t1, t2);
    std::cout<< *t1.ps <<std::endl;
    std::cout<< *t2.ps <<std::endl;

    std::cout<< "=-=-=-=-=-=-= 昏 割 线 =-=-=-=-=-=-=" <<std::endl;

    vector<HasPtr_val_version> v;
    v.emplace_back(HasPtr_val_version("14"));
    v.emplace_back(HasPtr_val_version("13"));
    v.emplace_back(HasPtr_val_version("12"));
    v.emplace_back(HasPtr_val_version("11"));
    v.emplace_back(HasPtr_val_version("10"));
    v.emplace_back(HasPtr_val_version("9"));
    v.emplace_back(HasPtr_val_version("8"));
    v.emplace_back(HasPtr_val_version("7"));
    v.emplace_back(HasPtr_val_version("6"));
    v.emplace_back(HasPtr_val_version("1"));
    v.emplace_back(HasPtr_val_version("2"));
    v.emplace_back(HasPtr_val_version("3"));
    v.emplace_back(HasPtr_val_version("4"));
    v.emplace_back(HasPtr_val_version("5"));
    v.emplace_back(HasPtr_val_version("99"));
    v.emplace_back(HasPtr_val_version("88"));
    v.emplace_back(HasPtr_val_version("66"));
    sort(v.begin(), v.end());
    for (const auto &it:v)
    {
        std::cout<< *it.ps <<std::endl;
    }

    return 0;
}