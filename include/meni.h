#ifndef MENI_H
#define MENI_H

#include "main.h"

/* Enumeracija koja opisuje
 * odrednice menija */
enum {RESETUJ, FULLSCREEN, ZICANI,
      SACUVAJ, UCITAJ, PAUZIRAJ, IZADJI};

/* Identifikator menija */
int meni;

/* Deklaracije fja za meni */
void postavi_meni(void);
void na_meni(int);

#endif /* MENI_H */
