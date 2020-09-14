//
// Created by Матвей on 12.09.2020.
//
#include "List.h"

#ifndef LAB1_MENU_H
#define LAB1_MENU_H

class Menu {
public:
    static void startMenu(List<> &list) {
        List<>::Iterator it = list.end();
        List<>::rIterator rit = list.rend();
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
                    Console::printlnBool(list.isEmpty());
                    break;
                case 4:
                    Console::print("Enter value: ");
                    cin >> tmp;
                    counter = 0;
                    try {
                        Console::printlnBool(list.contains(counter, tmp));
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 5:
                    Console::print("Enter index: ");
                    cin >> tmp;
                    try {
                        Console::println(list.getAt(counter, tmp));
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 6:
                    Console::print("Enter position: ");
                    cin >> tmp;
                    Console::print("Enter new value: ");
                    cin >> number;
                    try {
                        list.setAt(counter, number, tmp);
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 7:
                    Console::print("Enter value: ");
                    cin >> tmp;
                    try {
                        Console::print(list.indexOf(tmp));
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 8:
                    Console::print("Enter new value: ");
                    cin >> tmp;
                    list.insert(counter, tmp);
                    break;
                case 9:
                    Console::print("Enter new value: ");
                    cin >> tmp;
                    Console::print("Enter position: ");
                    cin >> number;
                    counter = 0;
                    Console::printlnBool(list.insertAt(counter, tmp, number));
                    break;
                case 10:
                    Console::print("Enter value: ");
                    cin >> tmp;
                    counter = 0;
                    try {
                        Console::printlnBool(list.remove(counter, tmp));
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 11:
                    Console::print("Enter position: ");
                    cin >> tmp;
                    counter = 0;
                    try {
                        Console::printlnBool(list.removeAt(counter, tmp));
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 12:
                    it = list.begin();
                    Menu::iteratorMenu(list, it);
                    break;
                case 13:
                    rit = list.rbegin();
                    Menu::riteratorMenu(list, rit);
                    break;
                case 14:
                    it = list.end();
                    Menu::iteratorMenu(list, it);
                    break;
                case 15:
                    rit = list.rend();
                    Menu::riteratorMenu(list, rit);
                    break;
                case 16:
                    Console::print("Counter = ");
                    Console::println(counter);
                    break;
                case 17:
                    list.print();
                    break;
                case 18:
                    Console::printlnBool((*it) == (*rit));
                    break;
                case 19:
                    Console::printlnBool(it == list.end());
                    break;
                case 20:
                    Console::printlnBool(rit == list.rend());
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
        Console::println("8) Insert new value");
        Console::println("9) Insert new value by index");
        Console::println("10) Remove node by value");
        Console::println("11) Remove node by index");
        Console::println("12) Get iterator");
        Console::println("13) Get reverse iterator");
        Console::println("14) Get empty iterator");
        Console::println("15) Get empty reverse iterator");
        Console::println("16) Print counter");
        Console::println("17) Print list");
        Console::println("18) Iterator == rIterator");
        Console::println("19) Iterator == end()");
        Console::println("20) rIterator == rend()");
    }

    static void iteratorMenu(List<> &list, List<>::Iterator it) {
        bool flag = true;
        int action = 0;
        while (flag) {
            Console::print("Has list: ");
            Console::printlnBool(it.hasList());
            Console::print("Has node: ");
            Console::printlnBool(it.hasNode());
            Console::print("Current value: ");
            try {
                Console::println(it.getData());
            } catch (const exception &ex) {
                Console::println("EXCEPTION");
            }
            Console::println("----------------------------------");
            list.print();
            Console::println("---------------MENU---------------");
            Console::println("0) EXIT");
            Console::println("1) Go to next");
            Console::println("2) Go to prev");
            Console::println("3) Get value");
            Console::println("4) Set value");
            Console::println("5) Drop list");
            Console::println("6) To head");
            Console::println("7) To tail");
            cin >> action;
            switch (action) {
                case 0:
                    flag = false;
                    break;
                case 1:
                    try {
                        it.next();
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 2:
                    try {
                        it.prev();
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 3:
                    try {
                        Console::println(it.getData());
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 4:
                    Console::print("Enter value: ");
                    cin >> action;
                    try {
                        it.setData(action);
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                        Console::println(ex.what());
                    }
                case 5:
                    it.setList();
                    break;
                case 6:
                    try {
                        it.toHead();
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 7:
                    try {
                        it.toTail();
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                default:
                    Console::print("Incorrect value");
                    break;
            }
            getchar();
        }

    }

    static void riteratorMenu(List<> &list, List<>::rIterator it) {
        bool flag = true;
        int action = 0;
        while (flag) {
            Console::print("Has list: ");
            Console::printlnBool(it.hasList());
            Console::print("Has node: ");
            Console::printlnBool(it.hasNode());
            Console::print("Current value: ");
            try {
                Console::println(it.getData());
            } catch (const exception &ex) {
                Console::println("EXCEPTION");
            }
            Console::println("----------------------------------");
            list.print();
            Console::println("---------------MENU---------------");
            Console::println("0) EXIT");
            Console::println("1) Go to next");
            Console::println("2) Go to prev");
            Console::println("3) Get value");
            Console::println("4) Set value");
            Console::println("5) Drop list");
            Console::println("6) To head");
            Console::println("7) To tail");
            cin >> action;
            switch (action) {
                case 0:
                    flag = false;
                    break;
                case 1:
                    try {
                        it.next();
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 2:
                    try {
                        it.prev();
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 3:
                    try {
                        Console::println(it.getData());
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 4:
                    Console::print("Enter value: ");
                    cin >> action;
                    try {
                        it.setData(action);
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                case 5:
                    it.setList();
                    break;
                case 6:
                    try {
                        it.toHead();
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                case 7:
                    try {
                        it.toTail();
                    } catch (const exception &ex) {
                        Console::println("EXCEPTION");
                    }
                    break;
                default:
                    Console::print("Incorrect value");
                    break;
            }
            getchar();
        }

    }
};

#endif //LAB1_MENU_H
