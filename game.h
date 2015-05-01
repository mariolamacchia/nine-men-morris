#ifndef _GAME_H
#define _GAME_H

#include "settings.h"
#include "board.h"

typedef struct nodo_gioc
{
    int colore_pedine;
    int tipo_pedine;
    short_string nome_giocatore;
    struct nodo_gioc * prossimo;
    int pedine_da_inserire;
    int pedine_in_gioco;
    booleano in_gioco;
    float punteggio;
} giocatore;

typedef giocatore * lista_giocatori;

typedef struct
{
    campo campo;
    int numero_giocatori;
    int numero_pedine;
    lista_giocatori giocatori;
    int turno;
    booleano iniziata;
    booleano mulino;
    short_string nome;
    int punteggio;
} partita;

int Numero_Giocatori (partita * Partita);
booleano Mulino (casella_selezionata Casella, campo Campo);
int Inserisci_Pedina (casella_selezionata Casella, partita * Partita);
int Sposta_Pedina (casella_selezionata Sorgente,
                   casella_selezionata Destinazione,
                   partita * Partita);
int Elimina_Pedina (casella_selezionata Casella, partita * Partita);
giocatore * Prossimo_Turno (partita * Partita);
int Gioca(partita * Partita, impostazioni Imp);
int Fase_Posizionamento (partita * Partita, impostazioni Imp);
int Fase_Spostamento (partita * Partita, impostazioni Imp);
int Vittoria (short_string Nome, float punteggio);
booleano Pedina_Bloccata (casella_selezionata Casella, campo Campo);
booleano Giocatore_Eliminato(partita Partita, int giocatore);
booleano Fine_Partita (partita Partita);
void Inizializza_Partita (impostazioni Imp, partita * game);

#endif // _GAME_H
