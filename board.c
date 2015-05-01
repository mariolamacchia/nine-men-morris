#include <stdlib.h>
#include "board.h"

int Lato_Campo (int grandezza)
{
    return grandezza*3-2;
}

int Area_Campo (int grandezza)
{
    return Lato_Campo(grandezza)*Lato_Campo(grandezza);
}

int Lato_Buffer_Campo(int grandezza, int spazio)
{
    return Lato_Campo(grandezza)+(Lato_Campo(grandezza)-1)*spazio;
}

int Perimetro_Quadrato (int grandezza)
{
    return (grandezza-1)*4;
}


void Crea_Campo (campo * Campo, int quadrati)
{
    int dimensioni,caselle,i,j,porzione,offset;

    dimensioni = Lato_Campo(quadrati);
    Campo->caselle = malloc(sizeof(casella)*Area_Campo(quadrati));

    for (i=0; i<dimensioni*dimensioni; i++) *(Campo->caselle+i) = -1;

    //disegna caselle
    for (i=0;i<quadrati;i++)
    {
        //disegna caselle mediane
        offset = i*dimensioni + dimensioni / 2;
        *(Campo->caselle + offset) = 0;
        offset = (dimensioni - 1 - i) * dimensioni + dimensioni / 2;
        *(Campo->caselle + offset) = 0;
        offset = dimensioni / 2 * dimensioni + i;
        *(Campo->caselle + offset) = 0;
        offset = dimensioni / 2 * dimensioni + dimensioni - 1 - i;
        *(Campo->caselle + offset) = 0;

        //prima metà
        caselle = quadrati/2;
        for (j=0; j<caselle; j++)
        {
            porzione = dimensioni/2-i;
            offset = i*dimensioni + porzione*j/caselle+i;
            *(Campo->caselle + offset) = 0;
            offset = (dimensioni - 1 - i) * dimensioni +
                     porzione  * j / caselle + i;
            *(Campo->caselle + offset) = 0;
            offset = (porzione * j / caselle + i) * dimensioni + i;
            *(Campo->caselle + offset) = 0;
            offset = (porzione * j / caselle + i) * dimensioni
                     + dimensioni - 1 - i;
            *(Campo->caselle + offset) = 0;
        }
        //seconda metà
        caselle = quadrati/2;
        if (quadrati%2==0) caselle=caselle-1;
        for (j=0;j<caselle; j++)
        {
            porzione = dimensioni/2-i;
            offset = i*dimensioni + (dimensioni - (porzione*j/caselle+1) -i);
            *(Campo->caselle + offset) = 0;
            offset = (dimensioni - 1 - i) * dimensioni +
                     (dimensioni - (porzione * j / caselle + 1) - i);
            *(Campo->caselle + offset) = 0;
            offset = (dimensioni - (porzione * j / caselle + 1) -i) *
                     dimensioni + i;
            *(Campo->caselle + offset) = 0;
            offset = (dimensioni - (porzione * j / caselle + 1) - i) *
                     dimensioni + dimensioni - i - 1;
            *(Campo->caselle + offset) = 0;
        }

    }
}

