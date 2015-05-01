#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "game-io.h"
#include "graphics.h"

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
