#include <math.h>
#include <GL/glut.h>

// Opis prozora
#define PROZ_DIM 500
#define PROZ_POL 100
#define APP_IME "Klikerche"

// Opis perspektive
#define PERSP_UGAO 60
#define PERSP_BLIZ 1
#define PERSP_DALJ 10

// Aski kod eskejp karaktera
#define ESC 27

// Makro za nepotrebne promenljive
#define PONISTI(x) (void)x

// Parametri sfernih koordinata oka/kamere:
// poluprecnik r, azimutni ugao phi, polarni
// ugao theta i promene prilikom kretanja
static float r = 5, phi = 0, theta = M_PI/6,
             d_r = 0.15, d_phi = M_PI/90, d_theta = M_PI/90;

// Deklaracija kolbek funkcija
static void na_tipku(unsigned char tipka, int x, int y);
static void na_prozor(int sirina, int visina);
static void na_prikaz(void);

int main(int arg_br, char** arg_niz)
{
    // Inicijalizacija Gluta
    glutInit(&arg_br, arg_niz);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    // Pravljenje prozora
    glutInitWindowSize(PROZ_DIM, PROZ_DIM);
    glutInitWindowPosition(PROZ_POL, PROZ_POL);
    glutCreateWindow(APP_IME);
    
    // Ucitavanje kolbek funkcija
    glutKeyboardFunc(na_tipku);
    glutReshapeFunc(na_prozor);
    glutDisplayFunc(na_prikaz);
    
    // Postavljanje OpenGL parametara
    glClearColor(0.05, 0.05, 0.05, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    // Ambijentalna, difuzna i spekularna
    // boja svetla koje osvetljuje scenu
    GLfloat amb_svetlo[] = {0.1, 0.1, 0.1, 1};
    GLfloat dif_svetlo[] = {0.7, 0.7, 0.7, 1};
    GLfloat spek_svetlo[] = {0.9, 0.9, 0.9, 1};
    
    // Postavljanje svojstava svetla
    glEnable(GL_LIGHT0);
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
    
    // Glavna petlja Gluta
    glutMainLoop();
    
    exit(EXIT_SUCCESS);
}

static void na_tipku(unsigned char tipka, int x, int y)
{
    PONISTI(x);
    PONISTI(y);
    
    switch (tipka){
    case ESC:
        // Prekid programa
        exit(EXIT_SUCCESS);
    
    case 'a':
    case 'A':
        // Oko se krece levo:
        // smanjivanje azimuta
        phi -= d_phi;
        
        // Popravka jer phi = [0, 2pi)
        if (phi < 0){
            phi += 2*M_PI;
        }
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'd':
    case 'D':
        // Oko se krece desno:
        // povecavanje azimuta
        phi += d_phi;
        
        // Popravka jer phi = [0, 2pi)
        if (phi >= 2*M_PI){
            phi -= 2*M_PI;
        }
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'e':
    case 'E':
        // Oko se priblizava:
        // smanjivanje radijusa
        r -= d_r;
        
        // Popravka jer r = [2, 10]
        if (r < 2){
            r = 2;
        }
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'q':
    case 'Q':
        // Oko se udaljava:
        // povecavanje radijusa
        r += d_r;
        
        // Popravka jer r = [2, 10]
        if (r > 10){
            r = 10;
        }
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'r':
    case 'R':
        // Resetovanje oka/kamere
        phi = 0;
        theta = M_PI/6;
        glutPostRedisplay();
        break;
    
    case 's':
    case 'S':
        // Oko se krece dole:
        // smanjivanje polara
        theta -= d_theta;
        
        // Popravka jer theta = [0, pi/2]
        // Inace je [-pi/2, pi/2], ali ovako
        // se izbegava odlazak ispod scene
        if (theta < 0){
            theta = 0;
        }
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'w':
    case 'W':
        // Oko se krece gore:
        // povecavanje polara
        theta += d_theta;
        
        // Popravka jer theta = [0, pi/2]
        if (theta > M_PI/2){
            theta = M_PI/2;
        }
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    }
}

static void na_prozor(int sirina, int visina)
{
    // Postavljanje pogleda
    glViewport(0, 0, sirina, visina);
    
    // Podesavanje projekcije
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(PERSP_UGAO, (float)sirina/visina,
                   PERSP_BLIZ, PERSP_DALJ);
}

static void na_prikaz(void)
{
    // Osvezavanje prozora
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Postavljanje matrice transformacije
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Polozaj tackastog svetla i njegovo
    // postavljanje pre vidnih parametara,
    // kako bi ono pratilo kretanje kamere
    GLfloat svetlo_pol[] = {0, 0, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, svetlo_pol);
    
    // Postavljanje vidnih parametara u skladu sa
    // matematickom formulacijom sfernih koordinata
    gluLookAt(r * cos(theta) * cos(phi),
              r * cos(theta) * sin(phi),
              r * sin(theta),
              0, 0, 0, 0, 0, 1);
    
    // Pravljenje kugle tj. klikercheta
    glutWireSphere(1, 20, 20);
    
    // Zamena bafera tj. prikaz slike na ekranu
    glutSwapBuffers();
}
