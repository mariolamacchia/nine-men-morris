#include <windows.h>

void Riproduci_Suono(int suono)
{
    switch (suono)
    {
        case 0:
            Beep(700,100);
            Beep(520,100);
            break;
        case 1:
            Beep(520,100);
            Beep(700,100);
            break;
        case 2:
            Beep(520,100);
            break;
        case 3:
            Beep(700,100);
            Beep(700,100);
            break;
        case 4:
            Beep(700,100);
            Beep(700,100);
            Beep(700,100);
            break;
        case 5:
            Beep(520,70);
            Beep(700,70);
            Beep(520,70);
            break;
        case 6:
            Beep(660,100);
            Beep(700,100);
            break;
        case 7:
            Beep(700,100);
            Beep(660,100);
            break;
        case 8:
            Beep(520,30);
            Beep(580,30);
            Beep(660,30);
            Beep(700,30);
            Beep(780,30);
            break;
        case 9:
            Beep(780,30);
            Beep(700,30);
            Beep(660,30);
            Beep(580,30);
            Beep(520,30);
            break;
        case 10:
            Beep(660,200);
            Beep(520,200);
            Beep(390,200);
            Beep(660,400);
            break;
        case 11:
            Beep(660,100);
            Beep(620,100);
            Beep(660,100);
            Beep(780,100);
            Sleep(200);
            Beep(880,100);
            Beep(780,100);
            Sleep(100);
            Beep(660,400);
            break;
        case 12:
            Beep(520,100);
            Beep(520,100);
            Beep(520,100);
            Sleep(200);
            Beep(1040,200);
            Beep(880,300);
            break;
        case 13:
            Beep(520,300);
            Beep(495,300);
            Beep(470,300);
            Beep(440,600);
            break;
        case 14:
            Beep(520,100);
            Beep(580,100);
            Beep(660,100);
            Beep(780,200);
            Sleep(200);
            Beep(660,100);
            Beep(780,400);
            break;
        case 15:
            Beep(700,100);
            Sleep(100);
            Beep(520,100);
            Beep(520,100);
            Beep(580,100);
            Sleep(200);
            Beep(520,200);
            Sleep(200);
            Beep(660,200);
            Beep(700,200);
            break;
    }
}
