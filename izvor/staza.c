#include "../include/staza.h"

void ucitaj_stazu(void)
{
    /* Otvaranje fajla koji skladisti
     * stazu u rezimu za citanje */
    FILE* fajl = fopen(STAZA_DAT, "r");
    
    /* Neuspesno citanje znaci da
     * se igra ne moze zapoceti */
    if (fajl == NULL){
        napusti_igru("Neuspesno citanje fajla sa stazom!");
    }
    
    /* Ucitavanje koordinata cilja */
    int cit = fscanf(fajl, "%d %d",
                     &staza.cilj.x, &staza.cilj.y);
    
    /* Neuspesno citanje znaci da
     * se igra ne moze zapoceti */
    if (cit == EOF){
        napusti_igru("Neuspesno citanje fajla sa stazom!");
    }
    
    /* Ucitavanje staze iz datoteke; ovime se otvara
     * put lakoj implementaciji vise od jednog nivoa,
     * ali ovde to ipak nije uradjeno, sto zbog toga
     * sto OpenGL i nije za nesto vise od prototipa
     * igre, sto zbog vremenskog ogranicenja; bolje
     * bi bilo i da je uz tip polja cuvana i visina */
    int i, j;
    for (i = 0; i < STAZA_DIM; i++){
        for (j = 0; j < STAZA_DIM; j++){
            cit = fscanf(fajl, "%d", &staza.mat[i][j]);
            
            /* Neuspesno citanje znaci da
             * se igra ne moze zapoceti */
            if (cit == EOF){
                napusti_igru("Neuspesno citanje fajla sa stazom!");
            }
        }
    }
    
    /* Stdio nazalost nije previse precizan kada
     * je u pitanju provera tipova ulaznih podataka,
     * tako da je za test odabran pocetak komentara,
     * posto dolazenje dotle ukazuje na uspeh */
    char test[TEST_MAX];
    cit = fscanf(fajl, "%s", test);
    
    /* Neuspesno citanje znaci da
     * se igra ne moze zapoceti */
    if (cit == EOF || strcmp(test, "#")){
        napusti_igru("Neuspesno citanje fajla sa stazom!");
    }
    
    /* Zatvaranje fajla */
    fclose(fajl);
    
    /* Provalija ne moze biti cilj */
    if (staza.mat[staza.cilj.x][staza.cilj.y] == PROVALIJA){
        napusti_igru("Provalija ne moze biti cilj!");
    }
    
    /* Pravljenje tekstura za stazu; one se
     * prave pomocu biblioteke SOIL ucitavanjem u
     * podrazumevanom rezimu, a prave im se novi
     * identifikatori, kao i propratne mipmape, dok
     * se tekstura pozadine obrce po y osi; ovime
     * SOIL postedjuje rukovanja sa redudantnim
     * fjama poput glGenTextures() i slicnim; same
     * teksture su stock slike sa interneta */
    staza.tekst = SOIL_load_OGL_texture(STAZA_TEKST,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    staza.kraj = SOIL_load_OGL_texture(STAZA_KRAJ,
    SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    
    /* Teksture moraju biti ucitane */
    if (staza.tekst == NEAKTIVNO
        || staza.kraj == NEAKTIVNO){
        napusti_igru("Neuspesno citanje tekstura staze!");
    }
}

/* Odbaceno pravljenje fiksne test-staze
 * u obliku cirilickog 'G' u korist one
 * prilagodljive, ucitane iz datoteke */
/*void napravi_stazu(void)
{*/
    /* Vezivanje teksture za iscrtavanje staze */
    /*glBindTexture(GL_TEXTURE_2D, staza.tekst);*/
    
    /* Iscrtavanje staze; magicni brojevi
     * koji se po potrebi mogu menjati; push
     * i pop su neophodni zbog kretanja tj.
     * inace transformacija klikera, dok se
     * radi dobrog osvetljenja ne moze bez
     * normalizacije upravnih vektora */
    /*glEnable(GL_NORMALIZE);
    glPushMatrix();*/
    
    /* Spustanje staze ispod klikera
     * i pravljenje prve plocice */
    /*glTranslatef(0, 0, -1.13);
    napravi_plocicu();*/
    
    /* Pravljenje jos sest plocica
     * duz x ose; produzavanje puta */
    /*int i;
    for (i = 0; i < 6; i++){
        glTranslatef(-6, 0, 0);
        napravi_plocicu();
    }*/
    
    /* Pravljenje jos tri plocice
     * duz y ose; malo skretanje */
    /*for (i = 0; i < 3; i++){
        glTranslatef(0, 6, 0);
        napravi_plocicu();
    }*/
    
    /* Ukljucivanje teksture za kraj
     * i iscrtavanje zavrsne plocice */
    /*glBindTexture(GL_TEXTURE_2D, staza.kraj);
    glTranslatef(0, 6, 0);
    napravi_plocicu();*/
    
    /* Kraj iscrtavanja, a samim tim
     * i potrebe za normalizacijom */
    /*glPopMatrix();
    glDisable(GL_NORMALIZE);
}*/

void napravi_stazu(void)
{
    /* Vezivanje teksture za iscrtavanje staze */
    glBindTexture(GL_TEXTURE_2D, staza.tekst);
    
    /* Iscrtavanje staze; push i pop su tu
     * zbog kretanja klikera, a normalizacija
     * vektora radi dobrog osvetljenja */
    glEnable(GL_NORMALIZE);
    glPushMatrix();
    
    /* Postavljanje staze na pocetnu poziciju;
     * kako matrica staze oznacava plocice, prva
     * (najgornja i najlevlja) nalazi se u tacki
     * (-60, -60), posto je udaljena za tacno deset
     * (pola dimenzije matrice) plocica cije su
     * stranice duzine sest, tako da se tu translira
     * po x i y osi; po z osi se spusta ispod klikera
     * prema odgovarajucim dimenzijama objekata */
    glTranslatef(-STAZA_DIM/2 * PLOC_DIM,
                 -STAZA_DIM/2 * PLOC_DIM,
                 -KLIK_RAD - PLOC_VIS);
    
    /* Iscrtavanje staze prema ucitanoj matrici;
     * transformacije koje odredjuju polozaj
     * trenutne plocice izvode se inkrementalno */
    int i, j;
    for (i = 0; i < STAZA_DIM; i++){
        for (j = 0; j < STAZA_DIM; j++){
            /* Vezivanje teksture za iscrtavanje cilja */
            if (i == staza.cilj.x && j == staza.cilj.y){
                glBindTexture(GL_TEXTURE_2D, staza.kraj);
            }
            
            switch (staza.mat[i][j]){
                case PROVALIJA:
                    break;
                
                case PLOCICA:
                    napravi_plocicu(PLOC_VIS);
                    break;
                
                case PREPREKA1:
                    napravi_plocicu(PREP1_VIS);
                    break;
                
                case PREPREKA2:
                    napravi_plocicu(PREP2_VIS);
                    break;
            }
            
            /* Vezivanje teksture za iscrtavanje staze */
            if (i == staza.cilj.x && j == staza.cilj.y){
                glBindTexture(GL_TEXTURE_2D, staza.tekst);
            }
            
            /* Pomeranje u narednu kolonu */
            glTranslatef(0, PLOC_DIM, 0);
        }
        
        /* Pomeranje u naredni red */
        glTranslatef(PLOC_DIM, -STAZA_DIM * PLOC_DIM, 0);
    }
    
    /* Kraj iscrtavanja, a samim tim
     * i potrebe za normalizacijom */
    glPopMatrix();
    glDisable(GL_NORMALIZE);
}

void napravi_plocicu(double visina)
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
    #define Vm(a,b,c) \
     glVertex3f(a PLOC_DIM/2, b PLOC_DIM/2, c PLOC_VIS)
    #define Vp(a,b,c) \
     glVertex3f(a PLOC_DIM/2, b PLOC_DIM/2, c visina)
    
    /* Plocice se icrtavaju kao skup cetvorouglova */
    glBegin(GL_QUADS);
    
    /* Crta se prednja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(1, 0, 0);
    T(0, 1); Vp(+, -, +);
    T(0, 0); Vm(+, -, -);
    T(1, 0); Vm(+, +, -);
    T(1, 1); Vp(+, +, +);
    
    /* Crta se desna strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, 1, 0);
    T(0, 1); Vp(+, +, +);
    T(0, 0); Vm(+, +, -);
    T(1, 0); Vm(-, +, -);
    T(1, 1); Vp(-, +, +);
    
    /* Crta se gornja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, 0, 1);
    T(0, 1); Vp(+, +, +);
    T(0, 0); Vp(-, +, +);
    T(1, 0); Vp(-, -, +);
    T(1, 1); Vp(+, -, +);
    
    /* Crta se zadnja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(-1, 0, 0);
    T(0, 1); Vp(-, -, +);
    T(0, 0); Vp(-, +, +);
    T(1, 0); Vm(-, +, -);
    T(1, 1); Vm(-, -, -);
    
    /* Crta se leva strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, -1, 0);
    T(0, 1); Vp(-, -, +);
    T(0, 0); Vm(-, -, -);
    T(1, 0); Vm(+, -, -);
    T(1, 1); Vp(+, -, +);
    
    /* Crta se donja strana plocice u odnosu
     * na pocetni polozaj oka i klikera */
    N(0, 0, -1);
    T(0, 1); Vm(-, -, -);
    T(0, 0); Vm(-, +, -);
    T(1, 0); Vm(+, +, -);
    T(1, 1); Vm(+, -, -);
    
    /* Kraj iscrtavanja plocica */
    glEnd();
    
    /* Prestanak vazenja makroa */
    #undef N
    #undef T
    #undef Vm
    #undef Vp
}
