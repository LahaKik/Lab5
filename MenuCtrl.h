#pragma once
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "ConsoleMover.h"

using namespace std;

class MenuCtrl
{
public:
    char variateSym[19] = "1234567890$%#@|&/\\";

    void StartMenu()
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
        bool IsExit = false;
        State state = startMenu;
        setlocale(LC_ALL, "");
        while (!IsExit)
        {
            system("cls");
            PrintMenu();
            int inpNum = 0;
            cin.clear();
            cin.sync();
            cin >> inpNum;

            try
            {
                state = static_cast<State>(inpNum);

            }
            catch (exception e)
            {
                state = startMenu;
            }
            switch (state)
            {
            case startMenu:
                break;

            case startAnimation:
                StartAnimation();
                break;

            case exit:
                IsExit = true;
                break;

            default:
                break;
            }
        }
    }
private:


    void PrintMenu()
    {
        cout << "Меню:" << endl
            <<"1 - Запустить анимацию" << endl << endl
            << "9 - Выход" << endl;
        cout << ("Действие: ");
    }

    void StartAnimation()
    {
        system("cls");
        ConsoleMover console = ConsoleMover();

        while (true)
        {
            cout << "j";
            console.Move();
            Sleep(20);
        }
    }


    enum State : int
    {
        startMenu,
        startAnimation,
        exit = 9
    };
};