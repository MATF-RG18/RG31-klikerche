#ifndef ISPIS_H
#define ISPIS_H

#include "main.h"

/* Opis poruke o FPS; polozaj teksta
 * i pomocna struktura sa podacima */
#define FPS_POL 25
struct fps{
    char niska[8];
    int vreme;
} fps;

/* Svaka poruka traje odnosno
 * nestaje nakon tri sekunde */
#define SEKUNDA 1000
#define TRAJANJE 3000

/* Enumeracija koja opisuje
 * aktivnost poruka na ekranu;
 * krece od jedinice, posto vec
 * postoji NEAKTIVNO = 0 */
enum {USPESNO_CUVANJE = 1, NEUSPESNO_CUVANJE,
      USPESNO_CITANJE, NEUSPESNO_CITANJE};

/* Struktura koja enkapsulira
 * aktivne poruke na ekranu */
struct poruke{
    int poruka;
    int vreme;
} por;

/* Deklaracije fja za ispis */
void ispisi_poruke(void);
void ispisi_fps(void);
void ispisi_cuvanje(void);
void ispisi_nisku(int, int, const char*);

#endif /* ISPIS_H */
