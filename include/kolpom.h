#ifndef KOLPOM_H
#define KOLPOM_H

#include "main.h"

/* Ime sacuvane igre */
#define SAVEGAME "savegame.txt"

/* Deklaracije funkcija koje
 * pozivaju kolbek funkcije */
void fullscreen(void);
void popravi_vreme(void);
void sacuvaj_igru(void);
void ucitaj_igru(void);

#endif /* KOLPOM_H */
