#pragma once
#include <windows.h>
#include <stdio.h>

using namespace std;

void gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}


class ConsoleMover
{
private:
    HANDLE screen0, screen1;
    SMALL_RECT srctReadRect;
    SMALL_RECT srctWriteRect;
    CHAR_INFO chiBuffer[3600];
    COORD coordBufSize;
    COORD coordBufCoord;
    BOOL fSuccess;
    bool state = true;
    char symMas[35] = "                    1234567890^|$&";
    

    void AddFirstLine(CHAR_INFO* buf) {
        for (int i = 0; i < 10; i++)
        {
            int insIndex = rand() % 120;
            CHAR sym = symMas[rand() % 34];
            CHAR_INFO insChar;
            insChar.Attributes = buf[insIndex].Attributes;
            insChar.Char.UnicodeChar = sym;
            buf[insIndex] = insChar;
        }
    }

public:
    ConsoleMover()
    {
        screen0 = CreateConsoleScreenBuffer(
            GENERIC_READ |
            GENERIC_WRITE,
            0,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL);
        screen1 = CreateConsoleScreenBuffer(
            GENERIC_READ |
            GENERIC_WRITE,
            0,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL);
        if (screen0 == INVALID_HANDLE_VALUE ||
            screen1 == INVALID_HANDLE_VALUE)
        {
            printf("CreateConsoleScreenBuffer");
        }
    }

    void Move() {
        if (state)
            if (!SetConsoleActiveScreenBuffer(screen0))
                printf("SetConsoleActiveScreenBuffer");
            else;
        else
            if (!SetConsoleActiveScreenBuffer(screen1))
                printf("SetConsoleActiveScreenBuffer");


        srctReadRect.Top = 0;
        srctReadRect.Left = 0;
        srctReadRect.Bottom = 29;
        srctReadRect.Right = 119;



        coordBufSize.Y = 30;
        coordBufSize.X = 120;



        coordBufCoord.X = 0;
        coordBufCoord.Y = 0;


        if (state) {
            fSuccess = ReadConsoleOutput(
                screen0,
                chiBuffer,
                coordBufSize,
                coordBufCoord,
                &srctReadRect);

            if (!fSuccess)
                printf("ReadConsoleOutput");

            AddFirstLine(chiBuffer);

            srctWriteRect.Top = 1;
            srctWriteRect.Left = 0;
            srctWriteRect.Bottom = 40;
            srctWriteRect.Right = 119;



            fSuccess = WriteConsoleOutput(
                screen1,
                chiBuffer,
                coordBufSize,
                coordBufCoord,
                &srctWriteRect);
            if (!fSuccess)
                printf("WriteConsoleOutput");
            if (!SetConsoleActiveScreenBuffer(screen1))
                printf("SetConsoleActiveScreenBuffer");
        }
        else {
            fSuccess = ReadConsoleOutput(
                screen1,
                chiBuffer,
                coordBufSize,
                coordBufCoord,
                &srctReadRect);

            if (!fSuccess)
                printf("ReadConsoleOutput");



            srctWriteRect.Top = 1;
            srctWriteRect.Left = 0;
            srctWriteRect.Bottom = 40;
            srctWriteRect.Right = 119;



            fSuccess = WriteConsoleOutput(
                screen0,
                chiBuffer,
                coordBufSize,
                coordBufCoord,
                &srctWriteRect);
            if (!fSuccess)
                printf("WriteConsoleOutput");
            if (!SetConsoleActiveScreenBuffer(screen0))
                printf("SetConsoleActiveScreenBuffer");
        }

        state = !state;


        
    }

};


