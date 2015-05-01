#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "basetypes.h"

typedef struct nodo_imp_gioc
{
    int colore_pedine;
    int tipo_pedine;
    short_string nome_giocatore;
    struct nodo_imp_gioc * prossimo;
} impostazioni_giocatore;

typedef impostazioni_giocatore * lista_impostazioni_giocatori;

typedef struct
{
    int grandezza_campo;
    int numero_giocatori;
    int numero_pedine;
    lista_impostazioni_giocatori giocatori;
    int giocatore_iniziale;
    int colore_campo;
    int colore_linee;
    int colore_selezione;
    booleano mostra_pedine_fuori;
    booleano mostra_coordinate;
    booleano mostra_punteggio;
    booleano suoni;
    int suono_inserimento;
    int suono_spostamento;
    int suono_mulino;
    int suono_eliminazione;
    int suono_sconfitta;
    int suono_vittoria;
    short_string nome_partita;
    int spazio_righe;
    int spazio_colonne;
} impostazioni;

void Impostazioni_Predefinite (impostazioni * Imp);

int Controlla_Impostazioni (impostazioni Imp);
void Crea_Lista_Impostazioni (impostazioni, lista_stringhe * lista_nomi,
                              lista_stringhe * lista_valori);
int Cambia_Impostazione (impostazioni * Imp, int indice, int valore);
int Cambia_Impostazioni_Giocatori (impostazioni * Imp);
void Colore_To_String (short_string stringa, int colore);
char Pedina_To_Char (int pedina);
booleano Messaggio(char * messaggio, booleano conferma);
void Stampa_Menu_Lista(int cursore, lista_stringhe lista_nomi, int colore);
int Leggi_Nomi_Partite (lista_stringhe * lista_nomi);
void Leggi_Valore_Stringa (char * valore);

#endif // _SETTINGS_H
