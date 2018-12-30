#include "../include/ispis.h"

void ispisi_poruke(void)
{
    /* Odabir matrice projekcije za trenutnu, njeno
     * kopiranje i ucitavanje jedinicne matrice */ 
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    /* Odabir matrice modela i pogleda za trenutnu,
     * njeno kopiranje i ucitavanje jedinicne matrice */ 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    /* Postavljanje ortografske projekcije koja
     * se prostire preko cele oblasti prikaza; na
     * ovaj nacin ce paralelno projektovani tekst
     * biti prelepljen preko prethodno iscrtane
     * perspektivno projektovane scene; visinske
     * koordinate su obrnute kako bi, komfora radi,
     * poruka o FPS imala nepromenljiv polozaj */
    gluOrtho2D(POGLED, glutGet(GLUT_WINDOW_WIDTH),
               glutGet(GLUT_WINDOW_HEIGHT), POGLED);
    
    /* Iskljucivanje osvetljenja, kako prethodna
     * iscrtavanja ne bi uticala na izgled teksta */
    glDisable(GL_LIGHTING);
    
    /* Omogucavanje upotrebe obicnih boja
     * umesto materijala za ispis teksta */
    glEnable(GL_COLOR_MATERIAL);
    
    /* Ispis statistika igre: broja slika
     * po sekundi (frames per second, FPS)
     * i proteklog vremena od pocetka igre */
    ispisi_statistike();
    
    /* Ispis eventualnih poruka u vezi
     * sa cuvanjem i citanjem igre */
    if (por.poruka != NEAKTIVNO){
        ispisi_cuvanje();
    }
    
    /* Ispis poruke o stanju */
    ispisi_stanje();
    
    /* Prestanak upotrebe obicnih boja
     * umesto materijala za ispis teksta */
    glDisable(GL_COLOR_MATERIAL);
    
    /* Ponovno ukljucivanje osvetljenja */
    glEnable(GL_LIGHTING);
    
    /* Odabir matrice projekcije za tekucu
     * i odbacivanje kopirane matrice */
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    /* Odabir matrice modela i pogleda
     * i odbacivanje kopirane matrice */
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void ispisi_statistike(void)
{
    /* Staticki brojac koji prebrojava slike koje
     * se prikazuju pre nego sto prodje sekund */
    static int frejm = NEAKTIVNO;
    frejm++;
    
    /* Izracunavanje vremenskog pomeraja */
    int pomeraj = vreme.novo - fps.vreme;
    
    /* Ako je pomeraj veci od sekunde, niska
     * koja cuva FPS i vreme se azuriraju, a
     * brojac resetuje postavljanjem na nulu;
     * tacan prebacaj pomeraja zanemaruje se
     * ukoliko je manji od jedne sekunde */
    if (pomeraj >= SEKUNDA){
        int frps = frejm * SEKUNDA / pomeraj;
        sprintf(fps.niska, "%2d FPS", frps);
        frejm = NEAKTIVNO;
        fps.vreme = vreme.novo;
    }
    
    /* Izracunavanje stopericinog pomeraja, sto
     * je zapravo razlika izmedju trenutnog vremena
     * i vremena provedenog u mirovanju/pauzi, ali
     * i pocetka pokretanja stoperice tj. nove igre */
    pomeraj = vreme.novo - stopw.pocetak - vreme.pauza;
    
    /* Ako je pomeraj za makar jednu sekundu veci
     * od prethodnog vremena azuriranja, moze opet
     * doci do azuriranja i niske i vremena; slicno
     * kao kod FPS, tacan prebacaj pomeraja zanemaruje
     * se ukoliko je manji od jedne sekunde */
    if (pomeraj >= stopw.starov + SEKUNDA){
        int sek = pomeraj / SEKUNDA;
        sprintf(stopw.niska, "%02dm:%02ds",
                             sek/SEK_U_MIN, sek%SEK_U_MIN);
        stopw.starov = pomeraj;
    }
    
    /* Pravljenje kumulativne niske
     * sa statistikama igre */
    char statistike[STAT_VEL];
    strcpy(statistike, fps.niska);
    strcat(statistike, ", ");
    strcat(statistike, stopw.niska);
    
    /* Postavljanje boje teksta; poruka o
     * statistikama je neutralne bele boje */
    glColor3f(1.0f, 1.0f, 1.0f);
    
    /* Ispisivanje poruke o statistikama;
     * polozaj je gornji levi cosak ekrana */
    ispisi_nisku(STAT_POL, STAT_POL, statistike);
}

void ispisi_cuvanje(void)
{
    /* Postavljanje boje teksta; poruke uspeha
     * su svetlozelene, a neuspeha crvene boje */
    switch (por.poruka){
        case USPESNO_CUVANJE:
        case USPESNO_CITANJE:
            glColor3f(0.2f, 1.0f, 0.0f);
            break;
        
        case NEUSPESNO_CUVANJE:
        case NEUSPESNO_CITANJE:
            glColor3f(1.0f, 0.2f, 0.0f);
            break;
    }
    
    /* Ispisivanje poruke prema indikatoru;
     * za polozaj se uzima donji levi cosak */
    int x = STAT_POL;
    int y = glutGet(GLUT_WINDOW_HEIGHT) - STAT_POL;
    switch (por.poruka){
        case USPESNO_CUVANJE:
            ispisi_nisku(x, y, "Uspesno cuvanje igre!");
            break;
        
        case NEUSPESNO_CUVANJE:
            ispisi_nisku(x, y, "Neuspesno cuvanje igre!");
            break;
        
        case USPESNO_CITANJE:
            ispisi_nisku(x, y, "Uspesno citanje igre!");
            break;
        
        case NEUSPESNO_CITANJE:
            ispisi_nisku(x, y, "Neuspesno citanje igre!");
            break;
    }
}

void ispisi_stanje(void)
{
    /* Postavljanje boje teksta; poruka
     * o stanju je neutralne bele boje */
    glColor3f(1.0f, 1.0f, 1.0f);
    
    /* Ispisuje se poruka ispod FPS-a
     * u zavisnosti od stanja igre */
    switch (stanje){
        /* Na pocetku se korisnik upoznaje sa igrom */
        case POCETAK:
            ispisi_nisku(STAT_POL, 2*STAT_POL,
            "DOBRO DOSLI U IGRU KLIKERCHE!\nKretanje: 'W', 'A', 'S', 'D'\nKamera: 'Q', 'E', 'Z', 'X'\nOstalo: tastatura i mis\nZadatak: dospeti do cilja!\nZa pocetak igre pritisnite 'G'\nZa izlaz pritisnite 'Esc'");
            break;
        
        /* U toku igre moguce je restartovati
         * je ili jednostavno napustiti */
        case U_TOKU:
            ispisi_nisku(STAT_POL, 2*STAT_POL,
            "IGRA JE U TOKU!\nPozurite do cilja!\nZa restart pritisnite 'G'\nZa izlaz pritisnite 'Esc'");
            break;
        
        /* U toku pauze je moguce nastaviti sa
         * igrom ili je jednostavno napustiti */
        case PAUZA:
            ispisi_nisku(STAT_POL, 2*STAT_POL,
            "IGRA JE PAUZIRANA!\nPrijatan odmor!\nZa nastavak pritisnite 'P'\nZa restart pritisnite 'G'\nZa izlaz pritisnite 'Esc'");
            break;
        
        /* Kada se stigne do cilja... */
        case CESTITKE:
            break;
        
        /* Kada se padne u provaliju... */
        case GAME_OVER:
            break;
    }
}

void ispisi_nisku(int x, int y, const char* poruka)
{
    /* Postavljanje relativnih koordinata teksta */
    glRasterPos2i(x, y);
    
    /* Postavljanje poruke na ekran; za izvornu
     * bitmapu odabran je zeljeni ugradjeni font */
    glutBitmapString(GLUT_BITMAP_9_BY_15,
                     (const unsigned char*)poruka);
}
