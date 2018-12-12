#include "../include/osnov.h"

void podesi_biblioteke(int* argc, char** argv)
{
    /* Pokretanje GLUT-a */
    glutInit(argc, argv);
    
    /* Opis: RGB (crvena, zelena, plava) sistem
     * boja, bafer dubine, dva bafera scene */
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
}

void napravi_prozor(void)
{
    /* Pravljenje prozora:
     * dimenzije, polozaj, ime */
    glutInitWindowSize(PROZ_DIM, PROZ_DIM);
    glutInitWindowPosition(PROZ_POL, PROZ_POL);
    glutCreateWindow(APP_IME);
    
    /* Odbaceni pokusaj pravljenja prozora
     * preko GLUT-ove posebne fje za igre;
     * ipak se bolje cini da postoji mogucnost
     * odabira zeljenog: wdwd ili fscr */
    /*glutGameModeString("1366x768:32@60");
    if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)){
        glutEnterGameMode();
    }*/
    
    /* Na pocetku je windowed prikaz,
     * nije aktivan debag rezim, a vreme
     * je takodje postavljeno na nulu */
    fulskrin = PASIVAN;
    debag = PASIVAN;
    vreme.staro = PASIVAN;
    
    /* OpenGL ciscenje prozora */
    glClearColor(PROZ_BOJA, PROZ_BOJA, PROZ_BOJA, PROZ_ALPH);
}

void postavi_svetlo(void)
{
    /* Ukljucivanje dubine */
    glEnable(GL_DEPTH_TEST);
    
    /* Ukljucivanje svetla */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    /* Ambijentalna, difuzna i spekularna
     * boja svetla koje osvetljuje scenu;
     * magicni brojevi koji se po zelji mogu
     * menjati u cilju promene boje svetla */
    GLfloat amb_svetlo[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat dif_svetlo[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat spek_svetlo[] = {0.9f, 0.9f, 0.9f, 1.0f};
    
    /* Postavljanje svojstava svetla */
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb_svetlo);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_svetlo);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spek_svetlo);
}

void napravi_stazu(void)
{
    /* Registrovanje prve liste za stazu */
    staza1 = glGenLists(STAZA);
    
    /* Pravljenje prve liste za stazu */
    glNewList(staza1, GL_COMPILE);
    
    /* Omogucavanje upotrebe obicnih
     * boja umesto materijala za stazu */
    glEnable(GL_COLOR_MATERIAL);
    
    /* Postavljanje boje staze; magicni brojevi
     * koji se po potrebi mogu menjati */
    glColor3f(0.4f, 0.9f, 0.9f);
    
    /* Iscrtavanje staze; magicni brojevi
     * koji se po potrebi mogu menjati;
     * normalizacija je neophodna zbog
     * osvetljenja, a push i pop zbog
     * transformacija klikera */
    glEnable(GL_NORMALIZE);
    glPushMatrix();
        glTranslatef(-18, 0, -1.1);
        glScalef(42, 6, 0.1);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-36, 15.5, -1.1);
        glScalef(6, 25, 0.1);
        glutSolidCube(1);
    glPopMatrix();
    glDisable(GL_NORMALIZE);
    
    /* Prestanak upotrebe obicnih
     * boja umesto materijala za stazu */
    glDisable(GL_COLOR_MATERIAL);
    
    /* Kraj liste za prvu stazu */
    glEndList();
    
    /* Registrovanje druge liste za stazu */
    staza2 = glGenLists(STAZA);
    
    /* Pravljenje liste za drugu stazu */
    glNewList(staza2, GL_COMPILE);
    
    /* Omogucavanje upotrebe obicnih
     * boja umesto materijala za stazu */
    glEnable(GL_COLOR_MATERIAL);
    
    /* Postavljanje boje staze; magicni brojevi
     * koji se po potrebi mogu menjati */
    glColor3f(0.4f, 0.9f, 0.9f);
    
    /* Iscrtavanje staze; magicni brojevi
     * koji se po potrebi mogu menjati;
     * normalizacija je neophodna zbog
     * osvetljenja, a push i pop zbog
     * transformacija klikera */
    glEnable(GL_NORMALIZE);
    glPushMatrix();
        glTranslatef(-18, 0, -1.1);
        glScalef(42, 6, 0.1);
        glutWireCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-36, 15.5, -1.1);
        glScalef(6, 25, 0.1);
        glutWireCube(1);
    glPopMatrix();
    glDisable(GL_NORMALIZE);
    
    /* Prestanak upotrebe obicnih
     * boja umesto materijala za stazu */
    glDisable(GL_COLOR_MATERIAL);
    
    /* Kraj liste za drugu stazu */
    glEndList();
}

void postavi_stazu(void)
{
    /* Pozivanje liste za iscrtavanje staze;
     * crta se poligonalna staza inace, a
     * zicana u slucaju debag rezima */
    if (debag){
        glCallList(staza2);
    } else {
        glCallList(staza1);
    }
}

void fullscreen(void)
{
    /* Ako je trenutni prikaz tipa
     * fullscreen, menja se u pocetni
     * windowed prikaz i obrnuto */
    if (fulskrin == AKTIVAN){
        glutReshapeWindow(PROZ_DIM, PROZ_DIM);
    } else {
        glutFullScreen();
    }
    
    /* Prostom negacijom azurira se
     * indikator fullscreen prikaza;
     * AKT. postaje PAS. i obrnuto */
    fulskrin = !fulskrin;
}

