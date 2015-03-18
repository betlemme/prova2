#include <iostream>

using namespace std;

main()
{
    int a = 4;
    int b = 77;

    int *p = &a;

    cout << "a: " << a << endl;
    cout << "&a: " << &a << endl;
    cout << "p:  " << p << endl;
    cout << "&p: " << &p << endl;
    cout << "*p: " << *p << endl;

    return 0;
}