void Crea_Buffer_Campo (buffer_campo ** buffer, campo Campo,
                        int spazio_righe, int spazio_colonne)
{
    int dimensioni,i,j,h,k,l,m, height, width;
    signed char valore;
    unsigned char * temp;

    //libera lo spazio precedentemente impiegato
    free(*buffer);

    //calcola le dimensioni e alloca lo spazio
    dimensioni = Lato_Campo(Campo.grandezza);
    height = dimensioni+(dimensioni-1)*spazio_righe;
    width = dimensioni+(dimensioni-1)*spazio_colonne;
    temp = malloc (sizeof(char)*height*width);

    /*  Nel buffer dello schermo viene memorizzato ciò da cui si prenderà
        la porazione da stampare. Viene tutto memorizzato come una matrice di
        caratteri: le caselle vuote come 'O', le pedine come il numero del
        rispettivo giocatore, le linee con il rispettivo carattere mentre lo
        spazio, per non essere confuso con il giocatore corrispondente al suo
        valore ASCII, verrà memorizzato con un valore arbitrario, KEY_SPAZIO,
        abbastanza grande da non poter essere un giocatore.  */

    h=0;
    k=0;
    for (i=0; i<dimensioni; i++)
    {
        for (j=0;j<dimensioni;j++)
        {
            valore = Valore_Casella(Casella_Selezionata(j,i),Campo);
            //casella
            if (valore != -1)
            {
                temp[h*width+(k++)] = valore;
                /**Spazio caselle**/
                //linee collegamento orizzontali
                if (j>=i && j<dimensioni-1-i && i<Campo.grandezza && k<width)
                    for (l=0;l<spazio_colonne;l++)
                        temp[h*width+(k++)] = 196;
                else if (j<i && j>=dimensioni-1-i && i>=Campo.grandezza*2-2 && k<width)
                    for (l=0;l<spazio_colonne;l++)
                        temp[h*width+(k++)] = 196;
                else if (i==dimensioni/2 && ((j<Campo.grandezza-1)||(j>=Campo.grandezza*2-2)) && k<width)
                    for (l=0;l<spazio_colonne;l++)
                        temp[h*width+(k++)] = 196;
                //vuoto
                else if (k<width)
                    for (l=0;l<spazio_colonne;l++)
                        temp[h*width+(k++)] = KEY_SPAZIO;
            }
            //altro
            else
            {
                //linee collegamento orizzontali
                if (j>=i && j<=dimensioni-1-i && i<Campo.grandezza)
                {
                    temp[h*width+(k++)] = 196;
                    if (k<width)
                        for (l=0;l<spazio_colonne;l++)
                            temp[h*width+(k++)] = 196;
                }
                else if (j<=i && j>=dimensioni-1-i && i>=Campo.grandezza*2-2)
                {
                    temp[h*width+(k++)] = 196;
                    if (k<width)
                        for (l=0;l<spazio_colonne;l++)
                            temp[h*width+(k++)] = 196;
                }
                else if (i==dimensioni/2 && ((j<Campo.grandezza)||(j>=Campo.grandezza*2-2)))
                {
                    temp[h*width+(k++)] = 196;
                    if (k<width)
                        for (l=0;l<spazio_colonne;l++)
                            temp[h*width+(k++)] = 196;
                }
                //linee collegamento verticali
                else if (i>=j && i<=dimensioni-j && j<Campo.grandezza)
                {
                    temp[h*width+(k++)] = 179;
                    if (k<width)
                        for (l=0;l<spazio_colonne;l++)
                            temp[h*width+(k++)] = KEY_SPAZIO;
                }
                else if (i<=j && i>=dimensioni-1-j && j>Campo.grandezza*2-2)
                {
                    temp[h*width+(k++)] = 179;
                    if (k<width)
                        for (l=0;l<spazio_colonne;l++)
                            temp[h*width+(k++)] = KEY_SPAZIO;
                }
                //vuoto
                else
                {
                    temp[h*width+(k++)] = KEY_SPAZIO;
                    if (k<width)
                        for (l=0;l<spazio_colonne;l++)
                            temp[h*width+(k++)] = KEY_SPAZIO;
                }
            }
        }
        h++;
        k=0;
        //righe intermedie
        if (h<height-1)
        {
            for (m=0;m<spazio_righe;m++)
            {
                for (j=0;j<dimensioni;j++)
                {
                    valore = Valore_Casella(Casella_Selezionata(j,i),Campo);
                    if (valore!=-1 && i>=j && i<dimensioni-1-j && j<=Campo.grandezza)
                    {
                        temp[h*width+(k++)]=179;
                        if (k<width)
                            for (l=0;l<spazio_colonne;l++) temp[h*width+(k++)]=KEY_SPAZIO;
                    }
                    else if (valore!=-1 && i<j && i>=dimensioni-1-j && j>=Campo.grandezza*2-2)
                    {
                        temp[h*width+(k++)]=179;
                        if (k<width)
                            for (l=0;l<spazio_colonne;l++) temp[h*width+(k++)]=KEY_SPAZIO;
                    }
                    else if (j==dimensioni/2 && (i<Campo.grandezza-1 || i>=Campo.grandezza*2-2))
                    {
                        temp[h*width+(k++)]=179;
                        if (k<width)
                            for (l=0;l<spazio_colonne;l++) temp[h*width+(k++)]=KEY_SPAZIO;
                    }
                    else if (temp[(h-1)*width+k]==179)
                    {
                        temp[h*width+(k++)]=179;
                        if (k<width)
                            for (l=0;l<spazio_colonne;l++) temp[h*width+(k++)]=KEY_SPAZIO;
                    }
                    else
                    {
                        temp[h*width+(k++)]=KEY_SPAZIO;
                        if (k<width)
                            for (l=0;l<spazio_colonne;l++) temp[h*width+(k++)]=KEY_SPAZIO;
                    }

                }
                h++;
                k=0;
            }
        }
    }
    *buffer = temp;
}

casella_selezionata Casella_Selezionata(int x, int y)
{
    casella_selezionata Casella;
    Casella.x = x;
    Casella.y = y;
    return Casella;
}

