#include <iostream>
#include "List.h"
using namespace std;

#define TEST

#ifdef TEST
int main() {
    cout << "############ START TEST ############" << endl;

    List<double> list(5);
    List<double> list2 = list;

    list.print();
    cout << list.pop(-1) << endl;
    list.push(-2,-2);
    list.print();


    list2.print();



    cout << "############# END TEST #############" << endl;

    return 0;
}
#else
int main() {
    cout << "############ START ############" << endl;
    cout << "Hello, World!" << endl;
    cout << "############# END #############" << endl;
    return 0;
}
#endif
