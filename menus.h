#include "basetypes.h"
#include "settings.h"
#include "game.h"

// Menu choices
#define MP_VNUOVA 1
#define MP_VCARICA 2
#define MP_VSALVA 3
#define MP_VIMP 4
#define MP_VAIUTO 6
#define MP_VRECORD 5

#define MP_NCAMPI 7
#define MR_MAX 10
#define MR_DIV1_Y 10
#define MR_DIV2_Y 22
#define MR_DIV_X 50
#define MR_TITOLO_LUNGHEZZA 43
#define MR_NOME_X 28
#define MR_PUNTI_X 48

void Stampa_Titolo();
void Stampa_Cornice(int colore);
void Stampa_Titolo_Menu(char * titolo, int colore);
void Stampa_Indicazioni(char * indicazioni);
void Stampa_Indicatori_Pagina (int pagina, int numero_pagine, int colore);
void Stampa_Cursore(int cursore, int colore, booleano doppio);
void Stampa_Menu(int cursore);
int Scelta_Menu(int * cursore);
int Scelta_Menu_Lista(int * cursore, int numero_voci);
void Stampa_Menu_Gioco (partita Partita, impostazioni Imp);
void Stampa_Menu_Impostazioni (int cursore, lista_stringhe lista_nomi,
                               lista_stringhe lista_valori, int colore);