void popravi_vreme(void)
{
    /* Novo proteklo vreme dobavlja
     * ugradjena GLUT-ova funkcija */
    vreme.novo = glutGet(GLUT_ELAPSED_TIME);
    
    /* Vremenski pomeraj, neophodan kako
     * bi se njime pomnozio svaki fizicki
     * pokret; time kretanje biva uniformno
     * i nezavisno od brzine racunara */
    vreme.pom = vreme.novo - vreme.staro;
    
    /* Maksimalnim pomerajem izbegava
     * se prevelika razlika u vremenima */
    if (vreme.pom > POM_MAX){
        vreme.pom = POM_MAX;
    }
    
    /* Novo vreme zastareva */
    vreme.staro = vreme.novo;
}

void sacuvaj_igru(void)
{
    /* Otvaranje fajla sa sacuvanom
     * igrom u rezimu za pisanje */
    FILE* fajl = fopen(SAVEGAME, "w");
    
    /* Ukoliko fajl nije mogao da bude
     * otvoren, zasad se prosto odustaje */
    if (fajl == NULL){
        return;
    }
    
    /* Ne postoji serijalizacija u C-u,
     * ali se cuvanje igre moze simulirati
     * zapisivanjem bitnih promenljivih */
    
    /* Upisivanje parametara oka */
    fprintf(fajl, "%lf %lf %lf\n", oko.r, oko.phi, oko.theta);
    
    /* Upisivanje razlika oka */
    fprintf(fajl, "%d %d %d\n", raz.r, raz.phi, raz.theta);
    
    /* Upisivanje polozaja klikera */
    fprintf(fajl, "%lf %lf %lf\n", klik.x, klik.y, klik.z);
    
    /* Upisivanje skoka i rotacije */
    fprintf(fajl, "%lf %lf\n", klik.s, rot.u);
    
    /* Od tipki je bitno samo da li
     * su u toku skok ili pauza */
    int ntipke = tipke & (SKOK | PAUZA);
    
    /* Upisivanje stanja indikatora,
     * fullscreen sa namerom obrnut */
    fprintf(fajl, "%d %d %d\n", !fulskrin, debag, ntipke);
    
    /* Upisivanje dokumentacionih komentara
     * u fajl pre zatvaranja, bekspejsovi
     * nakrcani zbog esteticnosti niske */
    fputc('\n', fajl);
    fprintf(fajl, "# Sacuvana igra zadrzi pet redova;\n");
    fprintf(fajl, "# detalji se mogu naci u funkciji;\n");
    fprintf(fajl, "# prvi: sferni parametri oka/kamere;\n");
    fprintf(fajl, "# drugi: razlike oka, za resetovanje;\n");
    fprintf(fajl, "# treci: polozaj igracevog klikera;\n");
    fprintf(fajl, "# cetvrti: parametri skoka i rotacije;\n");
    fprintf(fajl, "# peti: stanja indikatora za rezim\n");
    fprintf(fajl, "# prikaza, debag rezim i tipke\n");
    
    /* Zatvaranje fajla */
    fclose(fajl);
}

void ucitaj_igru(void)
{
    /* Otvaranje fajla sa sacuvanom
     * igrom u rezimu za citanje */
    FILE* fajl = fopen(SAVEGAME, "r");
    
    /* Ukoliko fajl nije mogao da bude
     * otvoren ili ne sadrzi sve neophodne
     * podatke, zasad se prosto odustaje */
    if (fajl == NULL || fscanf(fajl, "%*f %*f %*f \
                            %*d %*d %*d \
                            %*f %*f %*f \
                            %*f %*f \
                            %*d %*d %*d") == EOF){
        return;
    }
    
    /* Resetovanje offseta, koji je zbog
     * zprovere pomeren na kraj fajla */
    rewind(fajl);
    
    /* Citanje parametara oka */
    fscanf(fajl, "%lf %lf %lf\n", &oko.r, &oko.phi, &oko.theta);
    
    /* Citanje razlika oka */
    fscanf(fajl, "%d %d %d\n", &raz.r, &raz.phi, &raz.theta);
    
    /* Citanje polozaja klikera */
    fscanf(fajl, "%lf %lf %lf\n", &klik.x, &klik.y, &klik.z);
    
    /* Citanje skoka i rotacije */
    fscanf(fajl, "%lf %lf\n", &klik.s, &rot.u);
    
    /* Citanje stanja indikatora */
    fscanf(fajl, "%d %d %d\n", &fulskrin, &debag, &tipke);
    
    /* Postavljanje fullscreena na stanje
     * pre cuvanja igre, sto je obrnuto od
     * ucitanog obrnutog stanja (dupla
     * negacija daje tacnu tvrdnju) */
    fullscreen();
    
    /* Osvezavanje prozora ako je u toku
     * pauza, kako bi se prikazala nova
     * slika, a ne ostala zaledjena stara */
    if (tipke & PAUZA){
        glutPostRedisplay();
    }
    
    /* Zatvaranje fajla */
    fclose(fajl);
}
