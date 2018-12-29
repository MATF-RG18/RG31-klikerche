#ifndef CUVANJE_H
#define CUVANJE_H

#include "main.h"

/* Ime sacuvane igre */
#define SAVEGAME "ostalo/savegame.txt"

/* Velicina test bafera */
#define TEST_MAX 100

/* Deklaracije funkcija za
 * cuvanje i citanje igre */
void sacuvaj_igru(void);
void ucitaj_igru(void);

#endif /* CUVANJE_H */
