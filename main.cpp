#include <iostream>
#include <ctime>
#include "List.h"
#include "Console.h"
#include "Menu.h"

using namespace std;

//#define TEST

#ifdef TEST
int main() {
    srand(time(nullptr));

    cout << "############ START TEST ############" << endl;

    List<double> list(5);
    list.print();
    cout << list.getAt(-2) << endl;
    list.setAt(99.9, -2);
    cout << list.getAt(-2) << endl;
    list.print();

    cout << "############# END TEST #############" << endl;

    return 0;
}
#else

int main() {
    srand(time(nullptr));

    List<int> list(10);
    Menu::startMenu(list);
    return 0;
}

#endif
