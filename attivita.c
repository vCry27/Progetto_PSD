#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita.h"

Attivita* creaAttivita(const char* descrizione, const char* corso, Data scadenza, int tempo_stimato, Priorita priorita) { //La funzione costruisce un'attività nuova completa
    Attivita* nuova = (Attivita*) malloc(sizeof(Attivita));
    if (nuova == NULL) {
        printf("Errore di allocazione memoria.\n");
        exit(1);
    }

    strncpy(nuova->descrizione, descrizione, 99); //Copia la stringa descrizione nel campo descrizione della struttura
    strncpy(nuova->corso, corso, 49);
    nuova->descrizione[99] = '\0';
    nuova->corso[49] = '\0';

    nuova->scadenza = scadenza;
    nuova->tempo_stimato = tempo_stimato;
    nuova->tempo_trascorso = 0;
    nuova->priorita = priorita;
    nuova->stato = IN_CORSO;

    return nuova;
}

void aggiornaTempo(Attivita* att, int ore) { /*La funzione aggiornaTempo ha il compito di aggiornare il tempo trascorso su una determinata attività e, 
se necessario, marcarla come completata.*/
    if (att != NULL) {
        att->tempo_trascorso += ore; //Aggiornamento del tempo trascorso
        if (att->tempo_trascorso >= att->tempo_stimato) {//Verifica se l'attività è da considerare completata
            att->stato = COMPLETATA; 
        }
    }
}

int confrontaDate(Data d1, Data d2) { //Restituisce -1 se in corso, 0 se uguali, 1 se in ritardo
    if (d1.anno < d2.anno) return -1;
    if (d1.anno > d2.anno) return 1;
    if (d1.mese < d2.mese) return -1;
    if (d1.mese > d2.mese) return 1;
    if (d1.giorno < d2.giorno) return -1;
    if (d1.giorno > d2.giorno) return 1;
    return 0;
}

void aggiornaStato(Attivita* att, Data oggi) { //Aggiorna uno Stato in ritardo
    if (att == NULL || att->stato == COMPLETATA) return;

    if (confrontaDate(att->scadenza, oggi) < 0) {
        att->stato = IN_RITARDO;
    }
}

void stampaAttivita(const Attivita* att) { //Semplice stampa di un attività completa
    if (att == NULL) return;

    printf("Descrizione : %s\n", att->descrizione);
    printf("Corso       : %s\n", att->corso);
    printf("Scadenza    : %02d/%02d/%04d\n", att->scadenza.giorno, att->scadenza.mese, att->scadenza.anno);
    printf("Tempo stimato : %d ore\n", att->tempo_stimato);
    printf("Tempo svolto  : %d ore\n", att->tempo_trascorso);

    printf("Priorità    : ");
    switch (att->priorita) {
        case ALTA: printf("Alta\n"); break;
        case MEDIA: printf("Media\n"); break;
        case BASSA: printf("Bassa\n"); break;
    }

    printf("Stato       : ");
    switch (att->stato) {
        case COMPLETATA: printf("Completata\n"); break;
        case IN_CORSO: printf("In corso\n"); break;
        case IN_RITARDO: printf("In ritardo\n"); break;
    }

    printf("-----------\n");
}