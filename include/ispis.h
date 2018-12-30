#ifndef ISPIS_H
#define ISPIS_H

#include "main.h"

/* Opis vremenskih ispisa; posebne poruke
 * cuvanja i citanja igre traju odnosno
 * nestaju nakon tri sekunde */
#define SEKUNDA 1000
#define TRAJANJE 3000

/* Makroi za statistike */
#define STAT_POL 25
#define STAT_VEL 16
#define SEK_U_MIN 60

/* Opis poruke o FPS; polozaj teksta
 * i pomocna struktura sa podacima */
struct fps{
    char niska[7];
    int vreme;
} fps;

/* Struktura koja enkapsulira
 * stopericu koja meri vreme */
struct stoperica{
    int pocetak;
    int starov;
    char niska[8];
} stopw;

/* Enumeracija koja opisuje
 * aktivnost poruka na ekranu;
 * krece od jedinice, posto vec
 * postoji NEAKTIVNO = 0 */
enum {USPESNO_CUVANJE = 1, NEUSPESNO_CUVANJE,
      USPESNO_CITANJE, NEUSPESNO_CITANJE};

/* Struktura koja enkapsulira
 * aktivne poruke cuvanja ili
 * citanja igre na ekranu */
struct poruke{
    int poruka;
    int vreme;
} por;

/* Deklaracije fja za ispis */
void ispisi_poruke(void);
void ispisi_statistike(void);
void ispisi_cuvanje(void);
void ispisi_stanje(void);
void ispisi_nisku(int, int, const char*);

#endif /* ISPIS_H */
