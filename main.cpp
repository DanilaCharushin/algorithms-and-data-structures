#include <locale.h>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include "Windows.h"
#include "List.h"
#include "Console.h"
#include "Menu.h"
//TODO: replace all menu actions at class MENU

using namespace std;

#define TST

#ifdef TEST
int main() {
    srand(time(nullptr));

    cout << "############ START TEST ############" << endl;

    List<int> list(5);

    list.print();

    cout << list.contains(list[0]->getData()) << endl;

    list.remove(-59);

    Console().print("str\n", Console().RED);

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


    setlocale(LC_ALL, "Russian");
    cout << "############ START ############" << endl;
    List<int> list(5);
    bool flag = true;
    int action = 0;
    int tmp, number;
    while (flag) {
        Console().cls();
        Menu().printActionsList();
        cin >> action;
        Console().print("\n\n---ACTION!---");
        switch (action) {
            case 0:
                flag = false;
                break;
            case 1:
                Console().print("Size of list: ", 0);
                Console().print(list.getSize());
                break;
            case 2:
                list.clear();
                break;
            case 3:
                if (list.isEmpty())
                    Console().print("List is empty!", 0);
                else
                    Console().print("List is NOT empty!", 0);
                break;
            case 4:
                Console().print("Enter value: ", 0);
                cin >> tmp;
                if (list.contains(tmp))
                    Console().print("List contains this value", 0);
                else
                    Console().print("List NOT contains this value", 0);
                break;
            case 5:
                Console().print("Enter value: ", 0);
                cin >> tmp;
                Console().print(list.getAt(tmp));
                break;
            case 6:
                Console().print("Enter position: ", 0);
                cin >> tmp;
                Console().print("Enter new value: ", 0);
                cin >> number;
                list.setAt(number, tmp);
                break;
            case 7:
                Console().print("Enter value: ", 0);
                cin >> tmp;
                Console().print(list.indexOf(tmp));
                break;
            case 8:
                Console().print("Enter new value: ", 0);
                cin >> tmp;
                list.push(tmp);
                break;
            case 9:
                Console().print("Enter new value: ", 0);
                cin >> tmp;
                Console().print("Enter position: ", 0);
                cin >> number;
                list.push(tmp, number);
                break;
            case 10:
                Console().print("Enter value: ", 0);
                cin >> tmp;
                list.remove(tmp);
                break;
            case 11:
                Console().print("Enter position: ", 0);
                cin >> tmp;
                list.pop(tmp);
                break;
            case 12:
                Menu().iteratorMenu(List<>::Iterator(&list));
                break;
            case 13:
                Menu().iteratorMenu(List<>::rIterator(&list));
                break;
            case 14:
                Menu().iteratorMenu(List<>::Iterator());
                break;
            case 15:
                Menu().iteratorMenu(List<>::rIterator());
                break;
            case 16:
                break;
            case 17:
                list.print();
                break;
            default:
                Console().print("Incorrect value!");
                break;
        }
        Console().print("---ACTION DONE!---");
        _getch();

    }
    return 0;
}

#endif