casella_selezionata Casella_Adiacente(casella_selezionata Casella, direzione Direzione, campo Campo)
{
    //Restituisce Casella se non c'è una casella in direzione
    int i;
    casella_selezionata trovata;

    trovata = Casella;
    switch (Direzione)
    {
        case UP:
            i=Casella.y-1;
            while (i>=0 && trovata.y==Casella.y)
            {
                if (Campo.caselle[i*(Lato_Campo(Campo.grandezza))+Casella.x] != -1)
                    trovata.y = i;
                else i--;
            }
            break;
        case DOWN:
            i=Casella.y+1;
            while (i<Lato_Campo(Campo.grandezza) && trovata.y==Casella.y)
            {
                if (Campo.caselle[i*(Lato_Campo(Campo.grandezza))+Casella.x] != -1)
                    trovata.y = i;
                else i++;
            }
            break;
        case LEFT:
            i=Casella.x-1;
            while (i>=0 && trovata.x==Casella.x)
            {
                if (Campo.caselle[Casella.y*(Lato_Campo(Campo.grandezza))+i] != -1)
                    trovata.x = i;
                else i--;
            }
            break;
        case RIGHT:
            i=Casella.x+1;
            while (i<Lato_Campo(Campo.grandezza) && trovata.x==Casella.x)
            {
                if (Campo.caselle[Casella.y*(Lato_Campo(Campo.grandezza))+i] != -1)
                    trovata.x = i;
                else i++;
            }
            break;
    }
    return trovata;
}

int Valore_Casella(casella_selezionata Casella, campo Campo)
{
    return Campo.caselle[Casella.y*Lato_Campo(Campo.grandezza)+Casella.x];
}

void Setta_Valore(casella_selezionata Casella, campo Campo, casella valore)
{
    Campo.caselle[Casella.y*Lato_Campo(Campo.grandezza)+Casella.x]=valore;
}

booleano Stessa_Linea(casella_selezionata Casella1, casella_selezionata Casella2, campo Campo)
{
    booleano risultato = false;
    if (Casella1.x == Casella2.x)
    {
        //si trovano nelle prime righe
        if (Casella1.x<=Campo.grandezza &&
                Casella1.y >= Casella1.x &&
                Casella1.y < Lato_Campo(Campo.grandezza)-Casella1.x &&
                Casella2.y >= Casella1.x &&
                Casella2.y < Lato_Campo(Campo.grandezza)-Casella1.x)
            risultato = true;
        //si trovano nelle ultime righe
        if (Casella1.x >= Campo.grandezza*2-2 &&
                Casella1.y <= Casella1.x &&
                Casella1.y >= Campo.grandezza*3-3-Casella1.x &&
                Casella2.y <= Casella1.x &&
                Casella2.y >= Campo.grandezza*3-3-Casella1.x)
            risultato = true;
        //si trovano nelle righe centrali
        if (Casella1.x==Lato_Campo(Campo.grandezza)/2 &&
                ((Casella1.y<=Campo.grandezza && Casella2.y<=Campo.grandezza)||
                 (Casella1.y>=Campo.grandezza*2-2 && Casella2.y>=Campo.grandezza*2-2)))
            risultato = true;
    }
    else if (Casella1.y == Casella2.y)
    {
        //si trovano nelle prime righe
        if (Casella1.y<=Campo.grandezza &&
                Casella1.x >= Casella1.y &&
                Casella1.x < Lato_Campo(Campo.grandezza)-Casella1.y &&
                Casella2.x >= Casella1.y &&
                Casella2.x < Lato_Campo(Campo.grandezza)-Casella1.y)
            risultato = true;
        //si trovano nelle ultime righe
        if (Casella1.y >= Campo.grandezza*2-2 &&
                Casella1.x <= Casella1.y &&
                Casella1.x >= Lato_Campo(Campo.grandezza)-1-Casella1.y &&
                Casella2.x <= Casella1.y &&
                Casella2.x >= Lato_Campo(Campo.grandezza)-1-Casella1.y)
            risultato = true;
        //si trovano nelle righe centrali
        if (Casella1.y==Lato_Campo(Campo.grandezza)/2 &&
                ((Casella1.x<=Campo.grandezza && Casella2.x<=Campo.grandezza)||
                 (Casella1.x>=Campo.grandezza*2-2 && Casella2.x>=Campo.grandezza*2-2)))
            risultato = true;
    }
    else return false;
    return risultato;
}

booleano Stessa_Casella (casella_selezionata Casella1, casella_selezionata Casella2)
{
    if (Casella1.x == Casella2.x && Casella1.y == Casella2.y) return true;
    else return false;
}

booleano Adiacente (casella_selezionata Casella1, casella_selezionata Casella2, campo Campo)
{
    if ((Stessa_Linea(Casella1,Casella2,Campo)) &&
            (Stessa_Casella(Casella_Adiacente(Casella1,UP,Campo),Casella2) ||
             Stessa_Casella(Casella_Adiacente(Casella1,DOWN,Campo),Casella2) ||
             Stessa_Casella(Casella_Adiacente(Casella1,LEFT,Campo),Casella2) ||
             Stessa_Casella(Casella_Adiacente(Casella1,RIGHT,Campo),Casella2)))
        return true;
    else return false;
}



