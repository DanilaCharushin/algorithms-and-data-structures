//
// Created by Матвей on 12.09.2020.
//
#include "List.h"

#ifndef LAB1_MENU_H
#define LAB1_MENU_H

class Menu {
public:
    void startMenu(List<> &list) {
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
                    Menu().iteratorMenu(list);
                    break;
                case 13:
                    Menu().riteratorMenu(list);
                    break;
                case 14:
                    Menu().iteratorMenu(list);
                    break;
                case 15:
                    Menu().riteratorMenu(list);
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
            Console().print("---ACTION DONE!---\n\n");

        }
    }

    void printActionsList() {
        Console().print("---MENU---");
        Console().print("0) EXIT");
        Console().print("1) Check list size");
        Console().print("2) Clear list");
        Console().print("3) Is empty?");
        Console().print("4) Is contains value?");
        Console().print("5) Find value by index");
        Console().print("6) Change value by index");
        Console().print("7) Get index by value");
        Console().print("8) Push new value");
        Console().print("9) Push new value by index");
        Console().print("10) Delete node by value");
        Console().print("11) Delete node by index");
        Console().print("12) Get iterator");
        Console().print("13) Get reverse iterator");
        Console().print("14) Get empty iterator");
        Console().print("15) Get empty reverse iterator");
        Console().print("16) Запрос числа элементов списка, просмотренных операциями"
                        " опроса наличия заданного значения, включения нового значения в"
                        " позицию с заданным номером, удаления значения из позиции с заданным номером");
        Console().print("17) Print list");
    }

    void iteratorMenu(List<> &list) {
        List<>::Iterator it = List<>::Iterator(&list);
        bool flag = 1;
        int action = 0;
        while (flag) {
            Console().print("In list: ", 0);
            Console().printbool(it.hasList());
            Console().print("Current value: ", 0);
            try {
                Console().print(it.getData());
            }
            catch (runtime_error er) {
                Console().print(er.what());
            }
            Console().print("----------------------------------");
            list.print();
            Console().print("---------------MENU---------------");
            Console().print("0) EXIT");
            Console().print("1) Go to next");
            Console().print("2) Change value");
            Console().print("3) Drop list");
            Console().print("4) To head");
            cin >> action;
            switch (action) {
                case 0:
                    flag = false;
                    break;
                case 1:
                    it.next();
                    break;
                case 2:
                    Console().print("Enter value: ", 0);
                    cin >> action;
                    it.setData();
                    break;
                case 3:
                    it.setList();
                    break;
                case 4:
                    it.toHead();
                default:
                    Console().print("Incorrect value");
                    break;
            }
            //_getch();
        }

    }

    void riteratorMenu(List<> &list) {
        List<>::rIterator it = List<>::rIterator(&list);
        bool flag = 1;
        int action = 0;
        while (flag) {
            Console().print("In list: ", 0);
            Console().printbool(it.hasList());
            Console().print("Current value: ", 0);
            try {
                Console().print(it.getData());
            }
            catch (runtime_error er) {
                Console().print(er.what());
            }
            Console().print("----------------------------------");
            list.print();
            Console().print("---------------MENU---------------");
            Console().print("0) EXIT");
            Console().print("1) Go to next");
            Console().print("2) Change value");
            Console().print("3) Drop list");
            Console().print("4) To head");
            cin >> action;
            switch (action) {
                case 0:
                    flag = false;
                    break;
                case 1:
                    it.next();
                    break;
                case 2:
                    Console().print("Enter value: ", 0);
                    cin >> action;
                    it.setData();
                    break;
                case 3:
                    it.setList();
                    break;
                case 4:
                    it.toHead();
                default:
                    Console().print("Incorrect value");
                    break;
            }
            //_getch();
        }

    }
};

#endif //LAB1_MENU_H
