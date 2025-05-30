#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

ListaAttivita* nuovaLista() { //Restituisce un puntatore a una nuova struttura ListaAttivita.
    ListaAttivita* lista = (ListaAttivita*) malloc(sizeof(ListaAttivita)); //Alloca dinamicamente memoria per una nuova lista.
    if (lista == NULL) {
        printf("Errore di allocazione memoria.\n");
        exit(1);
    }
    lista->head = NULL; //Inizializza il puntatore al primo nodo (testa della lista) a NULL, cioè la lista è vuota.
    return lista;
}

void aggiungiAttivita(ListaAttivita* lista, Attivita* att) {
    Nodo* nuovo = (Nodo*) malloc(sizeof(Nodo)); //Alloca dinamicamente un nuovo nodo.
    if (nuovo == NULL) {
        printf("Errore di allocazione nodo.\n");
        exit(1);
    }
    nuovo->att = att; //Il campo att del nodo punta alla nuova attività.
    nuovo->next = lista->head; //Il nuovo nodo punta al primo elemento attualmente presente nella lista (inserimento in testa).
    lista->head = nuovo; //La testa della lista viene aggiornata per puntare al nuovo nodo, che ora è il primo elemento.
}

void stampaLista(const ListaAttivita* lista) { //Prende in input un puntatore costante a una ListaAttivita, ovvero una lista che non verrà modificata internamente.
    Nodo* corrente = lista->head; //Si crea un puntatore corrente per attraversare la lista, inizializzato al primo nodo (head).
    if (corrente == NULL) {
        printf("Nessuna attività presente.\n");
        return;
    }

    while (corrente != NULL) { //Finché non si arriva alla fine della lista (NULL) stampa
        stampaAttivita(corrente->att);
        corrente = corrente->next;
    }
}

void aggiornaProgresso(ListaAttivita* lista, const char* descrizione, const char* corso, int ore) {
    Nodo* corrente = lista->head; //Si parte dal primo nodo della lista.
    int trovata = 0; //La variabile trovata serve per sapere se l'attività è stata trovata.

    while (corrente != NULL) {
        if (strcmp(corrente->att->descrizione, descrizione) == 0 && //Vengono confrontati sia la descrizione sia il corso dell’attività. Se entrambi corrispondono, si è trovata l’attività giusta.
            strcmp(corrente->att->corso, corso) == 0) {
            aggiornaTempo(corrente->att, ore);
            printf("Aggiornamento riuscito.\n");
            trovata = 1;
            break;
        }
        corrente = corrente->next;
    }

    if (!trovata) {
        printf("Attività con descrizione \"%s\" e corso \"%s\" non trovata.\n", descrizione, corso);
    }
}

void generaReport(ListaAttivita* lista, Data oggi) {
    Nodo* corrente = lista->head;
    printf("==== REPORT SETTIMANALE ====\n");

    printf("\nAttività Completate:\n"); //Scorre la lista e stampa ogni attività il cui stato è COMPLETATA.
    corrente = lista->head;
    while (corrente != NULL) {
        if (corrente->att->stato == COMPLETATA) {
            stampaAttivita(corrente->att);
        }
        corrente = corrente->next;
    }

    printf("\nAttività In Corso:\n"); //Per ciascuna attività in corso: Chiama aggiornaStato, che potrebbe aggiornare lo stato in IN_RITARDO se la scadenza è superata.
    corrente = lista->head;
    while (corrente != NULL) {
        if (corrente->att->stato == IN_CORSO) {
            aggiornaStato(corrente->att, oggi);
            if (corrente->att->stato == IN_CORSO)
                stampaAttivita(corrente->att);
        }
        corrente = corrente->next;
    }

    printf("\nAttività In Ritardo:\n"); //Stampa le attività marcate come IN_RITARDO.
    corrente = lista->head;
    while (corrente != NULL) {
        if (corrente->att->stato == IN_RITARDO) {
            stampaAttivita(corrente->att);
        }
        corrente = corrente->next;
    }
}
