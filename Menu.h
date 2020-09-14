//
// Created by Матвей on 12.09.2020.
//
#include "List.h"

#ifndef LAB1_MENU_H
#define LAB1_MENU_H

class Menu {
public:
    static void startMenu(List<> &list) {
        bool flag = true;
        int action = 0;
        int tmp, number, counter = 0;
        while (flag) {
            Console::cls();
            Menu::printActionsList();
            cin >> action;
            Console::print("\n\n---ACTION---\n\n");
            switch (action) {
                case 0:
                    flag = false;
                    break;
                case 1:
                    Console::print("Size of list: ");
                    Console::print(list.getSize());
                    break;
                case 2:
                    list.clear();
                    break;
                case 3:
                    if (list.isEmpty())
                        Console::print("List is empty!");
                    else
                        Console::print("List is NOT empty!");
                    break;
                case 4:
                    Console::print("Enter value: ");
                    cin >> tmp;
                    counter = 0;
                    if (list.contains(counter, tmp))
                        Console::print("List contains this value");
                    else
                        Console::print("List NOT contains this value");
                    break;
                case 5:
                    Console::print("Enter value: ");
                    cin >> tmp;
                    Console::println(list.getAt(counter, tmp));
                    break;
                case 6:
                    Console::print("Enter position: ");
                    cin >> tmp;
                    Console::print("Enter new value: ");
                    cin >> number;
                    list.setAt(counter, number, tmp);
                    break;
                case 7:
                    Console::print("Enter value: ");
                    cin >> tmp;
                    Console::print(list.indexOf(tmp));
                    break;
                case 8:
                    Console::print("Enter new value: ");
                    cin >> tmp;
                    list.push(counter, tmp);
                    break;
                case 9:
                    Console::print("Enter new value: ");
                    cin >> tmp;
                    Console::print("Enter position: ");
                    cin >> number;
                    counter = 0;
                    list.push(counter, tmp, number);
                    break;
                case 10:
                    Console::print("Enter value: ");
                    cin >> tmp;
                    counter = 0;
                    list.remove(counter, tmp);
                    break;
                case 11:
                    Console::print("Enter position: ");
                    cin >> tmp;
                    counter = 0;
                    list.pop(counter, tmp);
                    break;
                case 12:
                    Menu::iteratorMenu(list);
                    break;
                case 13:
                    Menu::riteratorMenu(list);
                    break;
                case 14:
                    Menu::iteratorMenu(list);
                    break;
                case 15:
                    Menu::riteratorMenu(list);
                    break;
                case 16:
                    Console::print("Counter = ");
                    Console::println(counter);
                    break;
                case 17:
                    list.print();
                    break;
                default:
                    Console::print("Incorrect value!");
                    break;
            }
            Console::print("\n\n---DONE---\n\n");

        }
    }

    static void printActionsList() {
        Console::println("---MENU---");
        Console::println("0) EXIT");
        Console::println("1) Check list size");
        Console::println("2) Clear list");
        Console::println("3) Is empty?");
        Console::println("4) Is contains value?");
        Console::println("5) Find value by index");
        Console::println("6) Change value by index");
        Console::println("7) Get index by value");
        Console::println("8) Push new value");
        Console::println("9) Push new value by index");
        Console::println("10) Delete node by value");
        Console::println("11) Delete node by index");
        Console::println("12) Get iterator");
        Console::println("13) Get reverse iterator");
        Console::println("14) Get empty iterator");
        Console::println("15) Get empty reverse iterator");
        Console::println("16) Print counter");
        Console::println("17) Print list");
    }

    static void iteratorMenu(List<> &list) {
        List<>::Iterator it = List<>::Iterator(&list);
        bool flag = true;
        int action = 0;
        while (flag) {
            Console::print("In list: ");
            Console::printlnBool(it.hasList());
            Console::print("Current value: ");
            try {
                Console::println(it.getData());
            }
            catch (const runtime_error &er) {
                Console::println(er.what());
            }
            Console::println("----------------------------------");
            list.print();
            Console::println("---------------MENU---------------");
            Console::println("0) EXIT");
            Console::println("1) Go to next");
            Console::println("2) Change value");
            Console::println("3) Drop list");
            Console::println("4) To head");
            cin >> action;
            switch (action) {
                case 0:
                    flag = false;
                    break;
                case 1:
                    it.next();
                    break;
                case 2:
                    Console::print("Enter value: ");
                    cin >> action;
                    it.setData();
                    break;
                case 3:
                    it.setList();
                    break;
                case 4:
                    it.toHead();
                default:
                    Console::print("Incorrect value");
                    break;
            }
            getchar();
        }

    }

    static void riteratorMenu(List<> &list) {
        List<>::rIterator it = List<>::rIterator(&list);
        bool flag = true;
        int action = 0;
        while (flag) {
            Console::print("In list: ");
            Console::printlnBool(it.hasList());
            Console::print("Current value: ");
            try {
                Console::println(it.getData());
            }
            catch (const runtime_error &er) {
                Console::println(er.what());
            }
            Console::println("----------------------------------");
            list.print();
            Console::println("---------------MENU---------------");
            Console::println("0) EXIT");
            Console::println("1) Go to next");
            Console::println("2) Change value");
            Console::println("3) Drop list");
            Console::println("4) To head");
            cin >> action;
            switch (action) {
                case 0:
                    flag = false;
                    break;
                case 1:
                    it.next();
                    break;
                case 2:
                    Console::print("Enter value: ");
                    cin >> action;
                    it.setData();
                    break;
                case 3:
                    it.setList();
                    break;
                case 4:
                    it.toHead();
                default:
                    Console::println("Incorrect value");
                    break;
            }
            getchar();
        }

    }
};

#endif //LAB1_MENU_H
