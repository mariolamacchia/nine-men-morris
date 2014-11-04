/*
 * gioco.c
 *
 *  Created on: 25/lug/2013
 *      Author: utente
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <curses.h>
#include "funzioni.h"

void gotoxy(int x, int y)
{
    printf("%c[%d;%df",0x1B,y,x); 
}

void Cambia_Colore (int colore, int sfondo)
{
    printf("\033[0;%dm\033[0;%dm", 30 + colore, 40 + sfondo);
}

void Cambia_Sfondo(int colore, int colore_sfondo)
{
    int i;
    //Cambia lo sfondo
    gotoxy(0,0);
    Cambia_Colore(colore,colore_sfondo);
    for (i=0; i<BUFFER_X*BUFFER_Y; i++) putchar(BACK_CHAR);
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
}

void Inizializza_Gioco(partita * Partita, impostazioni * Imp)
{
    int i, fine_file, errore_imp;
    FILE * file_impostazioni;
    impostazioni_giocatore * puntatore;

    Cursore_Visibile(false);
    Cambia_Sfondo(BACK_COLOR,DEF_BACK_COLOR);

    //Carica impostazioni
    file_impostazioni = fopen(FILE_IMP, "rb");
    //verifica che il file esista
    if (file_impostazioni != NULL)
    {
        //verifica che il file non sia vuoto
        fseek(file_impostazioni,0,SEEK_END);
        fine_file = ftell(file_impostazioni);
        fseek(file_impostazioni,0,SEEK_SET);
        if (fine_file-ftell(file_impostazioni) != 0)
        {
            errore_imp = 0;
            //leggi impostazioni
            fread(Imp,1,sizeof(impostazioni),file_impostazioni);
            /* verifica che il dato letto corrispona
               in grandezza a quello previsto */
            if (feof(file_impostazioni) ||
                fine_file-ftell(file_impostazioni) !=
                    Imp->numero_giocatori * sizeof(impostazioni_giocatore)
                )
            {
                errore_imp = ERR_FILE_IMP_INVALID;
            }
            else
            {
                //leggi le impostazioni dei singoli giocatori
                Imp->giocatori = NULL;
                for (i=0; i<Imp->numero_giocatori; i++)
                {
                    if (Imp->giocatori == NULL)
                    {
                        Imp->giocatori =
                            malloc(sizeof(impostazioni_giocatore));
                        puntatore = Imp->giocatori;
                    }
                    else
                    {
                        puntatore->prossimo =
                            malloc(sizeof(impostazioni_giocatore));
                        puntatore = puntatore->prossimo;
                    }
                    fread(puntatore,
                          1,
                          sizeof(impostazioni_giocatore),
                          file_impostazioni);
                }
            }
        }
        else
        {
            errore_imp = ERR_FILE_IMP_VUOTO;
        }
        fclose(file_impostazioni);
    }
    else
    {
        errore_imp = ERR_FILE_IMP_INESISTENTE;
    }
    /* nel caso siano stati riscontrati errori
       si applicano le impostazioni predefinite */
    if (errore_imp)
    {
        Gestione_Errori(errore_imp);
        file_impostazioni = fopen(FILE_IMP,"wb");
        Impostazioni_Predefinite(Imp);
        fwrite(Imp,1,sizeof(impostazioni),file_impostazioni);
        puntatore = Imp->giocatori;
        for (i=0;i<Imp->numero_giocatori;i++)
        {
            fwrite(puntatore,
                   1,
                   sizeof(impostazioni_giocatore),
                   file_impostazioni);
            puntatore=puntatore->prossimo;
        }
        fclose(file_impostazioni);
    }


    //Segna partita come non iniziata
    Partita->iniziata = false;
    Partita->giocatori = NULL;
}

void Cursore_Visibile (booleano visibile)
{
}

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

void Riproduci_Suono(int suono)
{
    /*
    switch (suono)
    {
        case 0:
            Beep(700,100);
            Beep(520,100);
            break;
        case 1:
            Beep(520,100);
            Beep(700,100);
            break;
        case 2:
            Beep(520,100);
            break;
        case 3:
            Beep(700,100);
            Beep(700,100);
            break;
        case 4:
            Beep(700,100);
            Beep(700,100);
            Beep(700,100);
            break;
        case 5:
            Beep(520,70);
            Beep(700,70);
            Beep(520,70);
            break;
        case 6:
            Beep(660,100);
            Beep(700,100);
            break;
        case 7:
            Beep(700,100);
            Beep(660,100);
            break;
        case 8:
            Beep(520,30);
            Beep(580,30);
            Beep(660,30);
            Beep(700,30);
            Beep(780,30);
            break;
        case 9:
            Beep(780,30);
            Beep(700,30);
            Beep(660,30);
            Beep(580,30);
            Beep(520,30);
            break;
        case 10:
            Beep(660,200);
            Beep(520,200);
            Beep(390,200);
            Beep(660,400);
            break;
        case 11:
            Beep(660,100);
            Beep(620,100);
            Beep(660,100);
            Beep(780,100);
            Sleep(200);
            Beep(880,100);
            Beep(780,100);
            Sleep(100);
            Beep(660,400);
            break;
        case 12:
            Beep(520,100);
            Beep(520,100);
            Beep(520,100);
            Sleep(200);
            Beep(1040,200);
            Beep(880,300);
            break;
        case 13:
            Beep(520,300);
            Beep(495,300);
            Beep(470,300);
            Beep(440,600);
            break;
        case 14:
            Beep(520,100);
            Beep(580,100);
            Beep(660,100);
            Beep(780,200);
            Sleep(200);
            Beep(660,100);
            Beep(780,400);
            break;
        case 15:
            Beep(700,100);
            Sleep(100);
            Beep(520,100);
            Beep(520,100);
            Beep(580,100);
            Sleep(200);
            Beep(520,200);
            Sleep(200);
            Beep(660,200);
            Beep(700,200);
            break;
    }
    */
}

int Numero_Stringhe(lista_stringhe lista_elementi)
{
    int i=0;
    while (lista_elementi!=NULL)
    {
        lista_elementi = lista_elementi ->prossimo;
        i++;
    }
    return i;
}

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

int Scelta_Menu(int * cursore)
{
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
                    while (*cursore < 0) *cursore = *cursore + MP_NCAMPI;
                    break;
                case DOWN_ARROW:
                    *cursore=*cursore+1;
                    while (*cursore >= MP_NCAMPI)
                    {
                        *cursore = *cursore - MP_NCAMPI;
                    }
                    break;
            }
            break;
        case ENTER:
            if (*cursore == MP_NCAMPI-1) ritorno = 0;
            else ritorno = *cursore+1;
            break;
        case 'n':
            ritorno = MP_VNUOVA;
            break;
        case 'N':
            ritorno = MP_VNUOVA;
            break;
        case 'c':
            ritorno = MP_VCARICA;
            break;
        case 'C':
            ritorno = MP_VCARICA;
            break;
        case 's':
            ritorno = MP_VSALVA;
            break;
        case 'S':
            ritorno = MP_VSALVA;
            break;
        case 'r':
            ritorno = MP_VRECORD;
            break;
        case 'R':
            ritorno = MP_VRECORD;
            break;
        case 'i':
            ritorno = MP_VIMP;
            break;
        case 'I':
            ritorno = MP_VIMP;
            break;
        case 'a':
            ritorno = MP_VAIUTO;
            break;
        case 'A':
            ritorno = MP_VAIUTO;
            break;
        case ESC:
            ritorno = 0;
            break;
    }
    return ritorno;
}



int Nuova_Partita(impostazioni * Imp, partita * Partita)
{
    int errore, esito;

    //controlla che le impostazioni siano valide
    if ((errore = Controlla_Impostazioni(*Imp)))
    {
        Impostazioni_Predefinite(Imp);
        Gestione_Errori(errore);
    }

    Inizializza_Partita(*Imp,Partita);

    esito = Gioca(Partita,*Imp);

    return esito;
}

int Controlla_Impostazioni (impostazioni Imp)
{
    int errore=0, i;
    int err_numero_giocatori = 0,
        err_nome_partita = 0,
        err_grandezza_campo = 0,
        err_numero_pedine = 0,
        err_giocatore_iniziale = 0,
        err_colori = 0,
        err_spazi = 0;
    float max_pedine;
    impostazioni_giocatore * giocatore;

    //controlla tutte le impostazioni
    if (!strcmp(Imp.nome_partita, "")) err_nome_partita = 1;
    if (Imp.numero_giocatori < 2 ||
        Imp.numero_giocatori > Perimetro_Quadrato(MAX_GAME_SIZE))
    {
        err_numero_giocatori = 1;
    }
    if (Perimetro_Quadrato(Imp.grandezza_campo) < Imp.numero_giocatori ||
        Imp.grandezza_campo<3 ||
        Imp.grandezza_campo > MAX_GAME_SIZE)
    {
        err_grandezza_campo = 1;
    }
    max_pedine = Imp.grandezza_campo * Perimetro_Quadrato(Imp.grandezza_campo);
    max_pedine /= Imp.numero_giocatori;
    if (Imp.numero_pedine > max_pedine ||
         Imp.numero_pedine < Imp.grandezza_campo)
    {
        err_numero_pedine = 1;
    }
    if (Imp.giocatore_iniziale < 0 ||
        Imp.giocatore_iniziale > Imp.numero_giocatori)
    {
        err_giocatore_iniziale = 1;
    }
    if ((Imp.colore_campo < 0  || Imp.colore_campo > 15) ||
        (Imp.colore_linee < 0 || Imp.colore_linee > 15) ||
        (Imp.colore_selezione < 0 || Imp.colore_selezione > 15))
    {
        err_colori = 1;
    }
    if ((Imp.suoni == true) &&
         ((Imp.suono_eliminazione < 0 || Imp.suono_eliminazione > 15) ||
          (Imp.suono_inserimento < 0 || Imp.suono_inserimento > 15) ||
          (Imp.suono_mulino < 0 || Imp.suono_mulino > 15) ||
          (Imp.suono_sconfitta < 0 || Imp.suono_sconfitta > 15) ||
          (Imp.suono_spostamento < 0 || Imp.suono_spostamento > 15) ||
          (Imp.suono_vittoria < 0 || Imp.suono_vittoria > 15)))
    {
        err_suoni = 1;
    }
    if ((Imp.spazio_colonne < 0 || Imp.spazio_colonne > MAX_SPAZIO_COLONNE) ||
        (Imp.spazio_righe < 0 || Imp.spazio_righe > MAX_SPAZIO_RIGHE))
        err_spazi = 1;
    {
        err_spazi = 1
    }
    if (err_numero_giocatori ||
        err_nome_partita ||
        err_grandezza_campo ||
        err_numero_pedine ||
        err_giocatore_iniziale ||
        err_colori ||
        err_spazi)
    {
        errore = ERR_IMP_INVALID;
    }

    //controlla le impostazioni per ogni giocatore e il numero di giocatori
    if (!errore)
    {
        i=0;
        giocatore = Imp.giocatori;
    }
    while (i<Imp.numero_giocatori && giocatore!= NULL && !errore)
    {
        if (!strcmp(giocatore->nome_giocatore,"") ||
            (giocatore->tipo_pedine < 0 || giocatore->tipo_pedine > 15) ||
            (giocatore->colore_pedine < 0 || giocatore->colore_pedine > 15))
            errore = ERR_IMP_INVALID;
        i++;
        giocatore = giocatore->prossimo;
    }
    //controlla numero giocatori
    if (!errore)
    {
        if (i<Imp.numero_giocatori || giocatore != NULL)
        {
            errore = ERR_IMP_INVALID;
        }
    }

    return errore;
}


