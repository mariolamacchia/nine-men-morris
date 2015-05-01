#include <stdlib.h>
#include "basetypes.h"

int Numero_Stringhe(lista_stringhe lista_elementi)
{
    int i=0;
    while (lista_elementi != NULL)
    {
        lista_elementi = lista_elementi ->prossimo;
        i++;
    }
    return i;
}
