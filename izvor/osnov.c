#include "osnov.h"

void podesi_biblioteke(int* argc, char** argv)
{
    // Pokretanje Gluta
    glutInit(argc, argv);
    
    /* Opis: RGB (crvena, zelena, plava) sistem
       boja, bafer dubine, dva bafera scene */
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
}

void napravi_prozor(void)
{
    /* Pravljenje prozora:
       dimenzije, polozaj, ime */
    glutInitWindowSize(PROZ_DIM, PROZ_DIM);
    glutInitWindowPosition(PROZ_POL, PROZ_POL);
    glutCreateWindow(APP_IME);
    
    // OpenGL ciscenje prozora
    glClearColor(PROZ_BOJA, PROZ_BOJA, PROZ_BOJA, PROZ_ALPH);
}

void postavi_svetlo(void)
{
    // Ukljucivanje dubine
    glEnable(GL_DEPTH_TEST);
    
    // Ukljucivanje svetla
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    /* Ambijentalna, difuzna i spekularna
       boja svetla koje osvetljuje scenu,
       magicni brojevi koji se po zelji mogu
       menjati u cilju promene boje svetla */
    GLfloat amb_svetlo[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat dif_svetlo[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat spek_svetlo[] = {0.9f, 0.9f, 0.9f, 1.0f};
    
    // Postavljanje svojstava svetla
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb_svetlo);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_svetlo);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spek_svetlo);
}

void postavi_stazu(void)
{
    /* Ambijentalna, difuzna i spekularna
       refleksija materijala generisane staze,
       magicni brojevi koji se po zelji mogu
       menjati u cilju promene boje terena */
    GLfloat amb_ref[] = {0.4f, 0.9f, 0.9f, 1.0f};
    GLfloat dif_ref[] = {0.4f, 0.9f, 0.9f, 1.0f};
    GLfloat spek_ref[] = {0.4f, 0.9f, 0.9f, 1.0f};
    
    // Postavljanje svojstava staze
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb_ref);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_ref);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spek_ref);
    glMateriali(GL_FRONT, GL_SHININESS, GLATKOST);
    
    /* Postavljanje same staze, opet su posredi
       magicni brojevi koji se po zelji mogu
       menjati u cilju promene velicine terena */
    glBegin(GL_POLYGON);
        glVertex3i(-3,  3, -1);
        glVertex3i( 3,  3, -1);
        glVertex3i( 3, -3, -1);
        glVertex3i(-3, -3, -1);
    glEnd();
}
