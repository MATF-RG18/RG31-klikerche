#include "osnov.h"

void podesi_biblioteke(int arg_br, char** arg_niz)
{
    // Pokretanje Gluta
    glutInit(&arg_br, arg_niz);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
}

void napravi_prozor(void)
{
    // Pravljenje prozora
    glutInitWindowSize(PROZ_DIM, PROZ_DIM);
    glutInitWindowPosition(PROZ_POL, PROZ_POL);
    glutCreateWindow(APP_IME);
    
    // OpenGL ciscenje prozora
    glClearColor(0.05, 0.05, 0.05, 0);
}

void postavi_kolbek(void)
{
    // Postavljanje kolbek funkcija
    glutKeyboardFunc(na_tipku);
    glutReshapeFunc(na_prozor);
    glutDisplayFunc(na_prikaz);
}

void postavi_svetlo(void)
{
    // Ukljucivanje dubine
    glEnable(GL_DEPTH_TEST);
    
    // Ukljucivanje svetla
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Ambijentalna, difuzna i spekularna
    // boja svetla koje osvetljuje scenu
    GLfloat amb_svetlo[] = {0.1, 0.1, 0.1, 1};
    GLfloat dif_svetlo[] = {0.7, 0.7, 0.7, 1};
    GLfloat spek_svetlo[] = {0.9, 0.9, 0.9, 1};
    
    // Postavljanje svojstava svetla
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb_svetlo);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_svetlo);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spek_svetlo);
    
    // Ambijentalna, difuzna i spekularna
    // refleksija materijala objekata na sceni
    GLfloat amb_ref[] = {0.3, 0.7, 0.3, 1};
    GLfloat dif_ref[] = {0.2, 1, 0.2, 1};
    GLfloat spek_ref[] = {1, 1, 1, 1};
    
    // Glatkost materijala
    GLfloat glatkost = 100;
    
    // Postavljanje svojstava materijala
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb_ref);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_ref);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spek_ref);
    glMaterialf(GL_FRONT, GL_SHININESS, glatkost);
}
