#include "../include/staza.h"

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
     * do kocenja prilikom prvog ulaska u zicani
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
     * zicana u slucaju zicanog rezima */
    if (zicani){
        glCallList(staza2);
    } else {
        glCallList(staza1);
    }
}
