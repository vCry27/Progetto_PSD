# Progetto_PSD
Sistema di Pianificazione e Monitoraggio delle Attività di Studio

Funzionalità Principali
Durante l'esecuzione, il programma offre le seguenti funzionalità:

Inserimento Attività
Inserisce una nuova attività di studio specificando:

- Descrizione

- Corso/Materia

- Data di scadenza

- Tempo stimato per il completamento

- Priorità (Alta, Media, Bassa)

Visualizzazione Attività
Mostra tutte le attività attualmente registrate.

Aggiornamento Progresso
Permette di aggiornare le ore di studio svolte su una specifica attività.
Se necessario, lo stato (IN_CORSO, COMPLETATA, IN_RITARDO) viene aggiornato automaticamente.

Generazione Report Settimanale
Produce un report che classifica le attività in:

- Completate

- In Corso

- In Ritardo
basandosi sulla data corrente e aggiornando automaticamente gli stati.

Note sull'Uso dei File
Durante l'esecuzione normale:
- Non sono richiesti file esterni.
L'utente interagisce direttamente con il programma tramite menu e input da tastiera.

I file .txt (input.txt, expected.txt, output.txt) sono utilizzati esclusivamente per i test automatici:
- Caricamento di dati di prova.
- Verifica automatica dell'output generato.

Come Compilare ed Eseguire
Esecuzione normale:
make
./main

 Esecuzione dei test:
make test

 Pulizia dei file generati:
make clean

