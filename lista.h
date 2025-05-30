#ifndef LISTA_H
#define LISTA_H

#include "attivita.h"

typedef struct nodo {
    Attivita* att; //puntatore all’attività contenuta nel nodo.
    struct nodo* next; //puntatore al nodo successivo nella lista.
} Nodo;

typedef struct {
    Nodo* head;  //punta al primo nodo della lista.
} ListaAttivita;

ListaAttivita* nuovaLista();
void aggiungiAttivita(ListaAttivita* lista, Attivita* att);
void stampaLista(const ListaAttivita* lista);
void aggiornaProgresso(ListaAttivita* lista, const char* descrizione, const char* corso, int ore);
void generaReport(ListaAttivita* lista, Data oggi);

#endif
