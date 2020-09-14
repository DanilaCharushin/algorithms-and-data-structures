//
// Created by Матвей on 12.09.2020.
//

#ifndef LAB1_CONSOLE_H
#define LAB1_CONSOLE_H

//#define COLOR_ON

#include <iostream>
#include <cstring>

using namespace std;

class Console {
public:
    Console() = default;

    enum COLORS {
        DEFAULT, RED, GREEN, BLUE
    };

    static void SET_COLOR(COLORS color = DEFAULT) {
        switch (color) {
            case RED:
                system("color 04");
                break;
            case DEFAULT:
                system("color 07");
                break;
            case GREEN:
                system("color 02");
                break;
            case BLUE:
                system("color 01");
                break;
            default:
                system("color 07");
                break;
        }
    }


    static void print(int str, COLORS color = DEFAULT) {
#ifdef COLOR_ON
        Console::SET_COLOR(color);
#endif
        cout << str;
#ifdef COLOR_ON
        Console::SET_COLOR();
#endif
    }

    static void println(int str, COLORS color = DEFAULT) {
#ifdef COLOR_ON
        Console::SET_COLOR(color);
#endif
        cout << str << endl;
#ifdef COLOR_ON
        Console::SET_COLOR();
#endif
    }

    static void print(double str, COLORS color = DEFAULT) {
#ifdef COLOR_ON
        Console::SET_COLOR(color);
#endif
        cout << str;
#ifdef COLOR_ON
        Console::SET_COLOR();
#endif
    }

    static void println(double str, COLORS color = DEFAULT) {
#ifdef COLOR_ON
        Console::SET_COLOR(color);
#endif
        cout << str << endl;
#ifdef COLOR_ON
        Console::SET_COLOR();
#endif
    }

    static void printBool(bool str, COLORS color = DEFAULT) {
#ifdef COLOR_ON
        Console::SET_COLOR(color);
#endif
        if (str)
            cout << "TRUE";
        else
            cout << "FALSE";
#ifdef COLOR_ON
        Console::SET_COLOR();
#endif
    }

    static void printlnBool(bool str, COLORS color = DEFAULT) {
#ifdef COLOR_ON
        Console::SET_COLOR(color);
#endif
        if (str)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;
#ifdef COLOR_ON
        Console::SET_COLOR();
#endif
    }

    static void print(const string str, COLORS color = DEFAULT) {
#ifdef COLOR_ON
        Console::SET_COLOR(color);
#endif
        cout << str;
#ifdef COLOR_ON
        Console::SET_COLOR();
#endif
    }

    static void println(const string str, COLORS color = DEFAULT) {
#ifdef COLOR_ON
        Console::SET_COLOR(color);
#endif
        cout << str << endl;
#ifdef COLOR_ON
        Console::SET_COLOR();
#endif
    }

    static void cls() {
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
    }
};

#endif //LAB1_CONSOLE_H
