#include <conio.h>
#include "menus.h"
#include "game-io.h"

int Scelta_Menu(int * cursore)
{
    unsigned char scelta;
    int ritorno=-1;

    scelta = getch();
    switch (scelta)
    {
        case ARROW:
            scelta = getch();
            switch(scelta)
            {
                case UP_ARROW:
                    *cursore=*cursore-1;
                    while (*cursore < 0) *cursore = *cursore + MP_NCAMPI;
                    break;
                case DOWN_ARROW:
                    *cursore=*cursore+1;
                    while (*cursore >= MP_NCAMPI)
                    {
                        *cursore = *cursore - MP_NCAMPI;
                    }
                    break;
            }
            break;
        case ENTER:
            if (*cursore == MP_NCAMPI-1) ritorno = 0;
            else ritorno = *cursore+1;
            break;
        case 'n':
            ritorno = MP_VNUOVA;
            break;
        case 'N':
            ritorno = MP_VNUOVA;
            break;
        case 'c':
            ritorno = MP_VCARICA;
            break;
        case 'C':
            ritorno = MP_VCARICA;
            break;
        case 's':
            ritorno = MP_VSALVA;
            break;
        case 'S':
            ritorno = MP_VSALVA;
            break;
        case 'r':
            ritorno = MP_VRECORD;
            break;
        case 'R':
            ritorno = MP_VRECORD;
            break;
        case 'i':
            ritorno = MP_VIMP;
            break;
        case 'I':
            ritorno = MP_VIMP;
            break;
        case 'a':
            ritorno = MP_VAIUTO;
            break;
        case 'A':
            ritorno = MP_VAIUTO;
            break;
        case ESC:
            ritorno = 0;
            break;
    }
    return ritorno;
}

