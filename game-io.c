#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "console.h"
#include "game-io.h"
#include "errors.h"

void Stampa_Titolo ()
{
    int i;
    int nine = 14,
        i1 = 12,
        men = 10,
        morris = 12,
        i2 = 14,
        bordo = 5;

    gotoxy(0,0);
    Cambia_Colore(BACK_COLOR,DEF_BACK_COLOR);
    for (i=0;i<bordo;i++) putchar(BACK_CHAR);
    Cambia_Colore(nine,DEF_BACK_COLOR);
    printf(" _   _");
    Cambia_Colore(i1,DEF_BACK_COLOR);
    printf(" _              ");
    Cambia_Colore(men,DEF_BACK_COLOR);
    printf("__  __             ");
    Cambia_Colore(morris,DEF_BACK_COLOR);
    printf("__  __                 ");
    Cambia_Colore(i2,DEF_BACK_COLOR);
    printf("_     \n");

    Cambia_Colore(BACK_COLOR,DEF_BACK_COLOR);
    for (i=0;i<bordo;i++) putchar(BACK_CHAR);
    Cambia_Colore(nine,DEF_BACK_COLOR);
    printf("| \\ | ");
    Cambia_Colore(i1,DEF_BACK_COLOR);
    printf("(_)            ");
    Cambia_Colore(men,DEF_BACK_COLOR);
    printf("|  \\/  |           ");
    Cambia_Colore(morris,DEF_BACK_COLOR);
    printf("|  \\/  |               ");
    Cambia_Colore(i2,DEF_BACK_COLOR);
    printf("(_)    \n");

    Cambia_Colore(BACK_COLOR,DEF_BACK_COLOR);
    for (i=0;i<bordo;i++) putchar(BACK_CHAR);
    Cambia_Colore(nine,DEF_BACK_COLOR);
    printf("|  \\| |_ _ __   ___  ");
    Cambia_Colore(men,DEF_BACK_COLOR);
    printf("| \\  / | ___ _ __  ");
    Cambia_Colore(morris,DEF_BACK_COLOR);
    printf("| \\  / | ___  _ __ _ __ _ ___ \n");

    Cambia_Colore(BACK_COLOR,DEF_BACK_COLOR);
    for (i=0;i<bordo;i++) putchar(BACK_CHAR);
    Cambia_Colore(nine,DEF_BACK_COLOR);
    printf("| . ` | | '_ \\ / _ \\ ");
    Cambia_Colore(men,DEF_BACK_COLOR);
    printf("| |\\/| |/ _ \\ '_ \\ ");
    Cambia_Colore(morris,DEF_BACK_COLOR);
    printf("| |\\/| |/ _ \\| '__| '__| / __|\n");

    Cambia_Colore(BACK_COLOR,DEF_BACK_COLOR);
    for (i=0;i<bordo;i++) putchar(BACK_CHAR);
    Cambia_Colore(nine,DEF_BACK_COLOR);
    printf("| |\\  | | | | |  __/ ");
    Cambia_Colore(men,DEF_BACK_COLOR);
    printf("| |  | |  __/ | | |");
    Cambia_Colore(morris,DEF_BACK_COLOR);
    printf("| |  | | (_) | |  | |  | \\__ \\\n");

    Cambia_Colore(BACK_COLOR,DEF_BACK_COLOR);
    for (i=0;i<bordo;i++) putchar(BACK_CHAR);
    Cambia_Colore(nine,DEF_BACK_COLOR);
    printf("|_| \\_|_|_| |_|\\___| ");
    Cambia_Colore(men,DEF_BACK_COLOR);
    printf("|_|  |_|\\___|_| |_|");
    Cambia_Colore(morris,DEF_BACK_COLOR);
    printf("|_|  |_|\\___/|_|  |_|  |_|___/\n");

    //ripristina colori default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Stampa_Cornice (int colore)
{
    int i,j;

    //stampa la cornice per i menu standard
    Cambia_Colore(colore, colore-8);
    gotoxy(TESTO_X-1,TESTO_Y-1);
    putchar(201);
    for (i=0;i<BUFFER_TESTO_X;i++) putchar(205);
    putchar(187);
    for (i=0;i<BUFFER_TESTO_Y;i++)
    {
        gotoxy(TESTO_X-1,TESTO_Y+i);
        putchar(186);
        for (j=TESTO_X; j<TESTO_X+BUFFER_TESTO_X; j++) putchar(' ');
        putchar(186);
    }
    gotoxy(TESTO_X-1,TESTO_Y+BUFFER_TESTO_Y);
    putchar(200);
    for (i=0;i<BUFFER_TESTO_X;i++) putchar(205);
    putchar(188);

    //ripristina i colori default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Stampa_Cornice_Piccola (int colore)
{
    int i,j;

    //stapa la cornice per i messaggi
    Cambia_Colore(colore, colore-8);
    gotoxy(MEX_X-1,MEX_Y-1);
    putchar(201);
    for (i=0; i<MEX_WIDTH; i++) putchar(205);
    putchar (187);
    for (i=0; i<MEX_HEIGHT; i++)
    {
        gotoxy(MEX_X-1,MEX_Y+i);
        putchar(186);
        for (j=0; j<MEX_WIDTH; j++) putchar(' ');
        putchar(186);
    }
    gotoxy(MEX_X-1,MEX_Y+MEX_HEIGHT);
    putchar(200);
    for (i=0; i<MEX_WIDTH; i++) putchar(205);
    putchar(188);

    //ripristina i colori default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Stampa_Titolo_Menu(char * titolo, int colore)
{
    int i;
    //Cancella precedenti scritte
    gotoxy(TESTO_X,TESTO_Y-2);
    Cambia_Colore(BACK_COLOR,DEF_BACK_COLOR);
    for (i=0;i<BUFFER_TESTO_X;i++) putchar(BACK_CHAR);

    //scrivi nuovo titolo
    Cambia_Colore(colore,DEF_BACK_COLOR);
    gotoxy(BUFFER_X/2-(strlen(titolo)/2),TESTO_Y-2);
    printf(titolo);

    //ripristina i colori default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Stampa_Indicazioni(char * indicazioni)
{
    int i, j, riga;

    //Cancella vecchie scritte
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
    for (i=0;i<INDICAZIONI_HEIGHT;i++)
    {
        gotoxy(TESTO_X-1,TESTO_Y+BUFFER_TESTO_Y+1+i);
        for (j=0;j<BUFFER_TESTO_X+2;j++) putchar(' ');
    }

    //stampa il testo entro i margini consentiti
    i=0;
    j=0;
    riga=0;
    gotoxy(TESTO_X-1,TESTO_Y+BUFFER_TESTO_Y+1);
    while (i<strlen(indicazioni))
    {
        if (indicazioni[i]!='\n')
        {
            putchar(indicazioni[i]);
            i++;
            j++;
        }
        else
        {
            i++;
            if (j)
            {
                riga++;
                j=0;
                gotoxy(TESTO_X-1,TESTO_Y+BUFFER_TESTO_Y+1+riga);
            }
        }
        if (j==BUFFER_TESTO_X+2)
        {
            j=0;
            riga++;
            gotoxy(TESTO_X-1,TESTO_Y+BUFFER_TESTO_Y+1+riga);
        }
    }

    //ripristina i colori default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Stampa_Indicatori_Pagina (int pagina, int numero_pagine, int colore)
{
    int i;

    Cambia_Colore(colore,DEF_BACK_COLOR);

    //indicatore pagina giù
    if  (pagina<numero_pagine-1)
    {
        for (i=0;i<2;i++)
        {
            gotoxy(TESTO_X+BUFFER_TESTO_X+2,TESTO_Y+BUFFER_TESTO_Y-(i));
            if (!i) putchar(31);
            else putchar('|');
        }
    }
    else
        //cancella indicatore pagina giù se non richiesto
    {
        for (i=0;i<2;i++)
        {
            gotoxy(TESTO_X+BUFFER_TESTO_X+2,TESTO_Y+BUFFER_TESTO_Y-(i));
            putchar(' ');
        }
    }

    //pagina sù
    if  (pagina>0)
    {
        for (i=0;i<2;i++)
        {
            gotoxy(TESTO_X+BUFFER_TESTO_X+2,TESTO_Y-1+(i));
            if (!i) putchar(30);
            else putchar('|');
        }
    }
    else
        //cancella se non richiesto
    {
        for (i=0;i<2;i++)
        {
            gotoxy(TESTO_X+BUFFER_TESTO_X+2,TESTO_Y-1+(i));
            putchar(' ');
        }
    }

    //ripristina i colori default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Stampa_Cursore(int cursore, int colore, booleano doppio)
{
    Cambia_Colore(colore,colore-8);
    gotoxy(TESTO_X+MARGINE_CURSORE, TESTO_Y+cursore%BUFFER_TESTO_Y);
    printf("-->");
    //stampa la freccia al contrario se richiesta
    if (doppio)
    {
        gotoxy(TESTO_X+BUFFER_TESTO_X-3-MARGINE_CURSORE,
               TESTO_Y+cursore%BUFFER_TESTO_Y);
        printf("<--");
    }

    //ripristina colori default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}
booleano Messaggio(char * messaggio, booleano conferma)
{
    char c, *temp;
    int i,x,y;

    Stampa_Cornice_Piccola(ME_COLOR);
    Cambia_Colore(DEF_COLOR,ME_COLOR-8);
    //se è un messaggio di conferma aggiungi " (s/n)"
    if (conferma)
    {
        temp = malloc (sizeof(char)*(strlen(messaggio)+strlen(" (s/n)")));
        strcpy(temp,messaggio);
        strcat(temp," (s/n)");
    }
    else temp = messaggio;

    //stampa entro i bordi
    /* x indica la colonna in cui si sta scrivendo
       y indica la riga in cui si sta scrivendo   */
    y=0;
    x=0;
    gotoxy(MEX_X,MEX_Y+(y++));
    for (i=0; i<strlen(temp); i++)
    {
        /*se il contatore ha raggiunto un multiplo della larghezza dello
          schermo si va a capo, a meno che il carattere letto al momento
          non sia di newline */
        if (x==MEX_WIDTH && temp[i]!='\n')
        {
            gotoxy(MEX_X,MEX_Y+(y++));
            x=0;
        }
        //si va a capo in caso di newline
        if (temp[i]=='\n')
        {
            gotoxy(MEX_X,MEX_Y+(y++));
            x=0;
        }
        //altrimenti si stampa il carattere
        else
        {
            putchar(temp[i]);
            x++;
        }
    }

    //attendi l'utente
    if (conferma)
    {
        while (c!='s' && c!='S' && c!='n' && c!='N' && c!=ESC)
        {
            c=getch();
        }
    }
    else getch();

    //resetta colori default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
    //libera spazio
    free(temp);

    if (c=='s' || c=='S') return true;
    else return false;
}

void Stampa_Menu(int cursore)
{
    int spostamento_cursore,i;

    Stampa_Titolo();
    Stampa_Cornice(MP_COLOR);
    Stampa_Titolo_Menu("MENU PRINCIPALE", MP_COLOR);

    i=0;
    Cambia_Colore(MP_COLOR,MP_COLOR-8);
    gotoxy(TESTO_X+COL0_X-7,TESTO_Y+i);
    printf("(n)");
    gotoxy(TESTO_X+COL0_X,TESTO_Y+i);
    Cambia_Colore(DEF_COLOR,MP_COLOR-8);
    printf("Nuova Partita");
    i++;

    gotoxy(TESTO_X+COL0_X-7,TESTO_Y+i);
    Cambia_Colore(MP_COLOR,MP_COLOR-8);
    printf("(c)");
    gotoxy(TESTO_X+COL0_X,TESTO_Y+i);
    Cambia_Colore(DEF_COLOR,MP_COLOR-8);
    printf("Carica Partita");
    i++;

    gotoxy(TESTO_X+COL0_X-7,TESTO_Y+i);
    Cambia_Colore(MP_COLOR,MP_COLOR-8);
    printf("(s)");
    gotoxy(TESTO_X+COL0_X,TESTO_Y+i);
    Cambia_Colore(DEF_COLOR,MP_COLOR-8);
    printf("Salva Partita");
    i+=2;

    gotoxy(TESTO_X+COL0_X-7,TESTO_Y+i);
    Cambia_Colore(MP_COLOR,MP_COLOR-8);
    printf("(i)");
    gotoxy(TESTO_X+COL0_X,TESTO_Y+i);
    Cambia_Colore(DEF_COLOR,MP_COLOR-8);
    printf("Impostazioni");
    i++;

    gotoxy(TESTO_X+COL0_X-7,TESTO_Y+i);
    Cambia_Colore(MP_COLOR,MP_COLOR-8);
    printf("(r)");
    gotoxy(TESTO_X+COL0_X,TESTO_Y+i);
    Cambia_Colore(DEF_COLOR,MP_COLOR-8);
    printf("Record");
    i++;

    gotoxy(TESTO_X+COL0_X-7,TESTO_Y+i);
    Cambia_Colore(MP_COLOR,MP_COLOR-8);
    printf("(a)");
    gotoxy(TESTO_X+COL0_X,TESTO_Y+i);
    Cambia_Colore(DEF_COLOR,MP_COLOR-8);
    printf("Aiuto");
    i+=2;

    gotoxy(TESTO_X+COL0_X-7,TESTO_Y+i);
    Cambia_Colore(MP_COLOR,MP_COLOR-8);
    printf("(Esc)");
    gotoxy(TESTO_X+COL0_X,TESTO_Y+i);
    Cambia_Colore(DEF_COLOR,MP_COLOR-8);
    printf("Esci");

    //allinea il cursore agli spazi nel menu
    spostamento_cursore=0;
    if (cursore > 2) spostamento_cursore++;
    if (cursore == 6) spostamento_cursore++;

    Stampa_Cursore(cursore+spostamento_cursore,MP_COLOR,true);

    i=0;

    Stampa_Indicazioni("Premere le frecce su e gi\x97 per muoversi nel menu e"
                       "\nINVIO nel per confermare la selezione oppure premere"
                       "\nsemplicemente il tasto corrispondente alla scelta"
                       "\ndesiderata.");

    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}


void Stampa_Buffer_Campo (buffer_campo * buffer, int top, int left, int width, int height, casella_selezionata cursore, casella_selezionata pedina_da_spostare, partita Partita, impostazioni Imp)
{
    int x,i,j,y,right,bottom, numero_righe, numero_colonne;
    char unsigned valore, *pedine, *colori;

    pedine = malloc(sizeof(char)*Partita.numero_giocatori);
    colori = malloc(sizeof(char)*Partita.numero_giocatori);

    numero_righe = Lato_Buffer_Campo(Partita.campo.grandezza,Imp.spazio_righe);
    numero_colonne = Lato_Buffer_Campo(Partita.campo.grandezza,Imp.spazio_colonne);

    //seleziona la parte del buffer che contiene la casella selezionata dal cursore
    x=0;
    if (cursore.x*(1+Imp.spazio_colonne)/width>0)
    {
        for (i=0;i<width*((cursore.x*(1+Imp.spazio_colonne))/width);i++)
            x++;
    }
    y=0;
    if (cursore.y*(1+Imp.spazio_righe)/height>0)
    {
        for (i=0;i<height*((cursore.y*(1+Imp.spazio_righe))/height);i++)
            y++;
    }

    //crea array pedine e colori
    for (i=0;i<Partita.numero_giocatori;i++)
    {
        *(colori+i) = Partita.giocatori->colore_pedine;
        *(pedine+i) = Partita.giocatori->tipo_pedine;
        Partita.giocatori = Partita.giocatori->prossimo;
    }
    //definisci il bottom
    if (y+height>numero_righe) bottom = numero_righe;
    else
    {
        bottom = y+height;
    }

    //stampa
    for (i=y;i<bottom;i++)
    {
        gotoxy(left,top+(i-y));
        //determina il right
        if (x+width > numero_colonne) right = numero_colonne;
        else right = x+width;
        for (j=x;j<right;j++)
        {
            //se la casella è vuota
            if ((valore=buffer[i*numero_colonne+j])==0)
            {
                //si seleziona lo sfondo a seconda che la casella sia quella selezionata dal cursore o no
                if ((cursore.x*(1+Imp.spazio_colonne)==j && cursore.y*(1+Imp.spazio_righe)==i)||(pedina_da_spostare.x*(1+Imp.spazio_colonne)==j && pedina_da_spostare.y*(1+Imp.spazio_righe)==i))
                    Cambia_Colore(Imp.colore_linee,Imp.colore_selezione);
                else Cambia_Colore(Imp.colore_linee,Imp.colore_campo);
                putchar('O');
            }
            //se la casella non è vuota
            else if (valore<=Perimetro_Quadrato(MAX_GAME_SIZE))
            {
                //come sopra, si seleziona lo sfondo
                if ((cursore.x*(1+Imp.spazio_colonne)==j && cursore.y*(1+Imp.spazio_righe)==i)||(pedina_da_spostare.x*(1+Imp.spazio_colonne)==j && pedina_da_spostare.y*(1+Imp.spazio_righe)==i))
                    Cambia_Colore(*(colori+valore-1),Imp.colore_selezione);
                else Cambia_Colore(*(colori+valore-1),Imp.colore_campo);
                putchar(Pedina_To_Char(*(pedine+valore-1)));
            }
            //altrimenti sono linee o spazio
            else
            {
                Cambia_Colore(Imp.colore_linee,Imp.colore_campo);
                if (valore == KEY_SPAZIO) putchar(' ');
                else putchar(valore);
            }
        }
    }

    //resetta colori default e libera lo spazio allocato
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
    free(pedine);
    free(colori);
}

void Stampa_Finestra_Punteggi (int left, int top, int width, int height, partita Partita, impostazioni Imp)
{
    int punteggi_x_pag, giocatore_primo_punteggio,i,j;
    giocatore * puntatore;

    //cancella sfondo
    for (i=0;i<height-1;i++)
    {
        gotoxy(left,top+i);
        for (j=0;j<width;j++) putchar(' ');
    }

    //determina quanti punteggi si devono essere per pagina
    punteggi_x_pag = (height-2)/3;
    //in base al turno di gioco si determina qual è il giocatore che deve apparire per primo,
    //qualora i punteggi siano troppi
    giocatore_primo_punteggio = 1;
    while (Partita.turno > punteggi_x_pag+giocatore_primo_punteggio-1)
        giocatore_primo_punteggio+=punteggi_x_pag;
    //si ricavano tutti i punteggi
    puntatore = Partita.giocatori;
    for (i=1;i<giocatore_primo_punteggio;i++) puntatore = puntatore->prossimo;
    for (i=0; i<punteggi_x_pag && puntatore != NULL; i++)
    {
        //si escludono i giocatori eliminati
        while (!puntatore->in_gioco)
        {
            puntatore = puntatore->prossimo;
        }
        //si stampano i punteggi
        gotoxy(left+1,top+1+i*3);
        Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
        printf(puntatore->nome_giocatore);
        Cambia_Colore(puntatore->colore_pedine,DEF_BACK_COLOR);
        gotoxy(left+1,top+2+i*3);
        printf("%.2f",puntatore->punteggio);
        puntatore = puntatore->prossimo;
    }

    //resetto i colori di default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Stampa_Finestra_Pedine (int left, int top, int width, int height, partita Partita, impostazioni Imp)
{
    int pedine_x_riga, giocatori_x_finestra, primo_gioc, righe_x_gioc,i,j,max_pedine;
    giocatore * puntatore;

    //cancella sfondo
    for (i=0;i<height-1;i++)
    {
        gotoxy(left,top+i);
        for (j=0;j<width;j++) putchar(' ');
    }

    //si determina quante pedine stanno in una riga
    pedine_x_riga = width-2;
    //dunque quante righe servono a rappresentare le pedine di un giocatore
    righe_x_gioc = 2+Partita.numero_pedine/pedine_x_riga;
    if (Partita.numero_pedine % pedine_x_riga) righe_x_gioc++;
    //infine i giocatori da mostrare per ogni schermata
    giocatori_x_finestra = (height-2)/righe_x_gioc;
    //si determina, in base al turno, quale giocatore debba apparire per primo,
    //qualora siano troppi per un'unica schermata
    primo_gioc = 1;
    while (Partita.turno > giocatori_x_finestra+primo_gioc-1)
        primo_gioc+=giocatori_x_finestra;
    //si ricavano le pedine
    puntatore = Partita.giocatori;
    for (i=1;i<primo_gioc;i++) puntatore = puntatore->prossimo;
    for (i=0; i<giocatori_x_finestra && puntatore != NULL; i++)
    {
        while (!puntatore->in_gioco)
        {
            puntatore = puntatore->prossimo;
        }

        gotoxy(left+1,top+1+i*righe_x_gioc);
        Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
        printf(puntatore->nome_giocatore);
        Cambia_Colore(puntatore->colore_pedine,DEF_BACK_COLOR);
        if (puntatore->pedine_da_inserire) max_pedine = puntatore->pedine_da_inserire;
        else max_pedine = Partita.numero_pedine - puntatore->pedine_in_gioco;
        for (j=0;j<max_pedine;j++)
        {
            if (!(j%pedine_x_riga)) gotoxy(left+1,top+2+i*righe_x_gioc+j/pedine_x_riga);
            putchar(Pedina_To_Char(puntatore->tipo_pedine));
        }
        puntatore = puntatore->prossimo;
    }

    //resetto i colori di default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Stampa_Coordinate (int left, int top, int width, int height, int grandezza, impostazioni Imp, casella_selezionata cursore)
{
    int x, y, i;

    //Ricavo la porzione di campo stampata
    x=0;
    y=0;
    while (cursore.x*(Imp.spazio_colonne+1) > x+width-1)
        x+=width;
    while (cursore.y*(Imp.spazio_righe+1) > y+height-1)
        y+=height;

    Cambia_Colore(Imp.colore_linee,Imp.colore_campo);

    //stampo le coordinate a partire dalla prima casella visualizzatat
    //prima le coordinate delle ordinate
    for (i=0; i<height; i++)
    {
        gotoxy(left-2,top + i);
        if (((i+y)%(Imp.spazio_righe+1)==0) && ((i+y)/(Imp.spazio_righe+1) < Lato_Campo(grandezza)))
            putchar((i+y)/(Imp.spazio_righe+1)+'a');
        else putchar(' ');
        putchar(179);
    }
    //poi delle ascisse
    gotoxy(left,top-2);
    for (i=0;i<width;i++)
    {
        if (((i+x)/(Imp.spazio_colonne+1)<Lato_Campo(grandezza)) && ((i+x)%(Imp.spazio_colonne+1)==0))
            putchar((i+x)/(Imp.spazio_colonne+1)+'a');
        else putchar(' ');
    }

    //riempi gli spazi vuoti
    gotoxy(left-2,top-2);
    printf(" %c",179);
    gotoxy(left-2,top-1);
    printf("%c%c",196,197);
    for (i=0;i<width;i++) putchar(196);

    //resetto i colori di default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Stampa_Menu_Gioco (partita Partita, impostazioni Imp)
{
    short_string fase;
    giocatore * puntatore;
    int i;

    //trovo il giocatore di turno
    puntatore = Partita.giocatori;
    for (i=1;i<Partita.turno; i++)  puntatore = puntatore->prossimo;
    //ricavo la fase
    if (puntatore->pedine_da_inserire == 0) strcpy(fase,"spostamento");
    else strcpy(fase,"posizionamento");
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
    //il nome della partita
    gotoxy(1,0);
    printf("%s",Partita.nome);
    //la fase
    gotoxy(3+SHORT_STRING,0);
    printf("Fase di %s                       ", fase);
    gotoxy(50,0);
    //il nome del giocatore (gli spazi sono per cancellare il vecchio nome se più lungo)
    printf("Turno: %s                        ", puntatore->nome_giocatore);
    gotoxy(10,1);
    //le istruzioni di fioco
    printf("%c,%c,%c,%c: Muovi",24,25,26,27);
    gotoxy(30,1);
    printf("INVIO: Seleziona casella/pedina");

    //le linee sottostanti
    gotoxy(0,W_TOP-1);
    Cambia_Colore(Imp.colore_linee,DEF_BACK_COLOR);
    for (i=0;i<BUFFER_X;i++)
    {
        if ((i==W_PUNTEGGIO_WIDTH && Imp.mostra_punteggio)||(i==BUFFER_X-W_PEDINE_WIDTH && Imp.mostra_pedine_fuori))
            putchar(203);
        else putchar (205);

    }

    //Resetta colori default
    Cambia_Colore(DEF_COLOR, DEF_BACK_COLOR);
}

int Scelta_Casella(casella_selezionata * cursore, partita * Partita)
{
    /***
restituisce:
0: esci
-1: sposta cursore
1: invio
     ***/
    unsigned char scelta;
    int ritorno;

    scelta = getch();
    switch (scelta)
    {
        case ARROW:
            scelta = getch();
            switch (scelta)
            {
                case UP_ARROW:
                    *cursore = Casella_Adiacente(*cursore,UP,Partita->campo);
                    break;
                case DOWN_ARROW:
                    *cursore = Casella_Adiacente(*cursore,DOWN,Partita->campo);
                    break;
                case LEFT_ARROW:
                    *cursore = Casella_Adiacente(*cursore,LEFT,Partita->campo);
                    break;
                case RIGHT_ARROW:
                    *cursore = Casella_Adiacente(*cursore,RIGHT,Partita->campo);
                    break;
            }
            ritorno = -1;
            break;
        case ENTER:
            ritorno = 1;
            break;
        case ESC:
            ritorno = 0;
            break;
        default:
            ritorno = -1;
    }
    return ritorno;
}

void Stampa_Menu_Lista(int cursore, lista_stringhe lista_nomi, int colore)
{
    int i;


    Stampa_Titolo();
    Stampa_Indicatori_Pagina(cursore/BUFFER_TESTO_Y,Numero_Stringhe(lista_nomi)/BUFFER_TESTO_Y+1,colore);
    Stampa_Cornice(colore);
    if (cursore/BUFFER_TESTO_Y>0)
    {
        for (i=0; i<BUFFER_TESTO_Y*(cursore/BUFFER_TESTO_Y);i++)
        {
            lista_nomi = lista_nomi->prossimo;
        }
    }
    i=0;
    Cambia_Colore(DEF_COLOR,colore-8);
    while (lista_nomi!=NULL && i<BUFFER_TESTO_Y)
    {
        gotoxy(TESTO_X+COL0_X,TESTO_Y+(i++));
        printf("%s",lista_nomi->stringa);
        lista_nomi = lista_nomi->prossimo;
    }

    Stampa_Cursore(cursore,colore,false);
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

int Scelta_Menu_Lista(int * cursore, int numero_voci)
{
    /*****
      valori di ritorno:
      0           esci
      invio       1-num_voci
      su          -1
      giù         -1
      destra      num_partite+1 - num_partite*2
      sinistra    num_partite*2+1 - num_partite*3
      canc        num_partite*3+1 - num_partite*4
     *****/

    unsigned char scelta;
    int ritorno=-1;

    scelta = getch();
    switch (scelta)
    {
        case ARROW:
            scelta = getch();
            switch(scelta)
            {
                case UP_ARROW:
                    *cursore=*cursore-1;
                    while (*cursore < 0) *cursore = *cursore + numero_voci;
                    break;
                case DOWN_ARROW:
                    *cursore=*cursore+1;
                    while (*cursore >= numero_voci) *cursore = *cursore - numero_voci;
                    break;
                case CANC:
                    ritorno = *cursore+1+numero_voci*3;
                    break;
                case RIGHT_ARROW:
                    ritorno = *cursore+1+numero_voci;
                    break;
                case LEFT_ARROW:
                    ritorno = *cursore+1+numero_voci*2;
                    break;
            }
            break;
        case ENTER:
            ritorno = *cursore+1;
            break;
        case ESC:
            ritorno = 0;
    }
    return ritorno;
}

int Leggi_Nomi_Partite (lista_stringhe * lista_nomi)
{
    lista_stringhe puntatore;
    FILE * file_partite;
    partita Partita;
    int posizione;

    //libera lo spazio precedentemente utilizzato
    free(*lista_nomi);

    if ((file_partite = fopen(FILE_PARTITE,"rb"))!=NULL)
    {
        posizione = ftell(file_partite);
        fseek(file_partite,0,SEEK_END);
        if (posizione != ftell(file_partite))
        {
            fseek(file_partite,0,SEEK_SET);
            while (!feof(file_partite))
            {
                fread(&Partita,1,sizeof(partita),file_partite);
                if (!feof(file_partite))
                {
                    //Aggiungi Nome a lista
                    if (*lista_nomi == NULL)
                    {
                        *lista_nomi = malloc(sizeof(elemento_stringa));
                        puntatore = *lista_nomi;
                    }
                    else
                    {
                        puntatore->prossimo = malloc(sizeof(elemento_stringa));
                        puntatore = puntatore->prossimo;
                    }
                    puntatore -> prossimo = NULL;
                    strcpy(puntatore->stringa,Partita.nome);
                    //salta giocatori e campo da file
                    fseek(file_partite,(Area_Campo(Partita.campo.grandezza))*sizeof(casella),SEEK_CUR);
                    fseek(file_partite,Partita.numero_giocatori*sizeof(giocatore),SEEK_CUR);
                }
            }

            fclose(file_partite);
        }
        else
        {
            fclose(file_partite);
            return ERR_FILE_PARTITE_VUOTO;
        }
    }
    else return ERR_FILE_PARTITE_INESISTENTE;
    return 0;
}

void Stampa_Menu_Impostazioni(int cursore, lista_stringhe lista_nomi, lista_stringhe lista_valori, int colore)
{
    int i;


    Stampa_Titolo();
    Stampa_Indicatori_Pagina(cursore/BUFFER_TESTO_Y,Numero_Stringhe(lista_nomi)/BUFFER_TESTO_Y+1,colore);
    Cambia_Colore(colore,DEF_BACK_COLOR);
    Stampa_Cornice(colore);
    if (cursore/BUFFER_TESTO_Y>0)
    {
        for (i=0; i<BUFFER_TESTO_Y*(cursore/BUFFER_TESTO_Y);i++)
        {
            lista_nomi = lista_nomi->prossimo;
            lista_valori = lista_valori->prossimo;
        }
    }
    i=0;
    Cambia_Colore(DEF_COLOR,colore-8);
    while (lista_nomi!=NULL && i<BUFFER_TESTO_Y)
    {
        gotoxy(TESTO_X+COL1_X,TESTO_Y+i);
        printf("%s",lista_nomi->stringa);
        gotoxy(TESTO_X+COL2_X,TESTO_Y+i);
        printf("%s",lista_valori->stringa);
        lista_nomi = lista_nomi->prossimo;
        lista_valori = lista_valori->prossimo;
        i++;
    }

    Stampa_Cursore(cursore,colore,false);
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Leggi_Valore_Stringa(char * valore)
{
    short_string temp;
    unsigned char c;

    //si rende visibile il cursore
    Cursore_Visibile(true);

    strcpy(temp,"");
    Stampa_Cornice_Piccola(ME_COLOR);
    Cambia_Colore(DEF_COLOR,ME_COLOR-8);
    gotoxy(MEX_X,MEX_Y);
    printf("Inserire valore.");
    gotoxy(MEX_X,MEX_Y+1);
    printf("ESC per annullare, INVIO per accettare");
    gotoxy(MEX_X,MEX_Y+2);
    do
    {
        c=getch();
        /* blocca i tasti come F1-F12 e le frecce
           che inserirebbero falsi caratteri in quanto
           vengono letti come 0 e 224 seguiti da un altro
           carattere */
        if (c==0 || c==224)
        {
            getch();
            c=0;
        }

        /* accetta i caratteri compresi tra ! e Ü */
        if (c>32 && c<155 && c!=224)
        {
            //escludi i caratteri non accettati da Windows per i percorsi file
            if (c!='\\' && c!= '/' && c!='*' && c!=':' && c!='"' && c!='?' && c!='<' && c!='>' && c!='|' && c!='.')
                if (strlen(temp)<SHORT_STRING-1)
                {
                    temp[strlen(temp)+1] = '\0';
                    temp[strlen(temp)] = c;
                    putchar(c);
                }
        }
        //Backspace
        if (c==8 && strlen(temp)>0)
        {
            temp[strlen(temp)-1] = '\0';
            printf("\b \b");
        }
    }
    while (c!=13 && c!=27); //il ciclo si chiude quando viene premuto invio o esc
    /* se è stato premuto invio viene copiata la stringa inserita */
    if (c==13 && strcmp(temp,"")) strcpy(valore,temp);

    //nascondo nuovamente il cursore
    Cursore_Visibile(false);
}


void Stampa_Schermata (buffer_campo * buffer, partita Partita, impostazioni Imp, casella_selezionata cursore_casella, casella_selezionata pedina_da_spostare)
{
    int i, j, campo_left, campo_top, campo_width, campo_height, buffer_campo_x, buffer_campo_y;

    //Setta grandezze schermata
    campo_top = W_TOP;
    campo_width = Lato_Buffer_Campo(Partita.campo.grandezza,Imp.spazio_colonne);
    campo_height = Lato_Buffer_Campo(Partita.campo.grandezza,Imp.spazio_righe);
    buffer_campo_x = BUFFER_X;
    buffer_campo_y = BUFFER_Y-W_TOP;
    if (Imp.mostra_pedine_fuori) buffer_campo_x-=W_PEDINE_WIDTH;
    if (Imp.mostra_punteggio)
    {
        buffer_campo_x -=W_PUNTEGGIO_WIDTH+1;
        campo_left = W_PUNTEGGIO_WIDTH+1;
    }
    else campo_left = 0;


    //Setta colore campo
    Cambia_Colore(0,Imp.colore_campo);
    for (i=campo_top;i<campo_top+buffer_campo_y;i++)
    {
        gotoxy(campo_left,i);
        for (j=campo_left; j<campo_left+buffer_campo_x; j++)
            putchar(' ');
    }

    //Definisci eventuale spazio per le coordinate
    if (Imp.mostra_coordinate)
    {
        campo_left+=2;
        campo_top+=2;
        buffer_campo_x-=2;
        buffer_campo_y-=2;
    }

    //Se il campo è abbastanza piccolo lo centra
    if (campo_width <= buffer_campo_x)
        campo_left += (buffer_campo_x-campo_width)/2;
    else campo_width = buffer_campo_x;
    if (campo_height <= buffer_campo_y)
        campo_top += (buffer_campo_y-campo_height)/2;
    else campo_height = buffer_campo_y;

    //Stampa varie schermate
    Stampa_Menu_Gioco(Partita,Imp);
    if (Imp.mostra_punteggio)
    {
        Stampa_Finestra_Punteggi(0,W_TOP,W_PUNTEGGIO_WIDTH,BUFFER_Y-W_TOP,Partita,Imp);
        //Stampa cornice punteggi
        Cambia_Colore(Imp.colore_linee,DEF_BACK_COLOR);
        for (i=W_TOP; i<BUFFER_Y; i++)
        {
            gotoxy(W_PUNTEGGIO_WIDTH, i);
            putchar(186);
        }
    }
    if (Imp.mostra_pedine_fuori)
    {
        Stampa_Finestra_Pedine(BUFFER_X-W_PEDINE_WIDTH,W_TOP,W_PEDINE_WIDTH,BUFFER_Y-W_TOP,Partita,Imp);
        //Stampa cornice finestra pedine
        Cambia_Colore(Imp.colore_linee,DEF_BACK_COLOR);
        for (i=W_TOP; i<BUFFER_Y; i++)
        {
            gotoxy(BUFFER_X-W_PEDINE_WIDTH, i);
            putchar(186);
        }
    }
    if (Imp.mostra_coordinate) Stampa_Coordinate(campo_left,campo_top,campo_width,campo_height,Partita.campo.grandezza,Imp,cursore_casella);
    //Stampa campo
    Stampa_Buffer_Campo(buffer,campo_top,campo_left,campo_width,campo_height,cursore_casella,pedina_da_spostare,Partita,Imp);

    //Resetta colori default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}
