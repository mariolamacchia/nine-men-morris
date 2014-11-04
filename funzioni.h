/*
 * funzioni.h
 *
 *  Created on: 25/lug/2013
 *      Author: utente
 */

#ifndef FUNZIONI_H_
#define FUNZIONI_H_



#endif /* FUNZIONI_H_ */

#define SHORT_STRING 20

//Grafica
#define ALTEZZA_TITOLO 6
#define BUFFER_X 80
#define BUFFER_Y 25
#define BUFFER_TESTO_X 50
#define BUFFER_TESTO_Y 10
#define DEF_BACK_COLOR 0
#define BACK_COLOR 3
#define BACK_CHAR ' '
#define DEF_COLOR 10
#define TESTO_X 15
#define TESTO_Y 9
#define MARGINE_CURSORE 5
#define COL0_X 20
#define COL1_X 10
#define COL2_X 31
#define MEX_X 20
#define MEX_Y 11
#define MEX_HEIGHT 5
#define MEX_WIDTH 40
#define INDICAZIONI_HEIGHT 5
//

//Caratteri
#define ESC 27
#define ARROW 224
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ENTER 13
#define CANC 83
//

//Menu
#define MP_NCAMPI 7
#define MP_VNUOVA 1
#define MP_VCARICA 2
#define MP_VSALVA 3
#define MP_VIMP 4
#define MP_VAIUTO 6
#define MP_VRECORD 5
#define MP_COLOR 14
#define MS_COLOR 9
#define MC_COLOR 11
#define MA_COLOR 13
#define MR_COLOR 13
#define MR_1_COLOR 12
#define MR_2_COLOR 10
#define MR_3_COLOR 11
#define MR_LAST_COLOR 15
#define MR_MAX 10
#define MR_DIV1_Y 10
#define MR_DIV2_Y 22
#define MR_DIV_X 50
#define MR_TITOLO_LUNGHEZZA 43
#define MR_NOME_X 28
#define MR_PUNTI_X 48
#define MI_COLOR 10
#define ME_COLOR 12
//

//Errori
#define ERR_FILE_PARTITE_INESISTENTE 1
#define ERR_FILE_IMP_INESISTENTE 2
#define ERR_FILE_REC_INESISTENTE 3
#define ERR_FILE_AIUTO_INESISTENTE 4
#define ERR_FILE_IMP_INVALID 5
#define ERR_IMP_INVALID 6
#define ERR_FILE_AIUTO_VUOTO 7
#define ERR_PARTITA_NON_INIZIATA 8
#define ERR_FILE_PARTITE_VUOTO 9
#define ERR_FILE_REC_VUOTO 10
#define ERR_FILE_IMP_VUOTO 12
#define ERR_IMP_INESISTENTE 13
//errori di gioco
#define ERR_CASELLA_INESISTENTE 100
#define ERR_CASELLA_PIENA 101
#define ERR_CASELLA_VUOTA 102
#define ERR_CASELLE_NON_ADIACENTI 103
#define ERR_PEDINA_AVVERSARIA 104
#define ERR_PEDINA_GIOCATORE_TURNO 105
#define ERR_INTERROTTA 106
#define ERR_MULINO 107
//

//Nomi file
#define FILE_PARTITE "partite"
#define FILE_AIUTO "aiuto.txt"
#define FILE_IMP "impostazioni"
#define FILE_RECORD "record.txt"

//Gioco
#define MAX_GAME_SIZE 10
#define MIN_GAME_SIZE 3
#define MAX_SPAZIO_RIGHE 5
#define MAX_SPAZIO_COLONNE 5
#define W_PUNTEGGIO_WIDTH 20
#define W_PEDINE_WIDTH 21
#define W_TOP 3
#define W_MEX_BOX_HEIGHT 5
#define KEY_SPAZIO 200
//

typedef enum {False, True} booleano;

typedef char short_string[SHORT_STRING];
typedef char long_string[BUFFER_X];

typedef struct elem_riga
{
    long_string stringa;
    struct elem_riga * prossimo;
} riga_testo;

typedef riga_testo * buffer_testo;

typedef struct nodo_stringa
{
    short_string stringa;
    struct nodo_stringa * prossimo;
} elemento_stringa;

typedef elemento_stringa * lista_stringhe;

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

typedef enum {UP,DOWN,LEFT,RIGHT} direzione;

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

void gotoxy(int x, int y);
void Cambia_Colore (int colore, int sfondo);
void Cambia_Sfondo (int colore, int colore_sfondo);
void Inizializza_Gioco(partita * Partita, impostazioni * Imp);
void Cursore_Visibile (booleano visibile);

