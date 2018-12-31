#include "../include/tipke.h"

void na_tipku(unsigned char tipka, int dogadjaj)
{
    switch (tipka){
    case ESC:
        /* Prekid programa, nije
         * bitan dogadjaj tipke */
        napusti_igru("Program prekinut dogadjajem tastature!");
    
    case SPACE:
        /* Kliker krece u skok, ali samo ako
         * je igra u toku, nije prethodni skok
         * aktivan i kliker trenutno ne pada;
         * otpustanje tipke nije bitno */
        if (dogadjaj == DOLE && stanje == U_TOKU
            && klik.s == UGAO_POC && !klik.pad){
            kliker_skok();
        }
        break;
    
    case 'a':
    case 'A':
        /* Kliker se okrece nalevo
         * ili prestaje to da radi */
        switch (dogadjaj) {
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
        switch (dogadjaj) {
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
        switch (dogadjaj) {
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
        if (dogadjaj == DOLE){
            glutFullScreenToggle();
        }
        break;
    
    case 'g':
    case 'G':
        /* Odbaceno azuriranje indikatora
         * ikosaedarskog rezima obrtanjem/negacijom;
         * tipka 'g' asocirala je na debag rezim kod
         * kompilatora GCC, posto je pre tekstura ovaj
         * rezim sluzio da prikaze kotrljanje */
        /*if (dogadjaj == DOLE){
            ikosaedar = !ikosaedar;
        }*/
        
        /* Zapocinjanje igre ili
         * njeno restartovanje */
        if (dogadjaj == DOLE){
            if (stanje == POCETAK){
                zapocni_igru();
            } else {
                restartuj_igru();
            }
        }
        break;
    
    case 'k':
    case 'K':
        /* Cuvanje trenutne igre, ali
         * samo ukoliko je u toku ili
         * je privremeno pauzirana, pri
         * cemu vazi da kliker ne pada */
        if (dogadjaj == DOLE){
            if (klik.pad || (stanje != U_TOKU
                && stanje != PAUZA)){
                por.vreme = vreme.novo;
                por.poruka = NEUSPESNO_CUVANJE;
            } else {
                sacuvaj_igru();
            }
        }
        break;
    
    case 'l':
    case 'L':
        /* Citanje sacuvane igre */
        if (dogadjaj == DOLE){
            ucitaj_igru();
        }
        break;
    
    case 'p':
    case 'P':
        /* Pauzira se igra ili nastavlja
         * ako je prethodno pauzirana */
        if (dogadjaj == DOLE){
            if (stanje == U_TOKU){
                stanje = PAUZA;
            } else if (stanje == PAUZA){
                stanje = U_TOKU;
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
        switch (dogadjaj) {
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
        /* Resetovanje pogleda ili
         * prestanak resetovanja, ali
         * samo ako je igra u toku */
        if (dogadjaj == DOLE && stanje == U_TOKU){
            if (tipke & RESET){
                tipke &= ~RESET;
            } else {
                tipke |= RESET;
            }
        }
        break;
    
    case 's':
    case 'S':
        /* Kliker se krece unazad
         * ili prestaje to da radi */
        switch (dogadjaj) {
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
        switch (dogadjaj) {
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
        switch (dogadjaj) {
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
        switch (dogadjaj) {
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
     * se tipka i tip dogadjaja */
    na_tipku(tipka, DOLE);
}

void na_tipku_gore(unsigned char tipka, int x, int y)
{
    /* Zanemaruje se mesto klika */
    PONISTI(x);
    PONISTI(y);
    
    /* Glavnoj funkciji za obradu
     * dogadjaja tastature prosledjuje
     * se tipka i tip dogadjaja */
    na_tipku(tipka, GORE);
}
