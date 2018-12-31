#ifndef STAZA_H
#define STAZA_H

#include "main.h"

/* Opis staze */
#define STAZA_DIM 21
#define PLOC_DIM 6
#define PLOC_VIS 0.13
#define PREP1_VIS 1.5
#define PREP2_VIS 3

/* Datoteka i teksture */
#define STAZA_DAT "ostalo/staza.txt"
#define STAZA_TEKST "ostalo/sanduk.png"
#define STAZA_KRAJ "ostalo/kraj.png"

/* Enumeracija koja opisuje objekte
 * koji se generisu na stazi */
enum {PROVALIJA, PLOCICA,
      PREPREKA1, PREPREKA2};

/* Struktura koja enkapsulira
 * stazu i njeno iscrtavanje */
struct staza{
    /* Matrica staze */
    int mat[STAZA_DIM][STAZA_DIM];
    
    /* Koordinate cilja */
    struct cilj {
        int x;
        int y;
    } cilj;
    
    /* Tekstura sanduka */
    GLuint tekst;
    
    /* Tekstura za kraj */
    GLuint kraj;
} staza;

/* Deklaracije fja za stazu */
void ucitaj_stazu(void);
void napravi_stazu(void);
void napravi_plocicu(double);

#endif /* STAZA_H */
