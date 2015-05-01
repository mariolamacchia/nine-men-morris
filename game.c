#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "basetypes.h"
#include "console.h"
#include "sounds.h"
#include "game.h"
#include "errors.h"
#include "game-io.h"
#include "menus.h"
#include "nine-men-morris.h"

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
    file_record = fopen(FILE_RECORD, "r");
    if (file_record != NULL)
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
