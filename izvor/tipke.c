#include "../include/tipke.h"

void na_tipku(unsigned char tipka, int stanje)
{
    switch (tipka){
    case ESC:
        /* Prekid programa, nije
         * bitno stanje tipke */
        exit(EXIT_SUCCESS);
    
    case SPACE:
        /* Kliker krece u skok, ali
         * samo ako je igra u toku;
         * otpustanje nije bitno */
        if (stanje == DOLE && !(tipke & PAUZA)){
            tipke |= SKOK;
        }
        break;
    
    case 'a':
    case 'A':
        /* Kliker se okrece nalevo
         * ili prestaje to da radi */
        switch (stanje) {
            case DOLE:
                tipke |= LEVO;
                break;
            case GORE:
                tipke &= ~LEVO;
                break;
        }
        break;
    
    case 'd':
    case 'D':
        /* Kliker se okrece nadesno
         * ili prestaje to da radi */
        switch (stanje) {
            case DOLE:
                tipke |= DESNO;
                break;
            case GORE:
                tipke &= ~DESNO;
                break;
        }
        break;
    
    case 'e':
    case 'E':
        /* Oko se priblizava klikeru
         * ili prestaje to da radi */
        switch (stanje) {
            case DOLE:
                tipke |= NAPRED;
                break;
            case GORE:
                tipke &= ~NAPRED;
                break;
        }
        break;
    
    case 'f':
    case 'F':
        /* Promena rezima prikaza */
        if (stanje == DOLE){
            glutFullScreenToggle();
        }
        break;
    
    case 'g':
    case 'G':
        /* Azuriranje indikatora ikosaedarskog
         * rezima prostim obrtanjem/negacijom;
         * tipka 'g' asocira na debag rezim kod
         * kompilatora GCC, posto u igri ovaj
         * rezim sluzi da prikaze kotrljanje */
        if (stanje == DOLE){
            ikosaedar = !ikosaedar;
        }
        break;
    
    case 'k':
    case 'K':
        /* Cuvanje trenutne igre */
        if (stanje == DOLE){
            sacuvaj_igru();
        }
        break;
    
    case 'l':
    case 'L':
        /* Citanje sacuvane igre */
        if (stanje == DOLE){
            ucitaj_igru();
        }
        break;
    
    case 'p':
    case 'P':
        /* Pauzira se igra ili nastavlja
         * ako je prethodno pauzirana */
        if (stanje == DOLE){
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
        }
        break;
    
    case 'q':
    case 'Q':
        /* Oko se udaljava od klikera
         * ili prestaje to da radi */
        switch (stanje) {
            case DOLE:
                tipke |= NAZAD;
                break;
            case GORE:
                tipke &= ~NAZAD;
                break;
        }
        break;
    
    case 'r':
    case 'R':
        /* Resetovanje pogleda, ali
         * samo ako je igra u toku */
        if (stanje == DOLE && !(tipke & PAUZA)){
            tipke |= RESET;
        }
        break;
    
    case 's':
    case 'S':
        /* Kliker se krece unazad
         * ili prestaje to da radi */
        switch (stanje) {
            case DOLE:
                tipke |= VRATI;
                break;
            case GORE:
                tipke &= ~VRATI;
                break;
        }
        break;
    
    case 'w':
    case 'W':
        /* Kliker se krece napred
         * ili prestaje to da radi */
        switch (stanje) {
            case DOLE:
                tipke |= KRENI;
                break;
            case GORE:
                tipke &= ~KRENI;
                break;
        }
        break;
    
    case 'x':
    case 'X':
        /* Oko se spusta prema zemlji
         * ili prestaje to da radi */
        switch (stanje) {
            case DOLE:
                tipke |= NADOLE;
                break;
            case GORE:
                tipke &= ~NADOLE;
                break;
        }
        break;
    
    case 'z':
    case 'Z':
        /* Oko se podize od zemlje
         * ili prestaje to da radi */
        switch (stanje) {
            case DOLE:
                tipke |= NAGORE;
                break;
            case GORE:
                tipke &= ~NAGORE;
                break;
        }
        break;
    }
}

void na_tipku_dole(unsigned char tipka, int x, int y)
{
    /* Zanemaruje se mesto klika */
    PONISTI(x);
    PONISTI(y);
    
    /* Glavnoj funkciji za obradu
     * dogadjaja tastature prosledjuje
     * se tipka i njeno stanje */
    na_tipku(tipka, DOLE);
}

void na_tipku_gore(unsigned char tipka, int x, int y)
{
    /* Zanemaruje se mesto klika */
    PONISTI(x);
    PONISTI(y);
    
    /* Glavnoj funkciji za obradu
     * dogadjaja tastature prosledjuje
     * se tipka i njeno stanje */
    na_tipku(tipka, GORE);
}
