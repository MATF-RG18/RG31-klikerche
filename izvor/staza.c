#include "../include/staza.h"

void napravi_stazu(void)
{
    /* Registrovanje liste za stazu */
    staza = glGenLists(STAZA);
    
    /* Pravljenje liste za stazu */
    glNewList(staza, GL_COMPILE);
    
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
    
    /* Prestanak upotrebe obicnih boja
     * umesto materijala za stazu */
    glDisable(GL_COLOR_MATERIAL);
    
    /* Kraj liste za stazu */
    glEndList();
}

void postavi_stazu(void)
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
    
    /* Pozivanje liste za iscrtavanje staze */
    glCallList(staza);
}
