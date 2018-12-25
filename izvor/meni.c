#include "../include/meni.h"

void postavi_meni(void)
{
    /* Pravljenje menija i postavljanje
     * kolbek fje za obradu dogadjaja */
    meni = glutCreateMenu(na_meni);
    
    /* Postavljanje fonta odrednica; nazalost,
     * ova funkcija FreeGLUT-a nije dostupna */
    /*glutSetMenuFont(meni, GLUT_BITMAP_HELVETICA_10);*/
    
    /* Ubacivanje odrednica menija; imenovanje
     * i povezivanje sa odgovarajucim enumima;
     * odrednice odgovaraju svakom dogadjaju
     * tastature koji nije u vezi sa kretanjem */
    glutAddMenuEntry("Resetuj oko (R)", RESETUJ);
    glutAddMenuEntry("Promeni rezim prikaza (F)", FULLSCREEN);
    glutAddMenuEntry("Promeni rezim crtanja (G)", ZICANI);
    glutAddMenuEntry("Sacuvaj igru (K)", SACUVAJ);
    glutAddMenuEntry("Ucitaj igru (L)", UCITAJ);
    glutAddMenuEntry("Pauziraj igru (P)", PAUZIRAJ);
    glutAddMenuEntry("Izadji iz igre (Esc)", IZADJI);
    
    /* Povezivanje menija sa
     * desnim klikom misa */
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void na_meni(int opcija)
{
    /* Meni radi tako sto simulira dogadjaje
     * tastature, a time i zeljene radnje */
    unsigned char tipka;
    
    /* Tipka se postavlja na odgovarajucu, koja
     * predstavlja zeljeni dogadgaj tastature */
    switch (opcija){
        case RESETUJ:
            tipka = 'R';
            break;
        
        case FULLSCREEN:
            tipka = 'F';
            break;
        
        case ZICANI:
            tipka = 'G';
            break;
        
        case SACUVAJ:
            tipka = 'K';
            break;
        
        case UCITAJ:
            tipka = 'L';
            break;
        
        case PAUZIRAJ:
            tipka = 'P';
            break;
        
        case IZADJI:
            tipka = ESC;
            break;
    }
    
    /* Pozivanje kolbeka za tastaturu */
    na_tipku(tipka, DOLE);
}
