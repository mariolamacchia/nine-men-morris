#include "basetypes.h"
#include "game.h"
#include "settings.h"
#include "menus.h"

void Inizializza_Gioco(partita * Partita, impostazioni * Imp);
int Nuova_Partita(impostazioni * Imp, partita * Partita);
int Carica_Partita(partita * Partita, impostazioni Imp);
int Salva_Partita(partita * Partita);
int Record();
int Aiuto();
int Impostazioni(impostazioni * Imp);
booleano Esci();
