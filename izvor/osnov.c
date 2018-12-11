#include "osnov.h"

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
    
    /* Na pocetku je windowed prikaz */
    full_screen = !SCREEN_FULL;
    
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
    /* Registrovanje liste za iscrtavanje staze */
    staza = glGenLists(STAZA);
    
    /* Pravljenje liste za iscrtavanje staze */
    glNewList(staza, GL_COMPILE);
    
    /* Omogucavanje upotrebe obicnih
     * boja umesto materijala za stazu */
    glEnable(GL_COLOR_MATERIAL);
    
    /* Postavljanje boje staze; magicni brojevi
     * koji se po potrebi mogu menjati */
    glColor3f(0.4f, 0.9f, 0.9f);
    
    /* Iscrtavanje staze; magicni brojevi
     * koji se po potrebi mogu menjati */
    glBegin(GL_LINE_LOOP);
        glVertex3i( 3, -3, -1);
        glVertex3i( 3,  3, -1);
        glVertex3i(-24,  3, -1);
        glVertex3i(-24, 20, -1);
        glVertex3i(-30, 20, -1);
        glVertex3i(-30, -3, -1);
    glEnd();
    
    /* Prestanak upotrebe obicnih
     * boja umesto materijala za stazu */
    glDisable(GL_COLOR_MATERIAL);
    
    /* Kraj liste za iscrtavanje staze */
    glEndList();
}

void postavi_stazu(void)
{
    /* Pozivanje liste za iscrtavanje staze */
    glCallList(staza);
}