void Inizializza_Partita(impostazioni Imp, partita * Partita)
{
    lista_giocatori puntatore_gioc;
    lista_impostazioni_giocatori puntatore_imp;

    //carica impostazioni
    Partita->campo.grandezza =  Imp.grandezza_campo;
    Crea_Campo(&Partita->campo, Imp.grandezza_campo);
    Partita->iniziata = true;
    Partita->mulino = false;
    if (Imp.giocatore_iniziale) Partita->turno = Imp.giocatore_iniziale;
    else Partita->turno = rand()%Imp.numero_giocatori+1;
    strcpy(Partita->nome,Imp.nome_partita);
    Partita->numero_giocatori = Imp.numero_giocatori;
    Partita->numero_pedine = Imp.numero_pedine;
    puntatore_imp = Imp.giocatori;
    Partita->giocatori = malloc(sizeof(giocatore));
    puntatore_gioc = Partita->giocatori;
    while (puntatore_imp!=NULL)
    {
        puntatore_gioc->in_gioco = true;
        puntatore_gioc->punteggio = 0;
        puntatore_gioc->colore_pedine = puntatore_imp->colore_pedine;
        strcpy(puntatore_gioc->nome_giocatore,puntatore_imp->nome_giocatore);
        puntatore_gioc->tipo_pedine = puntatore_imp->tipo_pedine;
        puntatore_gioc->pedine_in_gioco = 0;
        puntatore_gioc->pedine_da_inserire = Imp.numero_pedine;
        if (puntatore_imp->prossimo != NULL)
        {
            puntatore_gioc->prossimo = malloc(sizeof(giocatore));
            puntatore_gioc = puntatore_gioc->prossimo;
        }
        else puntatore_gioc->prossimo = NULL;
        puntatore_imp = puntatore_imp->prossimo;
    }
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
        *(Campo->caselle + ) = 0;

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

booleano Mulino (casella_selezionata Casella, campo Campo)
{
    booleano mulino=true;
    int pedine=1;
    casella_selezionata adiacente,controllo;
    //controlla a sx
    controllo = Casella;
    adiacente = Casella_Adiacente(Casella,LEFT,Campo);
    while (Stessa_Linea(adiacente,Casella,Campo) && mulino && !Stessa_Casella(controllo,adiacente))
    {
        if (Valore_Casella(adiacente,Campo)!=Valore_Casella(Casella,Campo)) mulino = false;
        else
        {
            controllo = adiacente;
            adiacente = Casella_Adiacente(adiacente,LEFT,Campo);
            pedine++;
        }
    }
    //dx
    if (mulino)
    {
        controllo = Casella;
        adiacente = Casella_Adiacente(Casella,RIGHT,Campo);
    }
    while (Stessa_Linea(adiacente,Casella,Campo) && mulino && !Stessa_Casella(controllo,adiacente))
    {
        if (Valore_Casella(adiacente,Campo)!=Valore_Casella(Casella,Campo)) mulino = false;
        else
        {
            controllo = adiacente;
            adiacente = Casella_Adiacente(adiacente,RIGHT,Campo);
            pedine++;
        }
    }
    if (!mulino || pedine<Campo.grandezza)
    {
        mulino = true;
        pedine=1;
        //su
        controllo = Casella;
        adiacente = Casella_Adiacente(Casella,UP,Campo);
        while (Stessa_Linea(Casella,adiacente,Campo) && mulino && !Stessa_Casella(controllo,adiacente))
        {
            if (Valore_Casella(adiacente,Campo)!=Valore_Casella(Casella,Campo)) mulino = false;
            else
            {
                controllo = adiacente;
                adiacente = Casella_Adiacente(adiacente, UP, Campo);
                pedine++;
            }
        }
        //giù
        if (mulino)
        {
            adiacente = Casella_Adiacente(Casella,DOWN,Campo);
            controllo = Casella;
        }
        while (Stessa_Linea(Casella,adiacente,Campo) && mulino && !Stessa_Casella(controllo,adiacente))
        {
            if (Valore_Casella(adiacente,Campo)!=Valore_Casella(Casella,Campo)) mulino = false;
            else
            {
                controllo = adiacente;
                adiacente = Casella_Adiacente(adiacente, DOWN, Campo);
                pedine++;
            }
        }
    }
    if (mulino && pedine==Campo.grandezza)
    {
        return true;
    }
    else return false;
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

int Inserisci_Pedina (casella_selezionata Casella, partita * Partita)
{
    int valore, errore, i;
    valore = Valore_Casella(Casella,Partita->campo);
    giocatore * puntatore;

    switch (valore)
    {
        case -1:
            errore = ERR_CASELLA_INESISTENTE;
            break;
        case 0:
            Setta_Valore(Casella,Partita->campo,Partita->turno);
            i=1;
            puntatore = Partita->giocatori;
            while (i<Partita->turno)
            {
                puntatore = puntatore->prossimo;
                i++;
            }
            puntatore->pedine_da_inserire--;
            puntatore->pedine_in_gioco++;
            errore = 0;
            break;
        default:
            errore = ERR_CASELLA_PIENA;
            break;
    }

    return errore;
}

int Sposta_Pedina (casella_selezionata Sorgente, casella_selezionata Destinazione, partita * Partita)
{
    casella valore;
    giocatore * puntatore;
    int i;

    puntatore = Partita->giocatori;
    for (i=1; i<Partita->turno; i++)
    {
        puntatore = puntatore->prossimo;
    }

    if ((valore = Valore_Casella(Destinazione,Partita->campo))==0)
    {
        if (Valore_Casella(Sorgente,Partita->campo)==Partita->turno)
        {
            if (Adiacente(Sorgente,Destinazione,Partita->campo)||puntatore->pedine_in_gioco <= Partita->campo.grandezza)
            {
                Setta_Valore(Sorgente,Partita->campo,0);
                Setta_Valore(Destinazione,Partita->campo,Partita->turno);
            }
            else return ERR_CASELLE_NON_ADIACENTI;
        }
        else return ERR_PEDINA_AVVERSARIA;
    }
    else
        if (valore>0) return ERR_CASELLA_PIENA;
        else return ERR_CASELLA_INESISTENTE;
    return 0;
}

int Elimina_Pedina(casella_selezionata Casella, partita * Partita)
{
    int valore, i;
    giocatore * puntatore;

    if ((valore = Valore_Casella(Casella,Partita->campo))!=0)
    {
        if (valore != Partita->turno)
        {
            puntatore = Partita->giocatori;
            for (i=1;i<valore;i++)
            {
                puntatore = puntatore->prossimo;
            }
            puntatore->pedine_in_gioco--;
            Setta_Valore(Casella,Partita->campo,0);
        }
        else return ERR_PEDINA_GIOCATORE_TURNO;
    }
    else return ERR_CASELLA_VUOTA;
    return 0;
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

giocatore * Prossimo_Turno(partita * Partita)
{
    int i;
    giocatore * temp;

    Partita->turno++;
    if (Partita->turno > Partita->numero_giocatori)
        Partita->turno = 1;
    temp = Partita->giocatori;
    for (i=1;i<Partita->turno;i++)
    {
        temp = temp->prossimo;
    }
    return temp;
}

int Gioca(partita * Partita, impostazioni Imp)
{
    giocatore * puntatore;
    int esito;

    Cambia_Sfondo(BACK_COLOR,DEF_BACK_COLOR);

    if (!(esito = Fase_Posizionamento(Partita,Imp)))
    {
        if (!(esito = Fase_Spostamento(Partita,Imp)))
        {
            //trova il vincitore
            puntatore = Partita->giocatori;
            while (puntatore != NULL && !puntatore->in_gioco)
                puntatore = puntatore->prossimo;
            if (puntatore != NULL)
            {
                if (Imp.suoni) Riproduci_Suono(Imp.suono_vittoria);
                Vittoria(puntatore->nome_giocatore,puntatore->punteggio);
            }
            else
            {
                if (Imp.suoni) Riproduci_Suono(Imp.suono_sconfitta);
                Messaggio("Non c'\x82 nessun vincitore.",false);
            }
        }
    }

    Cambia_Sfondo(BACK_COLOR,DEF_BACK_COLOR);
    return esito;
}

int Fase_Posizionamento (partita * Partita, impostazioni Imp)
{
    ///restituisce 0 se premuto esc, altrimenti 1
    casella_selezionata cursore;
    booleano ok, esci, elimina;
    giocatore * giocatore_di_turno;
    int scelta,i,j,valore;
    buffer_campo * Campo;
    time_t start, end;

    giocatore_di_turno = Partita->giocatori;
    for (i=1; i<Partita->turno;i++)
        giocatore_di_turno = giocatore_di_turno->prossimo;
    cursore = Casella_Selezionata(0,0);
    ok=false;
    esci = false;
    Crea_Buffer_Campo(&Campo,Partita->campo,Imp.spazio_righe,Imp.spazio_colonne);

    while ((giocatore_di_turno->pedine_da_inserire>0 ||Partita->mulino) && !esci)
    {
        while (!ok && !esci)
        {
            Stampa_Schermata(Campo,*Partita,Imp,cursore,cursore);
            //aspetta che l'utente prema un tasto e modifica il suo punteggio in base al tempo impiegato
            start=clock();
            scelta = Scelta_Casella(&cursore,Partita);
            end=clock();
            giocatore_di_turno->punteggio+=(float)(end-start)/CLOCKS_PER_SEC;
            //se preme invio
            if (scelta==1)
            {
                //nel caso non ci si trovi nella sottofase di mulino controlla se si può inserire la pedina
                if (!Partita->mulino)
                {
                    if (Valore_Casella(cursore,Partita->campo)!=0)
                        Gestione_Errori(ERR_CASELLA_PIENA);
                    else
                    {
                        //inserisce la pedina
                        Inserisci_Pedina(cursore,Partita);
                        ok=true;
                        //controlla se si è formato un mulino
                        if (Mulino(cursore,Partita->campo))
                        {
                            //riproduce il suono e passa alla sottofase di mulino
                            if (Imp.suoni) Riproduci_Suono(Imp.suono_mulino);
                            Partita->mulino=true;
                        }
                        else
                        {
                            //riproduce il suono e passa il turno
                            if (Imp.suoni) Riproduci_Suono(Imp.suono_inserimento);
                            giocatore_di_turno = Prossimo_Turno(Partita);
                        }
                        Crea_Buffer_Campo(&Campo,Partita->campo,Imp.spazio_righe,Imp.spazio_colonne);
                    }
                }
                //nel caso si è in una sottofase di mulino si verifica che si può eliminare la pedina
                else
                {
                    valore = Valore_Casella(cursore,Partita->campo);
                    if (valore == 0)
                        Gestione_Errori(ERR_CASELLA_VUOTA);
                    else if (valore == Partita->turno)
                        Gestione_Errori(ERR_PEDINA_GIOCATORE_TURNO);
                    else
                    {
                        //controlla se la pedina selezionata compone un mulino
                        if (Mulino(cursore,Partita->campo))
                        {
                            //se la pedina è in un mulino controlla che non ce ne siano altre che non ne compongano
                            elimina = true;
                            for (i=0;i<Lato_Campo(Partita->campo.grandezza) && elimina;i++)
                                for (j=0;j<Lato_Campo(Partita->campo.grandezza) && elimina; j++)
                                {
                                    if (Valore_Casella(Casella_Selezionata(j,i),Partita->campo) == valore)
                                        if (!Mulino(Casella_Selezionata(j,i),Partita->campo))
                                            elimina = false;
                                }
                        }
                        else elimina = true;

                        if (elimina)
                        {
                            //elimina la pedina, passa il turno e riproduce il suono
                            Elimina_Pedina(cursore,Partita);
                            if (Imp.suoni) Riproduci_Suono(Imp.suono_eliminazione);
                            ok=true;
                            giocatore_di_turno = Prossimo_Turno(Partita);
                            Partita->mulino = false;
                            Crea_Buffer_Campo(&Campo,Partita->campo,Imp.spazio_righe,Imp.spazio_colonne);
                        }
                        else Gestione_Errori(ERR_MULINO);
                    }
                }
            }
            //se si preme esc esce dopo aver chiesto conferma
            else if (scelta==0)
                if (Messaggio("Sicuro di voler tornare al menu principale?",true)) esci = true;
        }
        ok = false;
    }
    if (esci) return ERR_INTERROTTA;
    else return 0;
}

int Fase_Spostamento (partita * Partita, impostazioni Imp)
{
    ///restituisce 0 se premuto esc, altrimenti 1
    casella_selezionata cursore, pedina_da_spostare;
    booleano ok, esci, prima_casella_scelta, elimina;
    giocatore * giocatore_di_turno, *puntatore;
    int scelta,i,j;
    buffer_campo * Campo;
    time_t start,end;
    long_string messaggio;

    //controlla tutti i giocatori eliminati
    puntatore = Partita->giocatori;
    i=1;
    //controlla i giocatori eliminati
    while (puntatore != NULL)
    {
        if (Giocatore_Eliminato(*Partita,i++) && Imp.suoni)
        {
            Riproduci_Suono(Imp.suono_sconfitta);
            strcpy(messaggio, puntatore->nome_giocatore);
            strcat(messaggio, " \x82 stato eliminato.");
            Messaggio(messaggio,false);
            puntatore->in_gioco = false;
        }
        puntatore = puntatore->prossimo;
    }

    giocatore_di_turno = Partita->giocatori;
    for (i=1; i<Partita->turno;i++)
        giocatore_di_turno = giocatore_di_turno->prossimo;
    cursore = Casella_Selezionata(0,0);
    ok=false;
    prima_casella_scelta = false;
    esci = false;
    Crea_Buffer_Campo(&Campo,Partita->campo,Imp.spazio_righe,Imp.spazio_colonne);

    while (!Fine_Partita(*Partita) && !esci)
    {
        while (!ok && !esci)
        {
            if (prima_casella_scelta) Stampa_Schermata(Campo,*Partita,Imp,cursore,pedina_da_spostare);
            else Stampa_Schermata(Campo,*Partita,Imp,cursore,cursore);
            //aspetta l'input dell'utente e somma il tempo impiegato al punteggio
            start=clock();
            scelta = Scelta_Casella(&cursore,Partita);
            end=clock();
            giocatore_di_turno->punteggio+=(float)(end-start)/CLOCKS_PER_SEC;
            //se si preme esc
            if (scelta == 0)
            {
                // se era stata selezionata una pedina, la deseleziona
                if (prima_casella_scelta)
                {
                    prima_casella_scelta = false;
                }
                //altrimenti esce dopo aver chiesto conferma
                else if (Messaggio("Sicuro di voler tornare al menu principale? ",true)) esci = true;
            }
            //se si preme invio
            else if (scelta == 1)
            {
                //se si è nella sottofase di mulino verifica che la pedina si possa eliminare
                if (Partita->mulino)
                {
                    if (Valore_Casella(cursore,Partita->campo)==0)
                        Gestione_Errori(ERR_CASELLA_VUOTA);
                    else if (Valore_Casella(cursore,Partita->campo)==Partita->turno)
                        Gestione_Errori(ERR_PEDINA_GIOCATORE_TURNO);
                    else
                    {
                        //controlla se la pedina selezionata compone un mulino
                        if (Mulino(cursore,Partita->campo))
                        {
                            //se la pedina è in un mulino controlla che non ce ne siano altre che non ne compongano
                            elimina = true;
                            for (i=0;i<Lato_Campo(Partita->campo.grandezza) && elimina;i++)
                                for (j=0;j<Lato_Campo(Partita->campo.grandezza) && elimina; j++)
                                {
                                    if (Valore_Casella(Casella_Selezionata(j,i),Partita->campo) == Valore_Casella(cursore,Partita->campo))
                                        if (!Mulino(Casella_Selezionata(j,i),Partita->campo))
                                            elimina = false;
                                }
                        }
                        else elimina = true;

                        if (elimina)
                        {
                            //la elimina, riproduce il suono e passa il turno
                            Elimina_Pedina(cursore,Partita);
                            if (Imp.suoni) Riproduci_Suono(Imp.suono_eliminazione);
                            ok=true;
                            Partita->mulino = false;
                            giocatore_di_turno = Prossimo_Turno(Partita);
                            Crea_Buffer_Campo(&Campo,Partita->campo,Imp.spazio_righe,Imp.spazio_colonne);
                        }
                        else Gestione_Errori(ERR_MULINO);
                    }
                }
                //se non è stata selezionata nessuna pedina da spostare, verifica che questa sia spostabile e la seleziona
                else if (!prima_casella_scelta)
                {
                    if (Valore_Casella(cursore,Partita->campo)==0)
                        Gestione_Errori(ERR_CASELLA_VUOTA);
                    else if (Valore_Casella(cursore,Partita->campo)!=Partita->turno)
                        Gestione_Errori(ERR_PEDINA_AVVERSARIA);
                    else
                    {
                        pedina_da_spostare = cursore;
                        prima_casella_scelta = true;
                        ok = true;
                    }
                }
                //se era stata selezionata già una pedina, verifica che la destinazione sia valida e la sposta
                else
                {
                    if (Stessa_Casella(cursore,pedina_da_spostare)) prima_casella_scelta = false;
                    else if (Valore_Casella(cursore,Partita->campo)!=0)
                        Gestione_Errori(ERR_CASELLA_PIENA);
                    else if (!Adiacente(cursore,pedina_da_spostare,Partita->campo)&&giocatore_di_turno->pedine_in_gioco>Partita->campo.grandezza)
                        Gestione_Errori(ERR_CASELLE_NON_ADIACENTI);
                    else
                    {
                        Sposta_Pedina(pedina_da_spostare,cursore,Partita);
                        if (Mulino(cursore,Partita->campo))
                        {
                            Partita->mulino = true;
                            if (Imp.suoni) Riproduci_Suono(Imp.suono_mulino);
                        }
                        else
                        {
                            giocatore_di_turno = Prossimo_Turno(Partita);
                            if (Imp.suoni) Riproduci_Suono(Imp.suono_spostamento);
                        }
                        ok = true;
                        prima_casella_scelta = false;
                        Crea_Buffer_Campo(&Campo,Partita->campo,Imp.spazio_righe,Imp.spazio_colonne);
                    }
                }
            }
        }
        //passa il turno e controlla se il nuovo giocatore è stato eliminato
        while (Giocatore_Eliminato(*Partita,Partita->turno))
        {
            if (Imp.suoni) Riproduci_Suono(Imp.suono_sconfitta);
            strcpy(messaggio, giocatore_di_turno->nome_giocatore);
            strcat(messaggio, " \x82 stato eliminato.");
            Messaggio(messaggio,false);
            giocatore_di_turno->in_gioco = false;
            Prossimo_Turno(Partita);
        }
        ok = false;
    }
    if (esci) return ERR_INTERROTTA;
    else return 0;
}

int Vittoria (short_string Nome, float Punteggio)
{
    FILE * file_record;
    int puntatore,j,i;
    short_string nomi[MR_MAX];
    float punteggi[MR_MAX];
    int errore = 0;
    long_string messaggio;

    //Scrivi messaggio vittoria
    strcpy(messaggio, "Il vincitore \x82 ");
    strcat(messaggio, Nome);
    strcat(messaggio, "!!!\n");

    //controlla che il file esista
    if ((file_record = fopen(FILE_RECORD,"r"))!=NULL)
    {        puntatore = ftell(file_record);
        fseek(file_record,0,SEEK_END);
        //controlla se il file è vuoto
        if (ftell(file_record)-puntatore)
        {
            fseek(file_record,0,SEEK_SET);
            //salva tutti i record in un array
            i=0;
            while (i<MR_MAX && !feof(file_record))
            {
                fscanf(file_record,"%s",nomi[i]);
                if (!feof(file_record))
                {
                    fscanf(file_record,"%f",&punteggi[i]);
                    i++;
                }
            }
            /*se i recod sono meno di 10 o se l'ultimo punteggio
              è maggiore del punteggio del vincitore, quest'ultimo
              verrà inserito (il punteggio migliore è il più basso) */
            if (i<MR_MAX || punteggi[i-1]>=Punteggio)
            {
                if (i<MR_MAX) j=i;
                else j=MR_MAX-1;
                while (punteggi[j-1]>Punteggio)
                {
                    punteggi[j]=punteggi[j-1];
                    strcpy(nomi[j],nomi[j-1]);
                    j--;
                }
                punteggi[j]=Punteggio;
                strcpy(nomi[j],Nome);
                fclose(file_record);
                //riscrivi file record
                fopen(FILE_RECORD,"w");
                for (j=0;j<=i && j<MR_MAX;j++)
                {
                    fprintf(file_record,"%s %.2f\n",nomi[j],punteggi[j]);
                }
                fclose(file_record);

                //stampa messaggio vittoria
                strcat(messaggio, "E' stato raggiunto un nuovo record!");
                Messaggio(messaggio,false);

                //manda a record
                Gestione_Errori(Record());
            }
            else
            {
                fclose(file_record);

                //stampa errore
                strcat(messaggio, "Non \x82 stato raggiunto nessun record.");
                Messaggio(messaggio, false);
            }
        }
        else
        {
            errore = ERR_FILE_REC_VUOTO;
            fclose(file_record);
        }
    }
    else errore = ERR_FILE_REC_INESISTENTE;

    if (errore)
    {        file_record = fopen(FILE_RECORD,"w");
        fprintf(file_record,"%s %.2f", Nome, Punteggio);
        fclose(file_record);

        //stampa messaggio vittoria
        strcat(messaggio, "E' stato raggiunto un nuovo record!");
        Messaggio(messaggio,false);

        //apri la schermata record
        Gestione_Errori(Record());
    }
    return errore;
}

booleano Pedina_Bloccata(casella_selezionata Casella, campo Campo)
{
    booleano bloccata = true;
    casella_selezionata vicina;

    vicina = Casella_Adiacente(Casella,UP,Campo);
    if (Adiacente(vicina, Casella, Campo) && Valore_Casella(vicina,Campo)==0) bloccata = false;
    vicina = Casella_Adiacente(Casella,DOWN,Campo);
    if (Adiacente(vicina, Casella, Campo) && Valore_Casella(vicina,Campo)==0) bloccata = false;
    vicina = Casella_Adiacente(Casella,LEFT,Campo);
    if (Adiacente(vicina, Casella, Campo) && Valore_Casella(vicina,Campo)==0) bloccata = false;
    vicina = Casella_Adiacente(Casella,RIGHT,Campo);
    if (Adiacente(vicina, Casella, Campo) && Valore_Casella(vicina,Campo)==0) bloccata = false;

    return bloccata;
}

booleano Giocatore_Eliminato(partita Partita, int giocatore)
{
    int j,i;
    booleano eliminato;
    casella_selezionata casella;

    for (i=1; i<giocatore;i++)
    {
        Partita.giocatori = Partita.giocatori->prossimo;
    }
    //se le pedine sono meno del minimo è stato eliminato
    if (Partita.giocatori->pedine_in_gioco < Partita.campo.grandezza) eliminato = true;
    else
    {
        //altrimenti se tutte le pedine sono bloccate è eliminato
        eliminato = true;
        for (i=0; i<Lato_Campo(Partita.campo.grandezza) && eliminato; i++)
            for (j=0; j<Lato_Campo(Partita.campo.grandezza) && eliminato;j++)
            {
                if ((Valore_Casella((casella = Casella_Selezionata(j,i)),Partita.campo))==giocatore)
                {
                    if (!Pedina_Bloccata(casella,Partita.campo)) eliminato = false;
                }
            }
    }
    return eliminato;
}

booleano Fine_Partita (partita Partita)
{
    int i=0,j=1;
    giocatore * puntatore;

    puntatore = Partita.giocatori;

    //se c'è più di un giocatore in gioco non è finita
    while (puntatore != NULL && i<2)
    {
        if (puntatore->in_gioco) i++;
        puntatore = puntatore->prossimo;
        j++;
    }
    if (i>1) return false;
    else return true;
}


int Carica_Partita(partita * Partita, impostazioni Imp)
{
    FILE * file_partite;
    int errore,cursore = 0, scelta, numero_nomi, i;
    booleano esci=false;
    lista_stringhe lista_nomi = NULL;
    partita partita_temp;
    lista_giocatori punt_gioc;


    lista_nomi = NULL;
    if (!(errore = Leggi_Nomi_Partite(&lista_nomi)))
    {
        while (!esci)
        {
            numero_nomi = Numero_Stringhe(lista_nomi);
            Stampa_Menu_Lista(cursore,lista_nomi,MC_COLOR);
            Stampa_Titolo_Menu("CARICA PARTITA",MC_COLOR);
            Stampa_Indicazioni("Premere le frecce su e gi\x97 per muoversi tra le\npartite, INVIO per caricare la partita nello spazio\nselezionato e CANC per eliminare la partita indicata\nPremere Esc per tornare al menu principale.");
            scelta = Scelta_Menu_Lista(&cursore,numero_nomi);
            if (scelta == 0)
            {
                esci = true;
                //cencella indicatori pagina
                Stampa_Indicatori_Pagina(0,0,0);
            }
            else if (scelta > 0 && scelta <= numero_nomi)
            {
                if ((file_partite = fopen(FILE_PARTITE,"rb"))!=NULL)
                {
                    for (i=1; i<scelta; i++)
                    {
                        fread(&partita_temp,1,sizeof(partita),file_partite);
                        fseek(file_partite,sizeof(casella)*Area_Campo(partita_temp.campo.grandezza),SEEK_CUR);
                        fseek(file_partite,sizeof(giocatore)*partita_temp.numero_giocatori,SEEK_CUR);
                    }
                    fread(Partita, 1, sizeof(partita),file_partite);
                    //carica campo
                    Partita->campo.caselle = malloc(sizeof(casella)*Area_Campo(Partita->campo.grandezza));
                    fread(Partita->campo.caselle, sizeof(casella), Area_Campo(Partita->campo.grandezza), file_partite);
                    //carica giocatori
                    Partita->giocatori = NULL;
                    for (i=0; i<Partita->numero_giocatori; i++)
                    {
                        if (Partita->giocatori == NULL)
                        {
                            Partita->giocatori = malloc(sizeof(giocatore));
                            punt_gioc = Partita->giocatori;
                        }
                        else
                        {
                            punt_gioc->prossimo = malloc(sizeof(giocatore));
                            punt_gioc = punt_gioc->prossimo;
                        }
                        fread(punt_gioc,1,sizeof(giocatore),file_partite);
                    }
                    fclose(file_partite);
                    Stampa_Indicazioni("Partita caricata con successo!\nPremere un tasto per proseguire con il gioco.");
                    getch();
                    Gioca(Partita,Imp);
                    esci = true;
                }
                else
                {
                    return ERR_FILE_PARTITE_INESISTENTE;
                }
            }
        }
    }
    return errore;
}

int Salva_Partita(partita * Partita)
{
    FILE * file_partite;
    int i,cursore=0,scelta, numero_nomi, posizione_file, bytes;
    lista_stringhe lista_nomi, punt_nomi;
    booleano esci =false, cancella;
    giocatore * puntgioc;
    void * backup, * puntbackup;
    partita temp_partita;
    elemento_stringa nuovo_slot;


    lista_nomi=NULL;

    if (Partita->iniziata)
    {
        Leggi_Nomi_Partite(&lista_nomi);
        //aggiungi campo "nuovo slot"
        strcpy(nuovo_slot.stringa,"<Nuovo Slot>");
        nuovo_slot.prossimo=NULL;

        if (lista_nomi!=NULL)
        {
            punt_nomi=lista_nomi;
            while (punt_nomi->prossimo!=NULL)
            {
                punt_nomi = punt_nomi->prossimo;
            }
            punt_nomi->prossimo = &nuovo_slot;
        }
        else lista_nomi = &nuovo_slot;
        //
        numero_nomi = Numero_Stringhe(lista_nomi);

        //cancella lo sfondo
        Cambia_Sfondo(DEF_COLOR,DEF_BACK_COLOR);

        while (!esci)
        {
            Stampa_Menu_Lista(cursore,lista_nomi,MS_COLOR);
            Stampa_Indicazioni("Premere le frecce su e gi\x97 per muoversi tra le\npartite, INVIO per salvare la partita nello spazio\nselezionato e CANC per eliminare la partita indicata\nPremere Esc per tornare al menu principale.");
            Stampa_Titolo_Menu("SALVA PARTITA",MS_COLOR);

            scelta = Scelta_Menu_Lista(&cursore,numero_nomi);
            if (scelta==0) esci = true;
            else if (scelta == numero_nomi)
            {
                /**Salva nuova partita**/
                file_partite = fopen(FILE_PARTITE,"ab");
                fwrite(Partita,1,sizeof(partita),file_partite);
                fwrite(Partita->campo.caselle,sizeof(casella),Lato_Campo(Partita->campo.grandezza)*Lato_Campo(Partita->campo.grandezza),file_partite);
                puntgioc = Partita->giocatori;
                while (puntgioc != NULL)
                {
                    fwrite(puntgioc,1,sizeof(giocatore),file_partite);
                    puntgioc = puntgioc->prossimo;
                }
                fclose(file_partite);

                lista_nomi = NULL;
                Leggi_Nomi_Partite(&lista_nomi);

                Stampa_Menu_Lista(cursore,lista_nomi,MS_COLOR);
                Stampa_Indicazioni("Partita salvata con successo.\nPremere un tasto per tornare al menu principale.");

                esci = true;
                getch();
            }
            else if ((scelta>0 && scelta<numero_nomi)||(scelta>numero_nomi*3 && scelta<numero_nomi*4))
            {
                /**Sovrascrivi o cancella**/
                if (scelta>=numero_nomi)
                    cancella=true;
                else cancella = false;
                while (scelta>=numero_nomi)
                {
                    scelta -=numero_nomi;
                }
                //determina memoria interna necessaria al backup del file
                file_partite = fopen(FILE_PARTITE,"rb");
                posizione_file = ftell(file_partite);
                fseek(file_partite,0,SEEK_END);
                bytes = ftell(file_partite)-posizione_file + sizeof(partita) + Partita->numero_giocatori*sizeof(giocatore) + Area_Campo(Partita->campo.grandezza)*sizeof(casella);
                fseek(file_partite,0,SEEK_SET);

                //alloca uno spazio pari a tutto il file partite + Partita e i suoi giocatori
                backup = malloc(bytes);
                puntbackup = backup;

                //Solo se si sta sovrascrivendo
                if (!cancella)
                {
                    //copia i precedenti
                    for (i=1; i<scelta; i++)
                    {
                        fread(&temp_partita,1,sizeof(partita),file_partite);
                        memcpy(puntbackup,&temp_partita,sizeof(partita));
                        puntbackup += sizeof(partita);
                        fread(puntbackup,sizeof(casella),Area_Campo(temp_partita.campo.grandezza),file_partite);
                        puntbackup += sizeof(casella)*Area_Campo(temp_partita.campo.grandezza);
                        fread(puntbackup,sizeof(giocatore),temp_partita.numero_giocatori,file_partite);
                        puntbackup += sizeof(giocatore)*temp_partita.numero_giocatori;
                    }
                    //copia la partita attuale
                    memcpy(puntbackup,Partita,sizeof(partita));
                    puntbackup+=sizeof(partita);

                    //copia il campo
                    memcpy(puntbackup,Partita->campo.caselle,sizeof(casella)*Area_Campo(Partita->campo.grandezza));
                    puntbackup += sizeof(casella)*Area_Campo(Partita->campo.grandezza);

                    //copia i giocatori
                    puntgioc = Partita->giocatori;
                    while (puntgioc!=NULL)
                    {
                        memcpy(puntbackup,puntgioc,sizeof(giocatore));
                        puntgioc = puntgioc->prossimo;
                        puntbackup += sizeof(giocatore);
                    }
                }

                //salta slot
                fread(&temp_partita,1,sizeof(partita),file_partite);
                fseek(file_partite,sizeof(casella)*Area_Campo(temp_partita.campo.grandezza),SEEK_CUR);
                fseek(file_partite,sizeof(giocatore)*temp_partita.numero_giocatori,SEEK_CUR);

                //copia successivi
                posizione_file = ftell(file_partite);
                fseek(file_partite,0,SEEK_END);
                bytes = ftell(file_partite)-posizione_file;
                fseek(file_partite,posizione_file,SEEK_SET);
                fread(puntbackup,1,bytes,file_partite);
                puntbackup+=bytes;

                //chudi file e riapri in modalità scrittura
                fclose(file_partite);
                file_partite= fopen(FILE_PARTITE,"wb");

                //copia il file dalla memoria
                fwrite(backup,1,puntbackup-backup,file_partite);
                fclose(file_partite);

                //dealloca lo spazio
                free(backup);

                //ricrea lista nomi
                lista_nomi = NULL;
                Leggi_Nomi_Partite(&lista_nomi);
                //aggiungi campo "nuovo slot"
                if (lista_nomi!=NULL)
                {
                    punt_nomi=lista_nomi;
                    while (punt_nomi->prossimo!=NULL)
                    {
                        punt_nomi = punt_nomi->prossimo;
                    }
                    punt_nomi->prossimo = &nuovo_slot;
                }
                else lista_nomi = &nuovo_slot;
                numero_nomi = Numero_Stringhe(lista_nomi);

                //

                //Solo se si sta sovrascrivendo
                if (!cancella)
                {
                    Stampa_Menu_Lista(cursore,lista_nomi,MS_COLOR);
                    Stampa_Indicazioni("Partita salvata con successo.\nPremere un tasto per tornare al menu principale.");

                    esci = true;
                    getch();
                }
            }
        }

    }
    else return ERR_PARTITA_NON_INIZIATA;

    //cancella indicatori pagina
    Stampa_Indicatori_Pagina(0,0,0);

    return 0;
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



int Impostazioni(impostazioni * Imp)
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
    lista_stringhe lista_nomi, lista_valori;
    booleano esci;
    int scelta, numero_stringhe,i;
    int cursore = 1, errore;
    impostazioni_giocatore * puntatore;
    FILE * file_impostazioni;

    Stampa_Titolo_Menu("Impostazioni",MI_COLOR);
    Stampa_Indicazioni("Premere su, gi\x97 per selezionare le opzioni, sinistra\ndestra e INVIO per cambiarle, ESC per tornare al\nmenu principale");
    esci = false;
    while (!esci)
    {
        Crea_Lista_Impostazioni(*Imp, &lista_nomi, &lista_valori);
        numero_stringhe = Numero_Stringhe(lista_nomi);
        Stampa_Menu_Impostazioni(cursore,lista_nomi,lista_valori,MI_COLOR);

        scelta = Scelta_Menu_Lista(&cursore,numero_stringhe);
        if (scelta == 0) esci = true;
        if (scelta > numero_stringhe && scelta <= numero_stringhe *2) Cambia_Impostazione(Imp,cursore,1);
        if (scelta > numero_stringhe*2 && scelta <= numero_stringhe *3) Cambia_Impostazione(Imp,cursore,-1);
        if (scelta > 0 && scelta <= numero_stringhe) Cambia_Impostazione(Imp,cursore,0);
    }

    file_impostazioni = fopen(FILE_IMP,"wb");
    fwrite(Imp,1,sizeof(impostazioni),file_impostazioni);
    puntatore = Imp->giocatori;
    for (i=0;i<Imp->numero_giocatori;i++)
    {
        fwrite(puntatore,1,sizeof(impostazioni_giocatore),file_impostazioni);
        puntatore=puntatore->prossimo;
    }
    fclose(file_impostazioni);

    //Cancella indicatori pagina
    Stampa_Indicatori_Pagina(0,0,0);

    errore = 0;
    if ((errore = Controlla_Impostazioni(*Imp)))
        Impostazioni_Predefinite(Imp);
    return errore;
}

void Crea_Lista_Impostazioni (impostazioni Imp, lista_stringhe * lista_nomi, lista_stringhe * lista_valori)
{
    lista_stringhe puntatore_nomi, puntatore_valori;
    lista_impostazioni_giocatori puntatore_giocatore;
    int i;

    //libera gli spazi precedentemente utilizzati e allocane altri
    free(lista_nomi);
    free(lista_valori);
    *lista_nomi = malloc(sizeof(elemento_stringa));
    *lista_valori = malloc(sizeof(elemento_stringa));

    puntatore_nomi = *lista_nomi;
    puntatore_valori = *lista_valori;
    //Impostazioni predefinite
    strcpy(puntatore_nomi->stringa, "Ripristina default");
    strcpy(puntatore_valori->stringa, "");
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //Nome Partita
    strcpy(puntatore_nomi->stringa,"Nome Partita");
    strcpy(puntatore_valori->stringa,Imp.nome_partita);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;
    //Numero giocatori
    strcpy(puntatore_nomi->stringa,"Numero giocatori");
    sprintf(puntatore_valori->stringa,"%d",Imp.numero_giocatori);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;
    //Grandezza Campo
    strcpy(puntatore_nomi->stringa,"Grandezza campo");
    sprintf(puntatore_valori->stringa,"%d",Imp.grandezza_campo);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;
    //Numero pedine
    strcpy(puntatore_nomi->stringa,"Numero pedine");
    sprintf(puntatore_valori->stringa,"%d",Imp.numero_pedine);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;
    //Giocatore iniziale
    strcpy(puntatore_nomi->stringa,"Giocatore iniziale");
    sprintf(puntatore_valori->stringa,"%d",Imp.giocatore_iniziale);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    i=0;
    puntatore_giocatore = Imp.giocatori;
    while (puntatore_giocatore!=NULL)
    {
        //Nomi
        sprintf(puntatore_nomi->stringa,"Nome giocatore %d",i+1);
        sprintf(puntatore_valori->stringa,"%s",puntatore_giocatore->nome_giocatore);
        puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
        puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
        puntatore_nomi=puntatore_nomi->prossimo;
        puntatore_valori=puntatore_valori->prossimo;
        //tipi
        sprintf(puntatore_nomi->stringa,"Pedine giocatore %d",i+1);
        sprintf(puntatore_valori->stringa,"%c",Pedina_To_Char(puntatore_giocatore->tipo_pedine));
        puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
        puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
        puntatore_nomi=puntatore_nomi->prossimo;
        puntatore_valori=puntatore_valori->prossimo;
        //colori
        sprintf(puntatore_nomi->stringa,"Colore giocatore %d",i+1);
        Colore_To_String(puntatore_valori->stringa, puntatore_giocatore->colore_pedine);
        puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
        puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
        puntatore_nomi=puntatore_nomi->prossimo;
        puntatore_valori=puntatore_valori->prossimo;

        puntatore_giocatore = puntatore_giocatore->prossimo;
        i++;
    }
    //Spaziatura righe
    strcpy(puntatore_nomi->stringa, "Spaziatura righe");
    sprintf(puntatore_valori->stringa,"%d",Imp.spazio_righe);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //Spaziatura colonne
    strcpy(puntatore_nomi->stringa, "Spaziatura colonne");
    sprintf(puntatore_valori->stringa,"%d",Imp.spazio_colonne);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //colore campo
    strcpy(puntatore_nomi->stringa,"Colore campo");
    Colore_To_String(puntatore_valori->stringa,Imp.colore_campo);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //colore linee
    strcpy(puntatore_nomi->stringa,"Colore linee");
    Colore_To_String(puntatore_valori->stringa,Imp.colore_linee);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //colore selezione
    strcpy(puntatore_nomi->stringa,"Colore selezione");
    Colore_To_String(puntatore_valori->stringa,Imp.colore_selezione);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //mostra coordinate
    strcpy(puntatore_nomi->stringa,"Mostra coordinate");
    if (Imp.mostra_coordinate) strcpy(puntatore_valori->stringa, "si");
    else strcpy(puntatore_valori->stringa, "no");
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //mostra pedine fuori
    strcpy(puntatore_nomi->stringa,"Mostra pedine fuori");
    if (Imp.mostra_pedine_fuori) strcpy(puntatore_valori->stringa, "si");
    else strcpy(puntatore_valori->stringa, "no");
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //mostra tempo
    strcpy(puntatore_nomi->stringa,"Mostra punteggio");
    if (Imp.mostra_punteggio) strcpy(puntatore_valori->stringa, "si");
    else strcpy(puntatore_valori->stringa, "no");
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //suoni on off
    strcpy(puntatore_nomi->stringa, "Suoni on/off");
    if (Imp.suoni) strcpy(puntatore_valori->stringa, "si");
    else strcpy(puntatore_valori->stringa, "no");
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //inserimento
    strcpy(puntatore_nomi->stringa, "Suono inserimento");
    sprintf(puntatore_valori->stringa, "%d", Imp.suono_inserimento);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //mov
    strcpy(puntatore_nomi->stringa, "Suono spostamento");
    sprintf(puntatore_valori->stringa, "%d", Imp.suono_spostamento);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //formazione
    strcpy(puntatore_nomi->stringa, "Suono mulino");
    sprintf(puntatore_valori->stringa, "%d", Imp.suono_mulino);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //eliminazione
    strcpy(puntatore_nomi->stringa, "Suono elimina");
    sprintf(puntatore_valori->stringa, "%d", Imp.suono_eliminazione);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //sconfitta
    strcpy(puntatore_nomi->stringa, "Suono sconfitta");
    sprintf(puntatore_valori->stringa, "%d", Imp.suono_sconfitta);
    puntatore_nomi->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_valori->prossimo = malloc(sizeof(elemento_stringa));
    puntatore_nomi=puntatore_nomi->prossimo;
    puntatore_valori=puntatore_valori->prossimo;

    //fine
    strcpy(puntatore_nomi->stringa, "Suono vittoria");
    sprintf(puntatore_valori->stringa, "%d", Imp.suono_vittoria);
    puntatore_nomi->prossimo = NULL;
    puntatore_valori->prossimo = NULL;
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

int Cambia_Impostazione(impostazioni * Imp, int indice, int valore)
{
    int errore=0, giocatore, i;
    impostazioni_giocatore * puntatore_giocatore;
    //impostazioni 0-3
    if (indice<=5)
    {
        switch (indice)
        {
            case 0:
                if (!valore)
                    if (Messaggio("Ripristinare tutte le impostazioni?", true))
                        Impostazioni_Predefinite(Imp);
                break;
            case 1:
                if (!valore) Leggi_Valore_Stringa(Imp->nome_partita);
                break;
            case 3:
                Imp->grandezza_campo+= valore;
                if (Imp->grandezza_campo > MAX_GAME_SIZE)
                {
                    Imp->grandezza_campo = Imp->numero_giocatori/4;
                    if (Imp->numero_giocatori%4) Imp->grandezza_campo++;
                    Imp->grandezza_campo++;
                    if (Imp->grandezza_campo<MIN_GAME_SIZE) Imp->grandezza_campo = MIN_GAME_SIZE;
                }
                if (Imp->grandezza_campo < MIN_GAME_SIZE) Imp->grandezza_campo = MAX_GAME_SIZE;
                if ((Imp->grandezza_campo-1)*4<Imp->numero_giocatori) Imp->grandezza_campo = MAX_GAME_SIZE;
                if (Imp->numero_pedine > ((Imp->grandezza_campo-1)*4*Imp->grandezza_campo)/Imp->numero_giocatori) Imp->numero_pedine = ((Imp->grandezza_campo-1)*4*Imp->grandezza_campo)/Imp->numero_giocatori;
                if (Imp->numero_pedine < Imp->grandezza_campo) Imp->numero_pedine = Imp->grandezza_campo;
                Cambia_Impostazioni_Giocatori(Imp);
                break;
            case 2:
                Imp->numero_giocatori+= valore;
                if (Imp->numero_giocatori<2) Imp->numero_giocatori = Perimetro_Quadrato(MAX_GAME_SIZE);
                if (Imp->numero_giocatori>Perimetro_Quadrato(MAX_GAME_SIZE)) Imp->numero_giocatori = 2;
                while (Perimetro_Quadrato(Imp->grandezza_campo)<Imp->numero_giocatori) Imp->grandezza_campo++;
                if (Imp->numero_pedine < Imp->grandezza_campo) Imp->numero_pedine = Imp->grandezza_campo;
                if (Imp->numero_pedine > (Perimetro_Quadrato(Imp->grandezza_campo)*Imp->grandezza_campo)/Imp->numero_giocatori) Imp->numero_pedine = ((Imp->grandezza_campo-1)*4*Imp->grandezza_campo)/Imp->numero_giocatori;
                if (Imp->giocatore_iniziale > Imp->numero_giocatori) Imp->giocatore_iniziale = Imp->numero_giocatori;
                Cambia_Impostazioni_Giocatori(Imp);
                break;
            case 4:
                Imp->numero_pedine+= valore;
                if (Imp->numero_pedine > (Perimetro_Quadrato(Imp->grandezza_campo)*Imp->grandezza_campo)/Imp->numero_giocatori) Imp->numero_pedine = Imp->grandezza_campo;
                if (Imp->numero_pedine < Imp->grandezza_campo) Imp->numero_pedine = (Perimetro_Quadrato(Imp->grandezza_campo)*Imp->grandezza_campo)/Imp->numero_giocatori;
                break;
            case 5:
                Imp->giocatore_iniziale+= valore;
                if (Imp->giocatore_iniziale < 0) Imp->giocatore_iniziale = Imp->numero_giocatori;
                if (Imp->giocatore_iniziale > Imp->numero_giocatori) Imp->giocatore_iniziale = 0;
                break;
        }
    }
    //impostazioni giocatori
    if (indice>5 && indice <= 5+3*Imp->numero_giocatori)
    {
        indice-=6;
        giocatore = indice/3;
        puntatore_giocatore = Imp->giocatori;
        for (i=0; i<giocatore; i++)
            puntatore_giocatore = puntatore_giocatore->prossimo;
        indice %=3;
        switch (indice)
        {
            case 0:
                if (!valore) Leggi_Valore_Stringa(puntatore_giocatore->nome_giocatore);
                break;
            case 1:
                puntatore_giocatore->tipo_pedine+=valore;
                if (puntatore_giocatore->tipo_pedine >= 16) puntatore_giocatore->tipo_pedine = 0;
                if (puntatore_giocatore->tipo_pedine < 0) puntatore_giocatore->tipo_pedine = 15;
                break;
            case 2:
                puntatore_giocatore->colore_pedine+=valore;
                if (puntatore_giocatore->colore_pedine >= 16) puntatore_giocatore->colore_pedine = 0;
                if (puntatore_giocatore->colore_pedine < 0) puntatore_giocatore->colore_pedine = 15;
                break;
        }

    }
    //altre
    else if (indice > 5+3*Imp->numero_giocatori && indice <= 21+3*Imp->numero_giocatori)
    {
        indice -= 6+3*Imp->numero_giocatori;
        switch (indice)
        {
            case 2:
                Imp->colore_campo+=valore;
                if (Imp->colore_campo >= 16) Imp->colore_campo = 0;
                if (Imp->colore_campo < 0) Imp->colore_campo = 15;
                break;
            case 3:
                Imp->colore_linee+=valore;
                if (Imp->colore_linee >= 16) Imp->colore_linee = 0;
                if (Imp->colore_linee < 0) Imp->colore_linee = 15;
                break;
            case 4:
                Imp->colore_selezione+=valore;
                if (Imp->colore_selezione >= 16) Imp->colore_selezione = 0;
                if (Imp->colore_selezione < 0) Imp->colore_selezione = 15;
                break;
            case 5:
                if (!Imp->mostra_coordinate) Imp->mostra_coordinate = true;
                else Imp->mostra_coordinate = false;
                break;
            case 6:
                if (!Imp->mostra_pedine_fuori) Imp->mostra_pedine_fuori = true;
                else Imp->mostra_pedine_fuori = false;
                break;
            case 7:
                if (!Imp->mostra_punteggio) Imp->mostra_punteggio = true;
                else Imp->mostra_punteggio = false;
                break;
            case 8:
                if (!Imp->suoni) Imp->suoni = true;
                else Imp->suoni = false;
                break;
            case 9:
                Imp->suono_inserimento +=valore;
                while (Imp->suono_inserimento>=16) Imp->suono_inserimento-=16;
                while (Imp->suono_inserimento<0) Imp->suono_inserimento+=16;
                if (Imp->suoni) Riproduci_Suono(Imp->suono_inserimento);
                break;
            case 10:
                Imp->suono_spostamento +=valore;
                while (Imp->suono_spostamento>=16) Imp->suono_spostamento-=16;
                while (Imp->suono_spostamento<0) Imp->suono_spostamento+=16;
                if (Imp->suoni) Riproduci_Suono(Imp->suono_spostamento);
                break;
            case 11:
                Imp->suono_mulino +=valore;
                while (Imp->suono_mulino>=16) Imp->suono_mulino-=16;
                while (Imp->suono_mulino<0) Imp->suono_mulino+=16;
                if (Imp->suoni) Riproduci_Suono(Imp->suono_mulino);
                break;
            case 12:
                Imp->suono_eliminazione +=valore;
                while (Imp->suono_eliminazione>=16) Imp->suono_eliminazione-=16;
                while (Imp->suono_eliminazione<0) Imp->suono_eliminazione+=16;
                if (Imp->suoni) Riproduci_Suono(Imp->suono_eliminazione);
                break;
            case 13:
                Imp->suono_sconfitta
                    +=valore;
                while (Imp->suono_sconfitta>=16) Imp->suono_sconfitta-=16;
                while (Imp->suono_sconfitta<0) Imp->suono_sconfitta+=16;
                if (Imp->suoni) Riproduci_Suono(Imp->suono_sconfitta);
                break;
            case 14:
                Imp->suono_vittoria +=valore;
                while (Imp->suono_vittoria>=16) Imp->suono_vittoria-=16;
                while (Imp->suono_vittoria<0) Imp->suono_vittoria+=16;
                if (Imp->suoni) Riproduci_Suono(Imp->suono_vittoria);
                break;
            case 0:
                Imp->spazio_righe+=valore;
                if (Imp->spazio_righe>MAX_SPAZIO_RIGHE) Imp->spazio_righe = 0;
                if (Imp->spazio_righe<0) Imp->spazio_righe = MAX_SPAZIO_RIGHE;
                break;
            case 1:
                Imp->spazio_colonne+=valore;
                if (Imp->spazio_colonne>MAX_SPAZIO_COLONNE) Imp->spazio_colonne = 0;
                if (Imp->spazio_colonne<0) Imp->spazio_colonne = MAX_SPAZIO_COLONNE;
                break;
        }
    }
    else errore=ERR_IMP_INESISTENTE;

    return errore;
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

int Cambia_Impostazioni_Giocatori(impostazioni * Imp)
{
    /**
Restituisce:
0:  i giocatori corrispondono alla lista
1:  sono stati aggiunti giocatori alla lista
-1: sono stati tolti giocatori alla lista
     **/

    impostazioni_giocatore * puntatore, * da_cancellare;
    int i=0;

    //controlla che il numero di giocatori corrisponda alle impostazioni dei giocatori nella lista
    puntatore = Imp->giocatori;
    while (i<Imp->numero_giocatori-1 && puntatore->prossimo != NULL)
    {
        puntatore = puntatore->prossimo;
        i++;
    }
    //se la lista ne ha di meno gliene aggiunge
    if (i<Imp->numero_giocatori-1 && puntatore->prossimo == NULL)
    {
        while (i<Imp->numero_giocatori-1)
        {
            puntatore->prossimo = malloc(sizeof(impostazioni_giocatore));
            puntatore = puntatore->prossimo;
            sprintf(puntatore->nome_giocatore, "Giocatore%d", i+2);
            puntatore->colore_pedine = rand()%16;
            puntatore->tipo_pedine = rand()%16;
            i++;
        }
        puntatore->prossimo = NULL;
        return 1;
    }
    //se la lista ne ha di più li cancella
    else if (i == Imp->numero_giocatori-1 && puntatore->prossimo != NULL)
    {
        da_cancellare = puntatore;
        puntatore = puntatore->prossimo;
        da_cancellare->prossimo = NULL;
        while (puntatore != NULL)
        {
            da_cancellare = puntatore;
            puntatore = puntatore->prossimo;
            free(da_cancellare);
        }
        return -1;
    }
    return 0;
}

void Impostazioni_Predefinite(impostazioni * Imp)
{
    lista_impostazioni_giocatori puntatore;

    Imp->colore_campo=7;
    Imp->colore_linee = 4;
    Imp->colore_selezione = 15;
    Imp->giocatore_iniziale = 0;
    Imp->numero_giocatori = 2;

    Imp->giocatori=malloc(sizeof(impostazioni_giocatore));
    Imp->giocatori->colore_pedine = 12;
    strcpy(Imp->giocatori->nome_giocatore,"Giocatore1");
    Imp->giocatori->tipo_pedine = 0;
    Imp->giocatori->prossimo = malloc(sizeof(impostazioni_giocatore));

    puntatore = Imp->giocatori->prossimo;
    puntatore->colore_pedine = 9;
    strcpy(puntatore->nome_giocatore,"Giocatore2");
    puntatore->tipo_pedine = 1;
    puntatore->prossimo = NULL;

    Imp->grandezza_campo = 3;
    Imp->mostra_coordinate = false;
    Imp->mostra_pedine_fuori = true;
    Imp->mostra_punteggio = true;
    strcpy(Imp->nome_partita,"Nuova Partita");
    Imp->numero_pedine = 3;
    Imp->suoni = true;
    Imp->suono_inserimento = 1;
    Imp->suono_mulino = 10;
    Imp->suono_spostamento = 2;
    Imp->suono_eliminazione = 7;
    Imp->suono_sconfitta = 13;
    Imp->suono_vittoria = 15;
    Imp->spazio_colonne = 2;
    Imp->spazio_righe = 1;
}

void Colore_To_String(short_string stringa, int colore)
{
    switch (colore)
    {
        case 0:
            strcpy(stringa, "black");
            break;
        case 1:
            strcpy(stringa, "blu");
            break;
        case 2:
            strcpy(stringa,"green");
            break;
        case 3:
            strcpy(stringa,"aqua");
            break;
        case 4:
            strcpy(stringa,"red");
            break;
        case 5:
            strcpy(stringa,"purple");
            break;
        case 6:
            strcpy(stringa,"yellow");
            break;
        case 7:
            strcpy(stringa,"white");
            break;
        case 8:
            strcpy(stringa,"gray");
            break;
        case 9:
            strcpy(stringa, "light blu");
            break;
        case 10:
            strcpy(stringa,"light green");
            break;
        case 11:
            strcpy(stringa,"light aqua");
            break;
        case 12:
            strcpy(stringa,"light red");
            break;
        case 13:
            strcpy(stringa,"light purple");
            break;
        case 14:
            strcpy(stringa,"light yellow");
            break;
        case 15:
            strcpy(stringa,"bright white");
            break;
    }
}

char Pedina_To_Char(int pedina)
{
    char carattere;
    //☺,☻,♥,♦,♣,♠,♂,♀,♪,♫,☼,$,®,©,X,Y
    switch (pedina)
    {
        case 0:
            carattere = 1; //☺
            break;
        case 1:
            carattere = 2; //☻
            break;
        case 2:
            carattere = 3; //♥
            break;
        case 3:
            carattere = 4; //♦
            break;
        case 4:
            carattere = 5; //♣
            break;
        case 5:
            carattere = 6; //♠
            break;
        case 6:
            carattere = 11; //♂
            break;
        case 7:
            carattere = 12; //♀
            break;
        case 8:
            carattere = 190; //¥
            break;
        case 9:
            carattere = 14; //♫
            break;
        case 10:
            carattere = 15; //☼
            break;
        case 11:
            carattere = '$';
            break;
        case 12:
            carattere = 156; //£
            break;
        case 13:
            carattere = 184; //©
            break;
        case 14:
            carattere = 'X';
            break;
        case 15:
            carattere = 'Y';
            break;
    }
    return carattere;
}



int Record()
{
    FILE * file_record;
    int posizione,i;
    float punteggio;
    short_string nome;

    //apre il file record, controlla che esista e che non sia vuoto
    file_record = fopen(FILE_RECORD,"r");
    if (file_record!=NULL)
    {
        fseek(file_record,0,SEEK_END);
        posizione = ftell(file_record);
        fseek(file_record,0,SEEK_SET);
        if (posizione-ftell(file_record))
        {
            //stampa lo sfondo, il titolo e le linee
            Cambia_Sfondo(BACK_COLOR,DEF_BACK_COLOR);
            Cambia_Colore(MR_COLOR,DEF_BACK_COLOR);
            //Stampa titolo top
            i=0;
            gotoxy((BUFFER_X-MR_TITOLO_LUNGHEZZA)/2,i++);
            puts(" ______                       _     __     ");
            gotoxy((BUFFER_X-MR_TITOLO_LUNGHEZZA)/2,i++);
            puts("/\\__  _\\                    /' \\  /'__`\\   ");
            gotoxy((BUFFER_X-MR_TITOLO_LUNGHEZZA)/2,i++);
            puts("\\/_/\\ \\/   ___   _____     /\\_, \\/\\ \\/\\ \\  ");
            gotoxy((BUFFER_X-MR_TITOLO_LUNGHEZZA)/2,i++);
            puts("   \\ \\ \\  / __`\\/\\ '__`\\   \\/_/\\ \\ \\ \\ \\ \\ ");
            gotoxy((BUFFER_X-MR_TITOLO_LUNGHEZZA)/2,i++);
            puts("    \\ \\ \\/\\ \\_\\ \\ \\ \\_\\ \\     \\ \\ \\ \\ \\_\\ \\");
            gotoxy((BUFFER_X-MR_TITOLO_LUNGHEZZA)/2,i++);
            puts("     \\ \\_\\ \\____/\\ \\ ,__/      \\ \\_\\ \\____/");
            gotoxy((BUFFER_X-MR_TITOLO_LUNGHEZZA)/2,i++);
            puts("      \\/_/\\/___/  \\ \\ \\/        \\/_/\\/___/ ");
            gotoxy((BUFFER_X-MR_TITOLO_LUNGHEZZA)/2,i++);
            puts("                   \\ \\_\\                   ");
            gotoxy((BUFFER_X-MR_TITOLO_LUNGHEZZA)/2,i++);
            puts("                    \\/_/                   ");
            //stampa divisori
            gotoxy((BUFFER_X-MR_DIV_X)/2,MR_DIV1_Y);
            for (i=0; i<MR_DIV_X; i++) putchar(205);
            gotoxy((BUFFER_X-MR_DIV_X)/2,MR_DIV2_Y);
            for (i=0; i<MR_DIV_X; i++) putchar(205);

            //passa in rassegna del file
            i=0;
            while (!feof(file_record) && i<MR_MAX)
            {
                //legge il nome del giocatore
                fscanf(file_record,"%s",nome);
                //controlla che non sia arrivato alla fine del file
                if (!feof(file_record))
                {
                    //legge il punteggio
                    fscanf(file_record,"%f",&punteggio);
                    //stampa il record con un colore diverso in base alla postazione
                    switch (i)
                    {
                        case 0:
                            Cambia_Colore(MR_1_COLOR,DEF_BACK_COLOR);
                            break;
                        case 1:
                            Cambia_Colore(MR_2_COLOR,DEF_BACK_COLOR);
                            break;
                        case 2:
                            Cambia_Colore(MR_3_COLOR,DEF_BACK_COLOR);
                            break;
                        default:
                            Cambia_Colore(MR_LAST_COLOR,DEF_BACK_COLOR);
                            break;
                    }
                    gotoxy(MR_NOME_X,MR_DIV1_Y+i+1);
                    printf("%s",nome);
                    gotoxy(MR_PUNTI_X,MR_DIV1_Y+i+1);
                    printf("%.2f",punteggio);
                    i++;
                }
            }
            //chiude il file e aspetta che l'utente prema un tasto
            fclose(file_record);
            Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
            gotoxy((BUFFER_X-MR_DIV_X)/2,MR_DIV2_Y+1);
            printf("Premere un tasto per tornare al menu principale.");
            getch();
        }
        else return ERR_FILE_REC_VUOTO;
    }
    else
    {
        return ERR_FILE_REC_INESISTENTE;
    }

    //resetta il colore di default
    Cambia_Sfondo(BACK_COLOR,DEF_BACK_COLOR);
    return 0;

}

int Aiuto()
{
    int posizione, pagina = 0,i, numero_righe,scelta;
    buffer_testo testo, punt;
    booleano esci=false;
    long_string riga, parola;
    unsigned char carattere;
    FILE * file_aiuto;

    //apre il file, controlla che esista, e se è vuoto
    if ((file_aiuto = fopen(FILE_AIUTO,"r"))!=NULL)
    {
        fseek(file_aiuto,0,SEEK_END);
        posizione = ftell(file_aiuto);
        fseek(file_aiuto,0,SEEK_SET);
        if (posizione-ftell(file_aiuto))
        {
            //passa in rassegna del documento e lo memorizza in più righe
            //più piccole della lunghezza massima di un rigo ed in maniera
            //da non tagliare nessuna parola in due
            numero_righe = 0;
            testo = malloc(sizeof(riga_testo));
            punt = testo;
            punt->prossimo = NULL;
            strcpy(punt->stringa,"");
            strcpy(riga,"");
            while (!feof(file_aiuto))
            {
                carattere = getc(file_aiuto);
                if (carattere > 32 && carattere <255)
                {
                    i=0;
                    do
                    {
                        parola[i++]=carattere;
                        carattere = getc(file_aiuto);
                    }
                    while (carattere > 32 && carattere <255 && !feof(file_aiuto));
                    parola[i]='\0';
                    if (strlen(riga)+strlen(parola)>=BUFFER_TESTO_X)
                    {
                        strcpy(punt->stringa,riga);
                        strcpy(riga,parola);
                        punt->prossimo = malloc(sizeof(riga_testo));
                        punt = punt->prossimo;
                        punt->prossimo = NULL;
                        strcpy(punt->stringa,"");
                        numero_righe++;
                    }
                    else strcat(riga,parola);
                }
                if (carattere == ' ')
                {
                    if (strlen(riga)<BUFFER_TESTO_X-1)
                    {
                        riga[strlen(riga)+1] = '\0';
                        riga[strlen(riga)] = ' ';
                    }
                }
                if (carattere == '\n')
                {
                    strcpy(punt->stringa,riga);
                    strcpy(riga,"");
                    punt->prossimo = malloc(sizeof(riga_testo));
                    punt = punt->prossimo;
                    punt->prossimo = NULL;
                    strcpy(punt->stringa,"");
                    numero_righe++;
                }
            }
            strcpy(punt->stringa,riga);
            numero_righe++;

            //cancella lo sfondo
            Cambia_Sfondo(DEF_COLOR,DEF_BACK_COLOR);

            //stampa le righe
            while (!esci)
            {

                Stampa_Titolo();
                Stampa_Cornice(MA_COLOR);
                Stampa_Titolo_Menu("Regole",MA_COLOR);
                Stampa_Indicazioni("Premere su e gi\x97 per cambiare pagina, ESC per\ntornare al menu principale");
                Stampa_Indicatori_Pagina(pagina,numero_righe/BUFFER_TESTO_Y+1,MA_COLOR);

                Cambia_Colore(DEF_COLOR,MA_COLOR-8);
                punt = testo;
                for (i=0; i<BUFFER_TESTO_Y*pagina; i++)
                {
                    punt = punt->prossimo;
                }
                i=0;
                while (punt != NULL && i<BUFFER_TESTO_Y)
                {
                    gotoxy(TESTO_X,TESTO_Y+i);
                    puts(punt->stringa);
                    punt = punt->prossimo;
                    i++;
                }
                //aspetta gli input dell'utente
                scelta = Scelta_Menu_Lista(&pagina,numero_righe/BUFFER_TESTO_Y+1);
                if (!scelta) esci =true;
            }
            //chiude il file
            fclose(file_aiuto);

            //dealloca tutto lo spazio
            punt=testo->prossimo;
            while (punt!=NULL)
            {
                free(testo);
                testo = punt;
                punt=testo->prossimo;
            }
            free(testo);
        }
        else
        {
            fclose(file_aiuto);
            return ERR_FILE_AIUTO_VUOTO;
        }
    }
    else return ERR_FILE_AIUTO_INESISTENTE;

    //resetta colori default
    Cambia_Colore(DEF_COLOR,DEF_BACK_COLOR);
    //cancella indicatori pagina
    Stampa_Indicatori_Pagina(0,0,0);

    return 0;
}

void Gestione_Errori(int errore)
{
    char messaggio[BUFFER_TESTO_X*BUFFER_TESTO_Y];

    if (errore)
    {
        Stampa_Cornice_Piccola(ME_COLOR);
        switch (errore)
        {
            //Errori
            case ERR_FILE_PARTITE_INESISTENTE:
                sprintf(messaggio,"Nessuna partita da caricare: file %s inesistente.",FILE_PARTITE);
                break;
            case ERR_FILE_IMP_INESISTENTE:
                sprintf(messaggio,"File %s inesistente. Verr\x85 ricreato con le impostazioni predefinite.",FILE_IMP);
                break;
            case ERR_FILE_REC_INESISTENTE:
                sprintf(messaggio,"File %s inesistente. Nessun record da mostrare.", FILE_RECORD);
                break;
            case ERR_FILE_AIUTO_INESISTENTE:
                sprintf(messaggio,"Impossibile procedere. File %s inesistente.",FILE_AIUTO);
                break;
            case ERR_FILE_IMP_INVALID:
                sprintf(messaggio,"Il file %s sembra danneggiato. Verr\x85 ricreato con le impostazioni predefinite.",FILE_IMP);
                break;
            case ERR_IMP_INVALID:
                strcpy(messaggio,"Le impostazioni non sono valide! Verranno ripristinate le impostazioni predefinite.");
                break;
            case ERR_FILE_AIUTO_VUOTO:
                sprintf(messaggio,"Impossibile procedere. File %s vuoto.",FILE_AIUTO);
                break;
            case ERR_PARTITA_NON_INIZIATA:
                strcpy(messaggio,"Nessuna partita da salvare!");
                break;
            case ERR_FILE_PARTITE_VUOTO:
                sprintf(messaggio,"Nessuna partita da caricare: file %s vuoto.",FILE_PARTITE);
                break;
            case ERR_FILE_REC_VUOTO:
                sprintf(messaggio,"File %s vuoto. Nessun record da mostrare.", FILE_RECORD);
                break;
            case ERR_FILE_IMP_VUOTO:
                sprintf(messaggio,"Il file %s \x82 vuoto. Verr\x85 ricreato con le impostazioni predefinite.",FILE_IMP);
                break;
            case ERR_IMP_INESISTENTE:
                strcpy(messaggio,"Errore! L'impostazione che si desidera cambiare \x82 inesistente!");
                break;
                //errori di gioco
            case ERR_CASELLA_INESISTENTE:
                strcpy(messaggio,"Errore! Casella inesistente!");
                break;
            case ERR_CASELLA_PIENA:
                strcpy(messaggio,"La casella selezionata \x82 gi\x85 occupata!");
                break;
            case ERR_CASELLA_VUOTA:
                strcpy(messaggio,"La casella selezionata \x82 vuota!");
                break;
            case ERR_CASELLE_NON_ADIACENTI:
                strcpy(messaggio,"Le caselle scelte non sono adiacenti!");
                break;
            case ERR_PEDINA_AVVERSARIA:
                strcpy(messaggio,"La pedina selezionata appartiene ad un avversario!");
                break;
            case ERR_PEDINA_GIOCATORE_TURNO:
                strcpy(messaggio,"La pedina selezionata non appartiene ad un avversario!");
                break;
            case ERR_INTERROTTA:
                strcpy(messaggio,"Partita interrotta dall'utente. Se si intende riprenderla salvare la partita attuale e caricarla");
                break;
            case ERR_MULINO:
                strcpy(messaggio,"Non puoi eliminare una pedina che forma un mulino se ce ne sono altre libere!");
                break;
                //
        }
        strcat(messaggio, "\nPremere un tasto per continuare.");

        Messaggio(messaggio,false);
    }
}

booleano Esci()
{
    return Messaggio("Sicuro di voler uscire?", true);
}
