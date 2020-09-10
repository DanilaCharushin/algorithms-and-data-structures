#include <iostream>
#include <ctime>
#include "List.h"
using namespace std;

#define TEST

#ifdef TEST
int main() {
    srand(time(nullptr));

    cout << "############ START TEST ############" << endl;

    List<int> list(5);

    list.print();

    cout << list.contains(list[0]->getData()) << endl;

    list.remove(-59);

    list.print();

    for (auto i = list.begin(); i.inList(); i++) {
        cout << (*i)->getData() << endl;
    }

    cout << "------------" << endl;

    for (auto i = list.rbegin(); i.inList(); i++) {
        cout << (*i)->getData() << endl;
    }

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
