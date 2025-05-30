#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attivita.h"
#include "lista.h"

Data leggiData() { //Funzione che legge una data inserita in input
    Data d;
    printf("Inserisci la data (gg mm aaaa): ");
    scanf("%d %d %d", &d.giorno, &d.mese, &d.anno);
    return d;
}

Priorita leggiPriorita() { //Funzione che legge la priorità
    int scelta;
    printf("Priorità (1 = Alta, 2 = Media, 3 = Bassa): ");
    scanf("%d", &scelta);
    switch (scelta) {
        case 1: return ALTA;
        case 2: return MEDIA;
        case 3: return BASSA;
        default: printf("Scelta non valida, impostata a Media.\n"); return MEDIA;
    }
}

int main() {
    ListaAttivita* lista = nuovaLista(); //Crea una lista vuota dove saranno memorizzate le attività.
    int scelta;
    char buffer[100], corso_buffer[50];

    do {
        printf("\n==== Menu ====\n");
        printf("1. Aggiungi attività\n");
        printf("2. Visualizza attività\n");
        printf("3. Aggiorna tempo studio\n");
        printf("4. Genera report settimanale\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        getchar();

        switch (scelta) {
            case 1: {
                char descrizione[100], corso[50]; 
                int tempo;
                printf("Descrizione: ");
                fgets(descrizione, 100, stdin); //Prende la descrizione
                descrizione[strcspn(descrizione, "\n")] = '\0';

                printf("Corso: ");
                fgets(corso, 50, stdin); //Prende il corso
                corso[strcspn(corso, "\n")] = '\0';

                Data scadenza = leggiData(); //Chiama la funzione per leggere la data
                printf("Tempo stimato (in ore): ");
                scanf("%d", &tempo);

                Priorita prio = leggiPriorita(); //Chiama la funzione per leggere la priorità

                Attivita* nuova = creaAttivita(descrizione, corso, scadenza, tempo, prio); //Alloca dinamicamente memoria per una nuova Attivita,
                aggiungiAttivita(lista, nuova);

                printf("Attività aggiunta con successo.\n");
                break;
            }
            case 2:
                stampaLista(lista); //Stampa la lista
                break;

            case 3: { //Aggiorna il tempo
                printf("Inserisci descrizione esatta dell'attività da aggiornare: ");
                fgets(buffer, 100, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                printf("Inserisci il corso/materia dell'attività: ");
                fgets(corso_buffer, 50, stdin);
                corso_buffer[strcspn(corso_buffer, "\n")] = '\0';

                int ore;
                printf("Ore da aggiungere: ");
                scanf("%d", &ore);

                aggiornaProgresso(lista, buffer, corso_buffer, ore);
                break;
            }
            case 4: { //Prende una data e genera il report
                printf("Data attuale:\n");
                Data oggi = leggiData();
                generaReport(lista, oggi);
                break;
            }
            case 0:
                printf("Uscita in corso...\n");
                break;
            default:
                printf("Scelta non valida.\n");
        }

    } while (scelta != 0);

    return 0;
}
