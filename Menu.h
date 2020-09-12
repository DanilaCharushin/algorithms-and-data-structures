//
// Created by Матвей on 12.09.2020.
//
#include "List.h"

#ifndef LAB1_MENU_H
#define LAB1_MENU_H

class Menu {
public:
    void startMenu() {
        printActionsList();
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
                        " позицию с заданным номером, удаления значения из позиции с заданным номером(");
        Console().print("17) Print list");
    }

    void iteratorMenu(List<>::Iterator it) {
        bool flag = 1;
        int action = 0;
        while (flag) {
            Console().print("In list: ", 0);
            Console().printb(it.hasList());
            Console().print("Current value: ", 0);
            try {
                Console().print(it.getData());
            }
            catch (runtime_error er) {
                Console().print(er.what());
            }
            Console().print("Next node: ", 0);
            Console().printb(it.hasNext());
            Console().print("----------------------------------");
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
    void iteratorMenu(List<>::rIterator it) {
        bool flag = 1;
        int action = 0;
        while (flag) {
            Console().print("In list: ", 0);
            Console().printb(it.hasList());
            Console().print("Current value: ", 0);
            try {
                Console().print(it.getData());
            }
            catch (runtime_error er) {
                Console().print(er.what());
            }
            Console().print("Next node: ", 0);
            Console().printb(it.hasNext());
            Console().print("----------------------------------");
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
