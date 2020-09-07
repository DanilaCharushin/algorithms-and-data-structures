#include <iostream>
#include "List.h"
using namespace std;

#define TEST

#ifdef TEST
int main() {
    cout << "############ START TEST ############" << endl;

    List<double> list(5);

    list.print();

    list.print();

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
