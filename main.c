#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

// Aski kod eskejp karaktera
#define ESC 27

// Parametri sfernih koordinata kamere:
// azimutni ugao phi, polarni ugao theta
// i njihove promene prilikom kretanja
static float phi = 0, theta = M_PI/6,
		d_phi = M_PI/90, d_theta = M_PI/90;

// Deklaracija kolbek funkcija
static void na_tipku(unsigned char tipka, int x, int y);
static void na_prozor(int sirina, int visina);
static void na_prikaz();

int main(int argc, char** argv)
{
	// Inicijalizacija Gluta
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	
	// Pravljenje prozora
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Klikerche");
	
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
	switch (tipka){
	case ESC:
		// Prekid programa
		exit(EXIT_SUCCESS);
	
	case 'a':
	case 'A':
		// Kamera ide levo:
		// smanjivanje azimuta
		phi -= d_phi;
		
		// Popravka jer phi = [0, 2pi)
		if (phi >= 2*M_PI){
			phi -= 2*M_PI;
		}
		
		// Osvezavanje scene
		glutPostRedisplay();
		break;
	
	case 'd':
	case 'D':
		// Kamera ide desno:
		// povecavanje azimuta
		phi += d_phi;
		
		// Popravka jer phi = [0, 2pi)
		if (phi < 0){
			phi += 2*M_PI;
		}
		
		// Osvezavanje scene
		glutPostRedisplay();
		break;
	
	case 'r':
	case 'R':
		// Resetovanje kamere
		phi = 0;
		theta = M_PI/6;
		glutPostRedisplay();
		break;
	
	case 's':
	case 'S':
		// Kamera ide dole:
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
		// Kamera ide gore:
		// pocevacanje polara
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
	gluPerspective(60, (float)sirina/visina, 1, 10);
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
	gluLookAt(5 * cos(theta) * cos(phi),
			5 * cos(theta) * sin(phi),
			5 * sin(theta),
			0, 0, 0, 0, 0, 1);
	
	// Pravljenje kugle tj. klikercheta
	glutWireSphere(1, 20, 20);
	
	// Zamena bafera tj. prikaz slike na ekranu
	glutSwapBuffers();
}
