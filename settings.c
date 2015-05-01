#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"
#include "errors.h"
#include "board.h"
#include "sounds.h"

int Controlla_Impostazioni (impostazioni Imp)
{
    int errore=0, i;
    int err_numero_giocatori = 0,
        err_nome_partita = 0,
        err_grandezza_campo = 0,
        err_numero_pedine = 0,
        err_giocatore_iniziale = 0,
        err_colori = 0,
        err_spazi = 0,
        err_suoni = 0;
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
        Imp.grandezza_campo < 3 ||
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
    {
        err_spazi = 1;
    }
    if (err_numero_giocatori ||
        err_nome_partita ||
        err_grandezza_campo ||
        err_numero_pedine ||
        err_giocatore_iniziale ||
        err_colori ||
        err_spazi ||
        err_suoni)
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


