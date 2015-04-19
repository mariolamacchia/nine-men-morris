/*
 * main.c
 *
 *  Created on: 25/lug/2013
 *      Author: utente
 */


#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"

int main()
{
    int cursore = 0, scelta;
    booleano esci = false;
    partita Partita;
    impostazioni Imp;
    Impostazioni_Predefinite(&Imp);

    Inizializza_Gioco(&Partita,&Imp);


    while (!esci)
    {
        Stampa_Menu(cursore);
        scelta = Scelta_Menu(&cursore);
        switch (scelta)
        {
            case MP_VNUOVA:
                Gestione_Errori(Nuova_Partita(&Imp, &Partita));
                break;
            case MP_VCARICA:
                Gestione_Errori(Carica_Partita(&Partita, Imp));
                break;
            case MP_VSALVA:
                Gestione_Errori(Salva_Partita(&Partita));
                break;
            case MP_VIMP:
                Gestione_Errori(Impostazioni(&Imp));
                break;
            case MP_VRECORD:
                Gestione_Errori(Record());
                break;
            case MP_VAIUTO:
                Gestione_Errori(Aiuto());
                break;
            case 0:
                esci = Esci();
                break;
        }
    }


    return 0;
}
