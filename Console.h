//
// Created by Матвей on 12.09.2020.
//

#ifndef LAB1_CONSOLE_H
#define LAB1_CONSOLE_H

#include <iostream>
#include <cstring>
#include <conio.h>
#include <stdio.h>

using namespace std;

class Console {
private:
public:
    Console() {
    };

    enum COLORS {
        DEFAULT, RED, GREEN, BLUE
    };

    /*static void print(char *str, COLORS color = DEFAULT) {
        switch (color) {
            case RED:
                system("color 04");
        }
        cout << str;
        system("color 07");
    }*/

    static void print(int str, COLORS color = DEFAULT) {
        switch (color) {
            case RED:
                system("color 04");
        }
        cout << str;
        system("color 07");
    }

    static void print(double str, COLORS color = DEFAULT) {
        switch (color) {
            case RED:
                system("color 04");
        }
        cout << str;
        system("color 07");
    }

    static void print(const string str, COLORS color = DEFAULT) {
        switch (color) {
            case RED:
                system("color 04");
        }
        cout << str;
        system("color 07");
    }

    static void cls(){
        system("cls");
    }
};

#endif //LAB1_CONSOLE_H
