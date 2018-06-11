#include <iostream>
#include "Folder.h"
using namespace std;

int main()
{
    Message m1("m1");
    Message m2("m2");
    Message m3("m3");
    Folder f1;
    Folder fuck;
    m1.save(f1);
    m1.save(fuck);
    m2.save(f1);
    m3.save(f1);
    Message m4("m4");
    Folder f2;
    m4.save(f2);

// - - - - - - - - - - - - - - //

    std::cout<<"f1: " ;
    f1.print(cout)<<endl ;

    std::cout<<"f2: " ;
    f2.print(cout)<<endl ;

    m1.print(cout)<<endl;
    m2.print(cout)<<endl;


// - - - - - - - - - - - - - -//

    swap(m1, m2);
    std::cout<<"f1: " ;
    f1.print(cout)<<endl ;

    std::cout<<"f2: " ;
    f2.print(cout)<<endl ;

    m1.print(cout)<<endl;
    m2.print(cout)<<endl;


    return 0;
}