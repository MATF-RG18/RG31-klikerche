#include "../include/scena.h"

void napravi_scenu(void)
{
    /* Pravljenje tekstura za stazu/teren; one se
     * prave pomocu biblioteke SOIL ucitavanjem u
     * podrazumevanom rezimu, a prave im se novi
     * identifikatori, kao i propratne mipmape, dok
     * se tekstura pozadine obrce po y osi; ovime
     * SOIL postedjuje rukovanja sa redudantnim
     * fjama poput glGenTextures() i slicnim; same
     * teksture su stock slike sa interneta */
    scena.pozt = SOIL_load_OGL_texture(SCENA_POZT,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    scena.zaklop = SOIL_load_OGL_texture(SCENA_ZAKL,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    scena.staza = SOIL_load_OGL_texture(STAZA_TEKST,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    scena.kraj = SOIL_load_OGL_texture(STAZA_KRAJ,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    
    /* Iscrtavanje pozadine resava se preko
     * GLU-ovog quadric valjka, posto on
     * ima ugradjenu podrsku za teksture;
     * pravi se novi quadric i sugerise mu
     * se da prihvati aktivnu teksturu */
    scena.obj = gluNewQuadric();
    gluQuadricTexture(scena.obj, GLU_TRUE);
    
    /* Registrovanje liste za scenu */
    scena.lista = glGenLists(AKTIVNO);
    
    /* Pravljenje liste za scenu */
    glNewList(scena.lista, GL_COMPILE);
    
    /* Ukljucivanje 2D tekstura i vezivanje
     * one namenjene za iscrtavanje pozadine */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scena.pozt);
    
    /* Pravljenje pozadine */
    napravi_pozadinu();
    
    /* Vezivanje teksture za iscrtavanje staze */
    glBindTexture(GL_TEXTURE_2D, scena.staza);
    
    /* Pravljenje staze */
    napravi_stazu();
    
    /* Iskljucivanje 2D tekstura */
    glBindTexture(GL_TEXTURE_2D, NEAKTIVNO);
    glDisable(GL_TEXTURE_2D);
    
    /* Kraj liste za scenu */
    glEndList();
}

void napravi_pozadinu(void)
{
    /* Refleksija materijala generisane scene;
     * magicni brojevi koji se po zelji mogu
     * menjati; trenutno staza odbija sve svetlo,
     * pa bi bila bela da nema teksture */
    GLfloat refl[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, refl);
    
    /* Iscrtavanje pozadine kao quadric valjka */
    glTranslated(0, 0, -POZ_VIS/2.);
    gluCylinder(scena.obj, POZ_DIM, POZ_DIM,
                POZ_VIS, POZ_PREC, POZ_PREC);
    glTranslated(0, 0, POZ_VIS/2.);
    
    /* Odbaceno iscrtavanje krugova
     * koji zatvaraju pozadinu */
    /*double u;
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, -1);
    glTexCoord2i(0, 0);
    glVertex3f(0, 0, -POZ_VIS/2.);
    for(u = 0; u <= 2*M_PI + M_PI/20; u += M_PI/20){
        if ((int)(20*u/M_PI) % 3 == 0){
            glTexCoord2i(0, 1);
        } else if ((int)(20*u/M_PI) % 3 == 1){
            glTexCoord2i(1, 0);
        } else {
            glTexCoord2i(1, 1);
        }
        glVertex3f(POZ_DIM * cos(u), POZ_DIM *sin(u), -POZ_VIS/2.);
    }
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1);
    glTexCoord2i(0, 0);
    glVertex3f(0, 0, POZ_VIS/2.);
    for(u = 0; u <= 2*M_PI + M_PI/20; u += M_PI/20){
        if ((int)(20*u/M_PI) % 3 == 0){
            glTexCoord2i(0, 1);
        } else if ((int)(20*u/M_PI) % 3 == 1){
            glTexCoord2i(1, 0);
        } else {
            glTexCoord2i(1, 1);
        }
        glVertex3f(POZ_DIM * cos(u), POZ_DIM *sin(u), POZ_VIS/2.);
    }
    glEnd();*/
    
    /* Vezivanje teksture za iscrtavanje zaklopa */
    glBindTexture(GL_TEXTURE_2D, scena.zaklop);
    
    /* Iscrtavanje kvadrata koji zaklapaju pozadinu */
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2i(0, 1);
    glVertex3f(-POZ_DIM, -POZ_DIM, -POZ_VIS/2.);
    glTexCoord2i(1, 1);
    glVertex3f(-POZ_DIM, POZ_DIM, -POZ_VIS/2.);
    glTexCoord2i(1, 0);
    glVertex3f(POZ_DIM, POZ_DIM, -POZ_VIS/2.);
    glTexCoord2i(0, 0);
    glVertex3f(POZ_DIM, -POZ_DIM, -POZ_VIS/2.);
    
    glNormal3f(0, 0, -1);
    glTexCoord2i(0, 1);
    glVertex3f(-POZ_DIM, -POZ_DIM, POZ_VIS/2.);
    glTexCoord2i(1, 1);
    glVertex3f(-POZ_DIM, POZ_DIM, POZ_VIS/2.);
    glTexCoord2i(1, 0);
    glVertex3f(POZ_DIM, POZ_DIM, POZ_VIS/2.);
    glTexCoord2i(0, 0);
    glVertex3f(POZ_DIM, -POZ_DIM, POZ_VIS/2.);
    glEnd();
}

void napravi_stazu(void)
{
    /* Iscrtavanje staze; magicni brojevi
     * koji se po potrebi mogu menjati; push
     * i pop su neophodni zbog kretanja tj.
     * inace transformacija klikera, dok se
     * zbog dobrog osvetljenja ne moze bez
     * normalizacije upravnih vektora */
    glEnable(GL_NORMALIZE);
    glPushMatrix();
    
    /* Spustanje staze ispod klikera
     * i pravljenje prve plocice */
    glTranslatef(0, 0, -1.13);
    napravi_plocicu();
    
    /* Pravljenje jos sest plocica
     * duz x ose; produzavanje puta */
    int i;
    for (i = 0; i < 6; i++){
        glTranslatef(-6, 0, 0);
        napravi_plocicu();
    }
    
    /* Pravljenje jos tri plocice
     * duz y ose; malo skretanje */
    for (i = 0; i < 3; i++){
        glTranslatef(0, 6, 0);
        napravi_plocicu();
    }
    
    /* Ukljucivanje teksture za kraj
     * i iscrtavanje zavrsne plocice */
    glBindTexture(GL_TEXTURE_2D, scena.kraj);
    glTranslatef(0, 6, 0);
    napravi_plocicu();
    
    /* Kraj iscrtavanja, a samim tim
     * i potrebe za normalizacijom */
    glPopMatrix();
    glDisable(GL_NORMALIZE);
}

void napravi_plocicu(void)
{
    /* Ideja za makroizovano icrtavanje plocica
     * preuzeta je direktno iz implementacije fje
     * glutSolidCube() biblioteke FreeGLUT; doradjena
     * je tako da bude skalirana i teksturirana */
    
    /* Normale i teksture su direktno definisane
     * koordinatama, a temena znakom ispred unapred
     * izracunatih vrednosti koordinata prema skali */
    #define N(a,b,c) glNormal3i(a, b, c)
    #define T(a, b) glTexCoord2i(a, b)
    #define V(a,b,c) glVertex3f(a 3, b 3, c 0.13)
    
    /* Plocice se icrtavaju kao skup cetvorouglova */
    glBegin(GL_QUADS);
    
    /* Crta se prednja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(1, 0, 0);
    T(0, 1); V(+, -, +);
    T(0, 0); V(+, -, -);
    T(1, 0); V(+, +, -);
    T(1, 1); V(+, +, +);
    
    /* Crta se desna strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, 1, 0);
    T(0, 1); V(+, +, +);
    T(0, 0); V(+, +, -);
    T(1, 0); V(-, +, -);
    T(1, 1); V(-, +, +);
    
    /* Crta se gornja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, 0, 1);
    T(0, 1); V(+, +, +);
    T(0, 0); V(-, +, +);
    T(1, 0); V(-, -, +);
    T(1, 1); V(+, -, +);
    
    /* Crta se zadnja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(-1, 0, 0);
    T(0, 1); V(-, -, +);
    T(0, 0); V(-, +, +);
    T(1, 0); V(-, +, -);
    T(1, 1); V(-, -, -);
    
    /* Crta se leva strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, -1, 0);
    T(0, 1); V(-, -, +);
    T(0, 0); V(-, -, -);
    T(1, 0); V(+, -, -);
    T(1, 1); V(+, -, +);
    
    /* Crta se donja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, 0, -1);
    T(0, 1); V(-, -, -);
    T(0, 0); V(-, +, -);
    T(1, 0); V(+, +, -);
    T(1, 1); V(+, -, -);
    
    /* Kraj iscrtavanja plocica */
    glEnd();
    
    /* Prestanak vazenja makroa */
    #undef N
    #undef T
    #undef V
}

void postavi_scenu(void)
{
    /* Uz odbacivanje postojanja zicanog rezima,
     * odbaceno je i pozivanje liste za iscrtavanje
     * staze prema aktivnosti tog rezima; crtala se
     * popunjena staza inace, a zicana u rezimu */
    /*if (zicani){
        glCallList(staza2);
    } else {
        glCallList(staza1);
    }*/
    
    /* Pozivanje liste za iscrtavanje scene */
    glCallList(scena.lista);
}