void Stampa_Titolo();
void Stampa_Cornice(int colore);
void Stampa_Titolo_Menu(char * titolo, int colore);
void Stampa_Indicazioni(char * indicazioni);
void Stampa_Indicatori_Pagina (int pagina, int numero_pagine, int colore);
void Stampa_Cursore(int cursore, int colore, booleano doppio);
void Riproduci_Suono (int suono);

int Numero_Giocatori (partita * Partita);
int Numero_Stringhe (lista_stringhe lista_elementi);
int Lato_Campo (int grandezza);
int Area_Campo (int grandezza);
int Lato_Buffer_Campo (int grandezza, int spazio);
int Perimetro_Quadrato(int grandezza);

booleano Messaggio(char * messaggio, booleano conferma);
void Stampa_Menu(int cursore);
int Scelta_Menu(int * cursore);
int Nuova_Partita(impostazioni * Imp, partita * Partita);
int Controlla_Impostazioni (impostazioni Imp);
void Inizializza_Partita (impostazioni Imp, partita * game);
void Crea_Campo(campo * Campo, int quadrati);
void Crea_Buffer_Campo (buffer_campo ** buffer, campo Campo,
        int spazio_righe, int spazio_colonne);
void Stampa_Buffer_Campo (buffer_campo * buffer,
                          int top, int left, int width, int height,
                          casella_selezionata cursore,
                          casella_selezionata pedina_da_spostare,
                          partita Partita, impostazioni Imp);
void Stampa_Finestra_Punteggi (int left, int top, int width, int height,
                               partita Partita, impostazioni Imp);
void Stampa_Finestra_Pedine (int left, int top, int width, int height,
                             partita Partita, impostazioni Imp);
void Stampa_Coordinate (int left, int top, int width, int height,
                        int grandezza, impostazioni Imp,
                        casella_selezionata cursore);
void Stampa_Menu_Gioco (partita Partita, impostazioni Imp);
void Stampa_Schermata (buffer_campo * buffer, partita Partita,
                       impostazioni Imp, casella_selezionata cursore_casella,
                       casella_selezionata pedina_da_spostare);
casella_selezionata Casella_Adiacente (casella_selezionata Casella,
                                       direzione Direzione, campo Campo);
int Valore_Casella (casella_selezionata Casella, campo Campo);
void Setta_Valore (casella_selezionata Casella, campo Campo, casella valore);
booleano Stessa_Linea (casella_selezionata Casella1,
                       casella_selezionata Casella2, campo Campo);
booleano Mulino (casella_selezionata Casella, campo Campo);
booleano Stessa_Casella (casella_selezionata Casella1,
                         casella_selezionata Casella2);
casella_selezionata Casella_Selezionata(int x, int y);
booleano Adiacente(casella_selezionata Casella1, casella_selezionata Casella,
                   campo Campo);
int Inserisci_Pedina (casella_selezionata Casella, partita * Partita);
int Sposta_Pedina (casella_selezionata Sorgente,
                   casella_selezionata Destinazione,
                   partita * Partita);
int Elimina_Pedina (casella_selezionata Casella, partita * Partita);

int Scelta_Casella(casella_selezionata * cursore, partita * Partita);

giocatore * Prossimo_Turno (partita * Partita);
int Gioca(partita * Partita, impostazioni Imp);
int Fase_Posizionamento (partita * Partita, impostazioni Imp);
int Fase_Spostamento (partita * Partita, impostazioni Imp);
int Vittoria (short_string Nome, float punteggio);
booleano Pedina_Bloccata (casella_selezionata Casella, campo Campo);
booleano Giocatore_Eliminato(partita Partita, int giocatore);
booleano Fine_Partita (partita Partita);
int Carica_Partita(partita * Partita, impostazioni Imp);
int Salva_Partita(partita * Partita);
void Stampa_Menu_Lista(int cursore, lista_stringhe lista_nomi, int colore);
int Leggi_Nomi_Partite (lista_stringhe * lista_nomi);
int Scelta_Menu_Lista(int * cursore, int numero_voci);
int Impostazioni(impostazioni * Imp);
void Crea_Lista_Impostazioni (impostazioni, lista_stringhe * lista_nomi,
                              lista_stringhe * lista_valori);
void Stampa_Menu_Impostazioni (int cursore, lista_stringhe lista_nomi,
                               lista_stringhe lista_valori, int colore);
int Cambia_Impostazione (impostazioni * Imp, int indice, int valore);
void Leggi_Valore_Stringa (char * valore);
int Cambia_Impostazioni_Giocatori (impostazioni * Imp);
void Impostazioni_Predefinite (impostazioni * Imp);
void Colore_To_String (short_string stringa, int colore);
char Pedina_To_Char (int pedina);
int Record();
int Aiuto();
void Gestione_Errori(int errore);
booleano Esci();
