#ifndef ATTIVITA_H
#define ATTIVITA_H

typedef enum { BASSA, MEDIA, ALTA } Priorita;
typedef enum { IN_CORSO, COMPLETATA, IN_RITARDO } Stato;

typedef struct {
    int giorno, mese, anno;
} Data;

typedef struct {
    char descrizione[100];
    char corso[50];
    Data scadenza;
    int tempo_stimato;
    int tempo_trascorso;
    Priorita priorita;
    Stato stato;
} Attivita;

Attivita* creaAttivita(const char* descrizione, const char* corso, Data scadenza, int tempo_stimato, Priorita priorita);
void aggiornaTempo(Attivita* att, int ore);
void aggiornaStato(Attivita* att, Data oggi);
void stampaAttivita(const Attivita* att);
int confrontaDate(Data d1, Data d2);

#endif