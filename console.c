#include <stdio.h>
#include <windows.h>
#include "console.h"

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Cambia_Colore (int colore, int sfondo)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 16*sfondo+colore);
}

void Cambia_Sfondo(int colore, int colore_sfondo)
{
    int i;
    //Cambia lo sfondo
    gotoxy(0,0);
    Cambia_Colore(colore,colore_sfondo);
    for (i=0; i<BUFFER_X*BUFFER_Y; i++) putchar(BACK_CHAR);
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Cursore_Visibile (booleano visibile)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visibile;
    SetConsoleCursorInfo(consoleHandle, &info);
}
