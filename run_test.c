#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita.h"
#include "lista.h"

Data parseData(const char* data_str) {   //Funzione per leggere la data dal file
    Data d;
    sscanf(data_str, "%d-%d-%d", &d.anno, &d.mese, &d.giorno);
    return d;
}

void caricaAttivitaDaFile(ListaAttivita* lista, const char* nomefile) {
    FILE* f = fopen(nomefile, "r"); //Apre il file in modalità lettura
    if (!f) {
        perror("Errore apertura file input");
        exit(1);
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), f)) { //fgets legge una riga intera dal file in linea
        char descrizione[100], corso[100], scadenza_str[20], priorita_str[10];
        int ore;
        Priorita priorita;

        sscanf(linea, "%99[^;];%99[^;];%19[^;];%d;%9s", descrizione, corso, scadenza_str, &ore, priorita_str); //Usa sscanf per dividere la riga letta in campi separati da ;

        if (strcmp(priorita_str, "ALTA") == 0)
            priorita = ALTA;
        else if (strcmp(priorita_str, "MEDIA") == 0)
            priorita = MEDIA;
        else
            priorita = BASSA;

        Data data = parseData(scadenza_str); //La funzione parseData prende il campo data come stringa ("2025-06-03") e lo converte in una struct Data
        Attivita* a = creaAttivita(descrizione, corso, data, ore, priorita);
        aggiungiAttivita(lista, a);
    }
    aggiornaProgresso(lista,"Riassunto Promessi Sposi","Italiano",2);  //2 Test Suite :Aggiornamento del progresso delle attività.
    fclose(f);
}

void stampaListaSuFile(ListaAttivita* lista, const char* nomefile) {
    FILE* f = fopen(nomefile, "w");
    if (!f) {
        perror("Errore apertura file output");
        exit(1);
    }

    Nodo* corrente = lista->head;
    while (corrente) {
        Attivita* a = corrente->att;

        fprintf(f, "Attività: %s\n", a->descrizione);
        fprintf(f, "Corso: %s\n", a->corso);
        fprintf(f, "Scadenza: %04d-%02d-%02d\n", a->scadenza.anno, a->scadenza.mese, a->scadenza.giorno);
        fprintf(f, "Ore stimate: %d\n", a->tempo_stimato);
        fprintf(f, "Ore svolte: %d\n", a->tempo_trascorso);

        fprintf(f, "Priorità: ");
        if (a->priorita == ALTA) fprintf(f, "ALTA\n");
        else if (a->priorita == MEDIA) fprintf(f, "MEDIA\n");
        else fprintf(f, "BASSA\n");

        fprintf(f, "Stato: ");
        if (a->stato == COMPLETATA) fprintf(f, "COMPLETATA\n\n");
        else if (a->stato == IN_RITARDO) fprintf(f, "IN_RITARDO\n\n");
        else fprintf(f, "IN_CORSO\n\n");

        corrente = corrente->next;
    }

    fclose(f);
}


int confrontaFile(const char* f1, const char* f2) { //Se sono uguali → ritorna 1 (vero).
    FILE *a = fopen(f1, "r");
    FILE *b = fopen(f2, "r");
    if (!a || !b) {
        perror("Errore apertura file confronto");
        return 0;
    }

    char linea1[512], linea2[512]; //linea1 e linea2 servono per memorizzare le righe lette.
    int riga = 1; //iga tiene traccia del numero di riga per dire dove si trova l’errore.
    while (fgets(linea1, sizeof(linea1), a) && fgets(linea2, sizeof(linea2), b)) { //Legge una riga dal file a e una riga dal file b.
        // Rimuovi newline e spazi finali
        linea1[strcspn(linea1, "\r\n")] = 0; // strcspn(linea, "\r\n") trova la posizione della prima \r o \n. .
        linea2[strcspn(linea2, "\r\n")] = 0; // Sostituisce quel carattere con \0 (fine stringa), eliminando l'andata a capo

        if (strcmp(linea1, linea2) != 0) { //Usa strcmp per confrontare linea1 e linea2.
            printf("Differenza alla riga %d:\n", riga);
            printf("  Output:   \"%s\"\n", linea1);
            printf("  Expected: \"%s\"\n", linea2);
            fclose(a); fclose(b);
            return 0;
        }
        riga++; //Passa alla riga successiva.
    }

    int restA = fgets(linea1, sizeof(linea1), a) != NULL; //restA è true → file a ha ancora righe non lette.
    int restB = fgets(linea2, sizeof(linea2), b) != NULL; //restB è true → file b ha ancora righe non lette.

    fclose(a); fclose(b);
    return !(restA || restB); // 1 se entrambi file finiti insieme, 0 se uno ha più righe
}


int main() {
    ListaAttivita* lista = nuovaLista();
    caricaAttivitaDaFile(lista, "input.txt");
    stampaListaSuFile(lista, "output.txt");
    Data oggi = {27, 5, 2025};
    generaReport(lista,oggi); //3 test suite: Generazione report settimanale
    
    if (confrontaFile("output.txt", "expected.txt")) {
        printf("✅ TEST PASSATO: output.txt corrisponde a expected.txt\n");  //1 test suite: Attività corretamente inserite
    } else {
        printf("❌ TEST FALLITO: output.txt diverso da expected.txt\n");
    }

    return 0;
}
