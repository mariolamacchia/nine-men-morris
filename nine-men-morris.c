#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "nine-men-morris.h"
#include "console.h"
#include "game-io.h"
#include "errors.h"

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

booleano Esci()
{
    return Messaggio("Sicuro di voler uscire?", true);
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
