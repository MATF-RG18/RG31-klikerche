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
    
    /* Odbaceni pokusaj fantomskog pozivanja
     * obe liste kako bi bile spremne za dalje
     * iscrtavanje; slicni pokusaji ubacivanja
     * u display fju takodje su propali; naime,
     * problem je sto iz nekog razloga dolazi
     * do kocenja prilikom prvog ulaska u debag
     * rezim, ali izgleda da tome nema spasa;
     * probane su i razne druge stvari, kao sto
     * je rezim liste GL_COMPILE_AND_EXECUTE */
    /*glCallList(staza1);
    glCallList(staza2);*/
}

void postavi_stazu(void)
{
    /* Pozivanje liste za iscrtavanje staze;
     * crta se popunjena staza inace, a
     * zicana u slucaju debag rezima */
    if (debag){
        glCallList(staza2);
    } else {
        glCallList(staza1);
    }
}
