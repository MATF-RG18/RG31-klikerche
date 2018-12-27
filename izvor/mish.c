#include "../include/mish.h"

void postavi_mis(void)
{
    /* Funkcija na mis osluskuje dogadjaje
     * misa i javlja koji je taster i gde
     * tacno pritisnut ili otpusten; ovde
     * pamti poziciju pokazivaca misa i
     * upravlja udaljenoscu oka/kamere,
     * kao i kretanjem klikera unapred */
    glutMouseFunc(na_mis);
    
    /* Funkcija na pomeraj obradjuje dogadjaj
     * kretanja stisnutog misa preko ekrana; ovde
     * upravlja vertikalnim i horizontalnim polozajem
     * oka tj. njegovom visinom i okretanjem; ovime
     * dogadjaji misa pokrivaju sve dogadjaje koji
     * imaju veze sa kretanjem oka i klikera */
    glutMotionFunc(na_pomeraj);
    
    /* Postavljanje slicice pokazivaca na
     * saku sa ispruzenim kaziprstom */
    glutSetCursor(GLUT_CURSOR_INFO);
    
    /* Nije neophodno inicijalizovati
     * strukturu sa koordinatama */
    /*mis.x = mis.y = PRAZNO*/
    
    /* Postavljanje menija, koji sluzi da olaksa
     * upotrebu opcija koje nisu u vezi sa kretanjem
     * (osnovna interkativna komponenta igre), a koje su
     * podrazumevano dostupne preko tipki tastature,
     * posto iz korisnicke tacke gledista i nema mnogo
     * svrhe pamtiti koji taster sta radi */
    postavi_meni();
}

void na_mis(int taster, int stanje, int x, int y)
{
    /* Ukoliko je pauza u toku,
     * dogadjaj se zanemaruje */
    if (tipke & PAUZA){
        return;
    }
    
    /* Pamti se pozicija pokazivaca */
    mis.x = x;
    mis.y = y;
    
    switch (stanje){
        /* Ukoliko je registrovan
         * dogadjaj pritiskanja */
        case GLUT_DOWN:
            switch (taster) {
                /* Obrtanjem tocka misa nagore
                 * oko se priblizava klikeru */
                case GLUT_WHEEL_UP:
                    oko_napred();
                    break;
                
                /* Obrtanjem tocka misa nadole
                 * oko se udaljava od kliera */
                case GLUT_WHEEL_DOWN:
                    oko_nazad();
                    break;
                
                /* Po pritisku glavnih tastera,
                 * nista posebno se ne desava; levi
                 * je bitan samo dok se pomera, dok
                 * je desni vezan za meni */
                case GLUT_LEFT_BUTTON:
                case GLUT_RIGHT_BUTTON:
                    break;
                
                /* Pritisak srednjeg tastera
                 * pokrece kliker unapred */
                case GLUT_MIDDLE_BUTTON:
                    tipke |= KRENI;
                    break;
            }
            break;
        
        /* Ukoliko je registrovan
         * dogadjaj otpustanja */
        case GLUT_UP:
            /* Otpustanje srednjeg tastera
             * zaustavlja kretanje klikera */
            if (taster == GLUT_MIDDLE_BUTTON){
                tipke &= ~KRENI;
            }
            break;
    }
}

void na_pomeraj(int x, int y)
{
    /* Ukoliko je pauza u toku,
     * pomeranje se zanemaruje */
    if (tipke & PAUZA){
        return;
    }
    
    /* Promena pozicije pokazivaca misa */
    int pom_x = x - mis.x;
    int pom_y = y - mis.y;

    /* Pamti se nova pozicija pokazivaca misa */
    mis.x = x;
    mis.y = y;
    
    /* Ukoliko je pomeraj po x osi pozitivan,
     * mis je prevucen nadesno, sto znaci da
     * se oko pomera nalevo, i suprotno */
    if (pom_x > PRAZNO){
        oko_levo();
    } else if (pom_x < PRAZNO){
        oko_desno();
    }
    
    /* Ukoliko je pomeraj po y osi pozitivan,
     * mis je prevucen nagore, sto znaci da
     * se i oko pomera nagore, i suprotno, ali
     * samo ukoliko se kliker ne krece, posto
     * je inace tesko ispratiti kretanje */
    if (!(tipke & KRENI) && !(tipke & VRATI)){
        if (pom_y > PRAZNO){
            oko_gore();
        } else if (pom_y < PRAZNO){
            oko_dole();
        }
    }
}

void postavi_meni(void)
{
    /* Pravljenje menija i postavljanje
     * kolbek fje za obradu dogadjaja */
    meni = glutCreateMenu(na_meni);
    
    /* Postavljanje fonta odrednica; nazalost,
     * ova funkcija FreeGLUT-a nije dostupna */
    /*glutSetMenuFont(meni, GLUT_BITMAP_9_BY_15);*/
    
    /* Ubacivanje odrednica menija; imenovanje
     * i povezivanje sa odgovarajucim enumima */
    glutAddMenuEntry("Resetuj oko (R)", RESETUJ);
    glutAddMenuEntry("Promeni rezim prikaza (F)", FULLSCREEN);
    glutAddMenuEntry("Promeni rezim crtanja (G)", IKOSAEDAR);
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
     * predstavlja zeljeni dogadjaj tastature */
    switch (opcija){
        case RESETUJ:
            tipka = 'R';
            break;
        
        case FULLSCREEN:
            tipka = 'F';
            break;
        
        case IKOSAEDAR:
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
    
    /* Pozivanje funkcije za tastaturu */
    na_tipku(tipka, DOLE);
}
