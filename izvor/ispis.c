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
    
    /* Ispis broja slika po sekundi
     * (frames per second, FPS) */
    ispisi_fps();
    
    /* Ispis eventualnih poruka u vezi
     * sa cuvanjem i citanjem igre */
    if (por.poruka != NEAKTIVNO){
        ispisi_cuvanje();
    }
    
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

void ispisi_fps(void)
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
        sprintf(fps.niska, "%3d FPS", frps);
        frejm = NEAKTIVNO;
        fps.vreme = vreme.novo;
    }
    
    /* Omogucavanje upotrebe obicnih boja
     * umesto materijala za ispis teksta */
    glEnable(GL_COLOR_MATERIAL);
    
    /* Postavljanje boje teksta; poruka
     * o FPS je neutralne bele boje */
    glColor3f(1.0f, 1.0f, 1.0f);
    
    /* Prestanak upotrebe obicnih boja
     * umesto materijala za ispis teksta */
    glDisable(GL_COLOR_MATERIAL);
    
    /* Ispisivanje poruke o FPS; za polozaj
     * se uzima gornji levi cosak ekrana */
    ispisi_nisku(FPS_POL, FPS_POL, fps.niska);
}

void ispisi_cuvanje(void)
{
    /* Omogucavanje upotrebe obicnih boja
     * umesto materijala za ispis teksta */
    glEnable(GL_COLOR_MATERIAL);
    
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
    
    /* Prestanak upotrebe obicnih boja
     * umesto materijala za ispis teksta */
    glDisable(GL_COLOR_MATERIAL);
    
    /* Ispisivanje poruke prema indikatoru;
     * za polozaj se uzima donji levi cosak */
    int x = FPS_POL;
    int y = glutGet(GLUT_WINDOW_HEIGHT) - FPS_POL;
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

void ispisi_nisku(int x, int y, const char* poruka)
{
    /* Postavljanje relativnih koordinata teksta */
    glRasterPos2i(x, y);
    
    /* Postavljanje poruke na ekran; za izvornu
     * bitmapu odabran je zeljeni ugradjeni font */
    glutBitmapString(GLUT_BITMAP_9_BY_15,
                     (const unsigned char*)poruka);
}
