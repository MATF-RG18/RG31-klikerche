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
    
    /* Igra koja nije u toku znaci da se nista
     * posebno ne desava na tajmer, te se samo
     * forsira ponovno iscrtavanje scene, a sam
     * tajmer ne gasi, vec samo resetuje; usput
     * se azurira vreme mirovanja */
    if (stanje != U_TOKU){
        vreme.pauza += vreme.pom;
        glutPostRedisplay();
        glutTimerFunc(VREME, na_tajmer, TAJMER);
        return;
    }
    
    /* Kliker skace */
    if (klik.s != UGAO_POC){
        kliker_skok();
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

void postavi_vreme(void)
{
    /* Ispis poruka o cuvanju i
     * citanju igre je neaktivan */
    por.poruka = NEAKTIVNO;
    
    /* Svako vreme je na nuli */
    vreme.staro = NEAKTIVNO;
    vreme.pauza = NEAKTIVNO;
    fps.vreme = NEAKTIVNO;
    stopw.pocetak = NEAKTIVNO;
    stopw.starov = NEAKTIVNO;
    
    /* Vremenske niske takodje su nulte */
    sprintf(fps.niska, " 0 FPS");
    sprintf(stopw.niska, "00m:00s");
}

void popravi_vreme(void)
{
    /* Novo proteklo vreme dobavlja
     * ugradjena GLUT-ova funkcija */
    vreme.novo = glutGet(GLUT_ELAPSED_TIME);
    
    /* Ako je isteklo vreme za prikazivanje
     * poruke cuvanja odnosno citanja igre,
     * prekida se sa njenim ispisivanjem */
    if (por.poruka != NEAKTIVNO &&
        vreme.novo - por.vreme > TRAJANJE){
        por.poruka = NEAKTIVNO;
    }
    
    /* Mozda bi logicno bilo da se ovde nalazi
     * i azuriranje poruke o statistikama, ali je
     * ono ipak ostavljeno za fuknciju ispisa kako
     * bi popravka vremena bila manje opterecena */
    
    /* Vremenski pomeraj, neophodan kako
     * bi se njime pomnozio svaki fizicki
     * pokret; time kretanje biva uniformno
     * i nezavisno od brzine racunara, kao i
     * trajanja tajmera i broja prikazanih
     * slika (frejmova) u sekundi (FPS) */
    vreme.pom = vreme.novo - vreme.staro;
    
    /* Maksimalnim pomerajem izbegava se
     * prevelika razlika u vremenima; od
     * ovoga se ipak odustalo, jer moze
     * da napravi zbrku stoperici */
    /*if (vreme.pom > POM_MAX){
        vreme.pom = POM_MAX;
    }*/
    /*vreme.pom = MINIM(vreme.pom, POM_MAX);*/
    
    /* Novo vreme zastareva */
    vreme.staro = vreme.novo;
}
