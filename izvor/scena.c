#include "../include/scena.h"

void napravi_scenu(void)
{
    /* Citanje staze iz datoteke */
    ucitaj_stazu();
    
    /* Pravljenje tekstura za scenu; one se
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
    
    /* Teksture moraju biti ucitane */
    if (scena.pozt == NEAKTIVNO
        || scena.zaklop == NEAKTIVNO){
        napusti_igru("Neuspesno citanje tekstura scene!");
    }
    
    /* Iscrtavanje pozadine resava se preko
     * GLU-ovog quadric valjka, posto on
     * ima ugradjenu podrsku za teksture;
     * pravi se novi quadric i sugerise mu
     * se da prihvati aktivnu teksturu;
     * quadric mora biti uspesno napravljen */
    scena.obj = gluNewQuadric();
    if (scena.obj == NULL){
        napusti_igru("Neuspesno pravljenje quadrica pozadine!");
    }
    gluQuadricTexture(scena.obj, GLU_TRUE);
    
    /* Registrovanje liste za scenu */
    scena.lista = glGenLists(AKTIVNO);
    
    /* Registracija mora biti uspesna */
    if (scena.lista == NEAKTIVNO){
        napusti_igru("Neuspesno pravljenje liste scene!");
    }
    
    /* Pravljenje liste za scenu */
    glNewList(scena.lista, GL_COMPILE);
    
    /* Ukljucivanje 2D tekstura i vezivanje
     * one namenjene za iscrtavanje pozadine */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scena.pozt);
    
    /* Pravljenje pozadine */
    napravi_pozadinu();
    
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
