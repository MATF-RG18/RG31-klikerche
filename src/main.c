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

// Preciznost sfere
#define SFERA_PREC 22

// Aski kod eskejp karaktera
#define ESC 27

// Makro za nekoriscene promenljive
#define PONISTI(x) (void)x

// Struktura koja enkapsulira oko/kameru,
// predstavljeno sfernim koordinatama
static struct oko{
    // Poluprecnik i promena
    GLdouble r, d_r;
    
    // Azimutni ugao i promena
    GLdouble phi, d_phi;
    
    // Polarni ugao i promena
    GLdouble theta, d_theta;
    
    // Dekartove koordinate
    GLdouble x, y, z;
} oko;

// Struktura koja enkapsulira klikerche
static struct kliker{
    // Koordinate centra
    GLdouble x, y, z;
    
    // Poluprecnik
    GLdouble r;
    
    // Preciznost
    GLdouble prec;
} kliker;

// Deklaracije fja za oko/kameru
static void napravi_oko(void);
static void popravi_oko(void);
static void oko_levo(void);
static void oko_desno(void);
static void oko_gore(void);
static void oko_dole(void);
static void oko_napred(void);
static void oko_nazad(void);

// Deklaracije fja za kliker
static void napravi_kliker(void);
static void nacrtaj_kliker(void);

// Deklaracije kolbek funkcija
static void na_tipku(unsigned char, int, int);
static void na_prozor(int, int);
static void na_prikaz(void);

// Deklaracije sablonskih funkcija
static void podesi_biblioteke(int, char**);
static void napravi_prozor(void);
static void postavi_kolbek(void);
static void postavi_svetlo(void);

int main(int arg_br, char** arg_niz)
{
    // Pokretanje Gluta
    podesi_biblioteke(arg_br, arg_niz);
    
    // Pravljenje prozora
    napravi_prozor();
    
    // Postavljanje kolbek funkcija
    postavi_kolbek();
    
    // Postavljanje svetla i materijala
    postavi_svetlo();
    
    // Pravljenje oka/kamere
    napravi_oko();
    
    // Pravljenje klikercheta
    napravi_kliker();
    
    // Glavna petlja Gluta
    glutMainLoop();
    
    exit(EXIT_SUCCESS);
}

static void na_tipku(unsigned char tipka, int x, int y)
{
    // Zanemaruje se mesto klika
    PONISTI(x);
    PONISTI(y);
    
    switch (tipka){
    case ESC:
        // Prekid programa
        exit(EXIT_SUCCESS);
    
    case 'a':
    case 'A':
        oko_levo();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'd':
    case 'D':
        oko_desno();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'e':
    case 'E':
        oko_napred();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'q':
    case 'Q':
        oko_nazad();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'r':
    case 'R':
        // Resetovanje oka/kamere
        napravi_oko();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 's':
    case 'S':
        oko_dole();
        
        // Osvezavanje scene
        glutPostRedisplay();
        break;
    
    case 'w':
    case 'W':
        oko_gore();
        
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
    
    // Postavljanje vidnih parametara
    popravi_oko();
    gluLookAt( oko.x,    oko.y,    oko.z,   // centar oka/kamere
              kliker.x, kliker.y, kliker.z, // centar pogleda
                 0,        0,        1);    // vektor normale
    
    // Crtanje kugle tj. klikercheta
    nacrtaj_kliker();
    
    // Zamena bafera tj. prikaz slike na ekranu
    glutSwapBuffers();
}

static void podesi_biblioteke(int arg_br, char** arg_niz)
{
    // Pokretanje Gluta
    glutInit(&arg_br, arg_niz);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
}

static void napravi_prozor(void)
{
    // Pravljenje prozora
    glutInitWindowSize(PROZ_DIM, PROZ_DIM);
    glutInitWindowPosition(PROZ_POL, PROZ_POL);
    glutCreateWindow(APP_IME);
    
    // OpenGL ciscenje prozora
    glClearColor(0.05, 0.05, 0.05, 0);
}

static void postavi_kolbek(void)
{
    // Postavljanje kolbek funkcija
    glutKeyboardFunc(na_tipku);
    glutReshapeFunc(na_prozor);
    glutDisplayFunc(na_prikaz);
}

static void postavi_svetlo(void)
{
    // Ukljucivanje dubine
    glEnable(GL_DEPTH_TEST);
    
    // Ukljucivanje svetla
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
}

static void napravi_oko(void)
{
    oko.r = 5;
    oko.d_r = 0.15;
    
    oko.phi = 0;
    oko.d_phi = M_PI/90;
    
    oko.theta = M_PI/6;
    oko.d_theta = M_PI/90;
}

static void popravi_oko(void)
{
    oko.x = oko.r * cos(oko.theta) * cos(oko.phi);
    oko.y = oko.r * cos(oko.theta) * sin(oko.phi);
    oko.z = oko.r * sin(oko.theta);
}

static void oko_levo(void)
{
    // Oko se krece levo:
    // smanjivanje azimuta
    oko.phi -= oko.d_phi;
    
    // Popravka jer phi = [0, 2pi)
    if (oko.phi < 0){
        oko.phi += 2*M_PI;
    }
}

static void oko_desno(void)
{
    // Oko se krece desno:
    // povecavanje azimuta
    oko.phi += oko.d_phi;
    
    // Popravka jer phi = [0, 2pi)
    if (oko.phi >= 2*M_PI){
        oko.phi -= 2*M_PI;
    }
}

static void oko_gore(void)
{
    // Oko se krece gore:
    // povecavanje polara
    oko.theta += oko.d_theta;
    
    // Popravka jer theta = [0, pi/2]
    if (oko.theta > M_PI/2){
        oko.theta = M_PI/2;
    }
}

static void oko_dole(void)
{
    // Oko se krece dole:
    // smanjivanje polara
    oko.theta -= oko.d_theta;
    
    // Popravka jer theta = [0, pi/2]
    // Inace je [-pi/2, pi/2], ali ovako
    // se izbegava odlazak ispod scene
    if (oko.theta < 0){
        oko.theta = 0;
    }
}

static void oko_napred(void)
{
    // Oko se priblizava:
    // smanjivanje radijusa
    oko.r -= oko.d_r;
    
    // Popravka jer r = [2, 10]
    if (oko.r < 2){
        oko.r = 2;
    }
}

static void oko_nazad(void)
{
    // Oko se udaljava:
    // povecavanje radijusa
    oko.r += oko.d_r;
    
    // Popravka jer r = [2, 10]
    if (oko.r > 10){
        oko.r = 10;
    }
}


static void napravi_kliker(void)
{
    kliker.x = 0;
    kliker.y = 0;
    kliker.z = 0;
    
    kliker.r = 1;
    
    kliker.prec = SFERA_PREC;
}

static void nacrtaj_kliker(void)
{
    glutWireSphere(kliker.r, kliker.prec, kliker.prec);
}
