#ifndef _BASETYPES_H
#define _BASETYPES_H

#include "graphics.h"
#define SHORT_STRING 20

typedef enum {false, true} booleano;

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

typedef enum {UP,DOWN,LEFT,RIGHT} direzione;

int Numero_Stringhe (lista_stringhe lista_elementi);

#endif
