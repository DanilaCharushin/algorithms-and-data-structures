#include <locale.h>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include "Windows.h"
#include "List.h"
#include "Console.h"
#include "Menu.h"


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
        switch (action) {
            case 0:
                flag = false;
                break;
            case 1:
                Console().print("Размер массива: ");
                Console().print(list.getSize());
                break;
            case 2:
                list.clear();
                break;
            case 3:
                if (list.isEmpty())
                    Console().print("Список пуст!");
                else
                    Console().print("Список НЕ пуст!");
                break;
            case 4:
                Console().print("Введите искомое значение: ");
                cin >> tmp;
                if (list.contains(tmp))
                    Console().print("Список содержит это значение");
                else
                    Console().print("Список содержит это значение");
                break;
            case 5:
                Console().print("Введите искомое значение: ");
                cin >> tmp;
                Console().print(list.getAt(tmp));
                break;
            case 6:
                break;
            case 7:
                Console().print("Введите искомое значение: ");
                cin >> tmp;
                Console().print(list.indexOf(tmp));
                break;
            case 8:
                Console().print("Введите новое значение: ");
                cin >> tmp;
                list.push(tmp);
                break;
            case 9:
                Console().print("Введите новое значение: ");
                cin >> tmp;
                Console().print("Введите желаемую позицию: ");
                cin >> number;
                list.push(tmp, number);
                break;
            case 10:
                Console().print("Введите значение: ");
                cin >> tmp;
                list.remove(tmp);
                break;
            case 11:
                Console().print("Введите gjpbwb.: ");
                cin >> tmp;
                list.pop(tmp);
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
            case 15:
                break;
            case 16:
                break;
            case 17:
                list.print();
                break;
            default:
                Console().print("Введено некорректное значение");
                break;
        }
        Console().print("\n");
        Console().print("---ACTION DONE!---\n");

    }
    return 0;
}

#endif
