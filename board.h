#ifndef _BOARD_H
#define _BOARD_H

#include "basetypes.h"

typedef int casella;
typedef struct
{
    int grandezza;
    casella * caselle;
} campo;

typedef unsigned char buffer_campo;

typedef struct
{
    int x;
    int y;
} casella_selezionata;

int Lato_Campo (int grandezza);
int Area_Campo (int grandezza);
int Lato_Buffer_Campo (int grandezza, int spazio);
int Perimetro_Quadrato(int grandezza);

casella_selezionata Casella_Adiacente (casella_selezionata Casella,
                                       direzione Direzione, campo Campo);
void Crea_Campo(campo * Campo, int quadrati);
void Crea_Buffer_Campo (buffer_campo ** buffer, campo Campo,
        int spazio_righe, int spazio_colonne);
int Valore_Casella (casella_selezionata Casella, campo Campo);
booleano Stessa_Casella (casella_selezionata Casella1,
                         casella_selezionata Casella2);
casella_selezionata Casella_Selezionata(int x, int y);
booleano Adiacente(casella_selezionata Casella1, casella_selezionata Casella,
                   campo Campo);
booleano Stessa_Linea (casella_selezionata Casella1,
                       casella_selezionata Casella2, campo Campo);
void Setta_Valore (casella_selezionata Casella, campo Campo, casella valore);

#endif // _BOARD_H
