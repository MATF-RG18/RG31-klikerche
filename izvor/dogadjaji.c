#include "../include/dogadjaji.h"

void na_tipku_dole(unsigned char tipka, int x, int y)
{
    /* Zanemaruje se mesto klika */
    PONISTI(x);
    PONISTI(y);
    
    switch (tipka){
    case ESC:
        /* Prekid programa */
        exit(EXIT_SUCCESS);
    
    case SPACE:
        /* Kliker krece u skok, ali
         * samo ako je igra u toku */
        if (!(tipke & PAUZA)){
            tipke |= SKOK;
        }
        break;
    
    case 'a':
    case 'A':
        /* Kliker se okrece nalevo */
        tipke |= LEVO;
        break;
    
    case 'd':
    case 'D':
        /* Kliker se okrece nadesno */
        tipke |= DESNO;
        break;
    
    case 'e':
    case 'E':
        /* Oko se priblizava */
        tipke |= NAPRED;
        break;
    
    case 'f':
    case 'F':
        /* Promena rezima prikaza */
        fullscreen();
        break;
    
    case 'g':
    case 'G':
        /* Prostom negacijom azurira se
         * indikator rezima za debagovanje;
         * AKT. postaje PAS. i obrnuto */
        debag = !debag;
        break;
    
    case 'k':
    case 'K':
        /* Cuvanje trenutne igre */
        sacuvaj_igru();
        break;
    
    case 'l':
    case 'L':
        /* Citanje sacuvane igre */
        ucitaj_igru();
        break;
    
    case 'p':
    case 'P':
        /* Pauzira se igra ili nastavlja
         * ako je prethodno pauzirana */
        tipke ^= PAUZA;
        
        /* Ponovo se postavlja tajmer ako
         * je igra nastavljena nakon pauze,
         * a usput se i resetuje vreme */
        if (!(tipke & PAUZA)){
            vreme.staro = glutGet(GLUT_ELAPSED_TIME);
            glutTimerFunc(TAJMER, na_tajmer, TAJMER);
        }
        
        /* Zaustavlja se animacija
         * ako je uopste u toku */
        tipke &= ~RESET;
        break;
    
    case 'q':
    case 'Q':
        /* Oko se udaljava */
        tipke |= NAZAD;
        break;
    
    case 'r':
    case 'R':
        /* Resetovanje pogleda, ali
         * samo ako je igra u toku */
        if (!(tipke & PAUZA)){
            tipke |= RESET;
        }
        break;
    
    case 's':
    case 'S':
        /* Kliker se krece nazad */
        tipke |= VRATI;
        break;
    
    case 'w':
    case 'W':
        /* Kliker se krece napred */
        tipke |= KRENI;
        break;
    
    case 'x':
    case 'X':
        /* Oko se spusta */
        tipke |= DOLE;
        break;
    
    case 'z':
    case 'Z':
        /* Oko se podize */
        tipke |= GORE;
        break;
    }
}

void na_tipku_gore(unsigned char tipka, int x, int y)
{
    /* Zanemaruje se mesto klika */
    PONISTI(x);
    PONISTI(y);
    
    switch (tipka){
    case ESC:
        /* Do prekida programa dolazi
         * po pritiskanju ESC tipke;
         * otpustanje nije bitno */
        break;
    
    case SPACE:
        /* Skok je uglavnom animacija;
         * otpustanje tipke nije bitno */
        break;
    
    case 'a':
    case 'A':
        /* Kliker se vise ne okrece nalevo */
        tipke &= ~LEVO;
        break;
    
    case 'd':
    case 'D':
        /* Kliker se vise ne okrece nadesno */
        tipke &= ~DESNO;
        break;
    
    case 'e':
    case 'E':
        /* Oko se vise ne priblizava */
        tipke &= ~NAPRED;
        break;
    
    case 'f':
    case 'F':
        /* Fullscreen je opcija tipa toggle;
         * otpustanje tipke nije bitno */
        break;
    
    case 'g':
    case 'G':
        /* Debag je opcija tipa toggle;
         * otpustanje tipke nije bitno */
        break;
    
    case 'k':
    case 'K':
        /* Cuvanje igre ima trenutni efekat;
         * otpustanje tipke nije bitno */
        break;
    
    case 'l':
    case 'L':
        /* Citanje igre ima trenutni efekat;
         * otpustanje tipke nije bitno */
        break;
    
    case 'p':
    case 'P':
        /* Pauza je opcija tipa toggle;
         * otpustanje tipke nije bitno */
        break;
    
    case 'q':
    case 'Q':
        /* Oko se vise ne udaljava */
        tipke &= ~NAZAD;
        break;
    
    case 'r':
    case 'R':
        /* Resetovanje pogleda je animacija;
         * otpustanje tipke nije bitno */
        break;
    
    case 's':
    case 'S':
        /* Kliker se vise ne krece nazad */
        tipke &= ~VRATI;
        break;
    
    case 'w':
    case 'W':
        /* Kliker se vise ne krece napred */
        tipke &= ~KRENI;
        break;
    
    case 'x':
    case 'X':
        /* Oko se vise ne spusta */
        tipke &= ~DOLE;
        break;
    
    case 'z':
    case 'Z':
        /* Oko se vise ne podize */
        tipke &= ~GORE;
        break;
    }
}
