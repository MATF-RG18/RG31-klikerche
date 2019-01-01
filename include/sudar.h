#ifndef SUDAR_H
#define SUDAR_H

#include "main.h"

/* Opis pada */
#define KLIK_PAD 0.008
#define KLIK_PADV -74
#define KLIK_PADB 2.5
#define OKO_PAD 10
#define OKO_PADP 150

/* Dodatni opis skoka */
#define SKOK_VIS 2.75
/*enum {SKOK_NIJE, SKOK_KRAJ};*/

/* Struktura koja enkapsulira
 * dogadjaje u vezi sa sudarima */
struct sudar{
    /* Indikator da li je kliker
     * preblizu visem polju */
    int preblizu;
    
    /* Visina starog polja */
    double svis;
    
    /* Trenutni smer kretanja */
    int smer;
} sudar;

/* Deklaracija fja za sudare */
void kliker_skok(void);
void kliker_pad(void);
void obradi_sudare(void);
double nadji_visinu(int, int);
int dovoljno_blizu_cilja(void);
void oko_iznad(void);
void game_over(void);

#endif /* SUDAR_H */
