#include "../include/vreme.h"

void na_tajmer(int id)
{
    /* Provera da li poziv dolazi od
     * odgovarajuceg tajmera; nije bas
     * neophodno, pogotovu posto ovde
     * ima samo jedan tajmer koji sam
     * sebe poziva, ali je dobra praksa */
    if (id != TAJMER){
          return;
    }
    
    /* Svakim pozivom fje na tajmer
     * azurira se vremenski pomeraj;
     * iako se ocekuje da bude jednak
     * trajanju tajmera (VREME), ipak
     * valja preduprediti talasanje */
    popravi_vreme();
    
    /* Pauzirana igra znaci da se
     * nista ne desava na tajmer */
    if (tipke & PAUZA){
        return;
    }
    
    /* Kliker skace */
    if (tipke & SKOK){
        /* Kraj animacije skoka */
        if (kliker_skok() == SKOK_KRAJ){
            tipke &= ~SKOK;
        }
    }
    
    /* Resetovanje pogleda */
    if (tipke & RESET){
        /* Kraj animacije resetovanja */
        if (oko_reset() == RES_KRAJ){
            tipke &= ~RESET;
        }
    }
    
    /* Kliker se krece napred */
    if (tipke & KRENI){
        kliker_napred();
    }
    
    /* Kliker se krece nazad */
    if (tipke & VRATI){
        kliker_nazad();
    }
    
    /* Oko se priblizava */
    if (tipke & NAPRED){
        oko_napred();
    }
    
    /* Oko se udaljava */
    if (tipke & NAZAD){
        oko_nazad();
    }
    
    /* Oko se penje */
    if (tipke & NAGORE){
        oko_gore();
    }
    
    /* Oko se spusta */
    if (tipke & NADOLE){
        oko_dole();
    }
    
    /* Kliker se okrece nalevo,
     * dakle oko ide desno, osim
     * u slucaju istovremenog
     * kretanja klikera unazad,
     * radi intuitivnijeg pravca */
    if (tipke & LEVO){
        if (tipke & VRATI){
            oko_levo();
        } else {
            oko_desno();
        }
    }
    
    /* Kliker se okrece nadesno,
     * dakle oko ide levo, osim
     * u slucaju istovremenog
     * kretanja klikera unazad,
     * radi intuitivnijeg pravca */
    if (tipke & DESNO){
        if (tipke & VRATI){
            oko_desno();
        } else {
            oko_levo();
        }
    }
    
    /* Osvezavanje prozora; forsira se
     * ponovno iscrtavanje scene */
    glutPostRedisplay();
    
    /* Ponovno postavljanje tajmera */
    glutTimerFunc(VREME, na_tajmer, TAJMER);
}

void popravi_vreme(void)
{
    /* Novo proteklo vreme dobavlja
     * ugradjena GLUT-ova funkcija */
    vreme.novo = glutGet(GLUT_ELAPSED_TIME);
    
    /* Vremenski pomeraj, neophodan kako
     * bi se njime pomnozio svaki fizicki
     * pokret; time kretanje biva uniformno
     * i nezavisno od brzine racunara */
    vreme.pom = vreme.novo - vreme.staro;
    
    /* Maksimalnim pomerajem izbegava
     * se prevelika razlika u vremenima */
    if (vreme.pom > POM_MAX){
        vreme.pom = POM_MAX;
    }
    
    /* Novo vreme zastareva */
    vreme.staro = vreme.novo;
}
