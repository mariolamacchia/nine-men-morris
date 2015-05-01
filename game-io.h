#include "board.h"
#include "game.h"

// Chars
#define ESC 27
#define ARROW 224
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ENTER 13
#define CANC 83

// File names
#define FILE_PARTITE "partite"
#define FILE_AIUTO "aiuto.txt"
#define FILE_IMP "impostazioni"
#define FILE_RECORD "record.txt"

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
void Stampa_Schermata (buffer_campo * buffer, partita Partita,
                       impostazioni Imp, casella_selezionata cursore_casella,
                       casella_selezionata pedina_da_spostare);
int Scelta_Casella(casella_selezionata * cursore, partita * Partita);
void Stampa_Cornice_Piccola (int colore);
