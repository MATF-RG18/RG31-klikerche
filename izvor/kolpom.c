#include "../include/kolpom.h"

void fullscreen(void)
{
    /* Ako je trenutni prikaz tipa
     * fullscreen, menja se u pocetni
     * windowed prikaz i obrnuto */
    if (fulskrin == AKTIVAN){
        glutReshapeWindow(PROZ_DIM, PROZ_DIM);
    } else {
        glutFullScreen();
    }
    
    /* Prostom negacijom azurira se
     * indikator fullscreen prikaza;
     * AKT. postaje PAS. i obrnuto */
    fulskrin = !fulskrin;
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

void sacuvaj_igru(void)
{
    /* Otvaranje fajla sa sacuvanom
     * igrom u rezimu za pisanje */
    FILE* fajl = fopen(SAVEGAME, "w");
    
    /* Ukoliko fajl nije mogao da bude
     * otvoren, zasad se prosto odustaje */
    if (fajl == NULL){
        return;
    }
    
    /* Ne postoji serijalizacija u C-u,
     * ali se cuvanje igre moze simulirati
     * zapisivanjem bitnih promenljivih */
    
    /* Upisivanje parametara oka */
    fprintf(fajl, "%lf %lf %lf\n", oko.r, oko.phi, oko.theta);
    
    /* Upisivanje razlika oka */
    fprintf(fajl, "%d %d %d\n", raz.r, raz.phi, raz.theta);
    
    /* Upisivanje polozaja klikera */
    fprintf(fajl, "%lf %lf %lf\n", klik.x, klik.y, klik.z);
    
    /* Upisivanje skoka i rotacije */
    fprintf(fajl, "%lf %lf\n", klik.s, rot.u);
    
    /* Od tipki je bitno samo da li
     * su u toku skok ili pauza */
    int ntipke = tipke & (SKOK | PAUZA);
    
    /* Upisivanje stanja indikatora;
     * fullscreen namerno obrnut */
    fprintf(fajl, "%d %d %d\n", !fulskrin, debag, ntipke);
    
    /* Upisivanje dokumentacionih komentara
     * u fajl pre njegovog zatvaranja */
    fputc('\n', fajl);
    fprintf(fajl, "# Sacuvana igra zadrzi pet redova;\n");
    fprintf(fajl, "# detalji se mogu naci u funkciji;\n");
    fprintf(fajl, "# prvi: sferni parametri oka/kamere;\n");
    fprintf(fajl, "# drugi: razlike oka, za resetovanje;\n");
    fprintf(fajl, "# treci: polozaj igracevog klikera;\n");
    fprintf(fajl, "# cetvrti: parametri skoka i rotacije;\n");
    fprintf(fajl, "# peti: stanja indikatora za rezim\n");
    fprintf(fajl, "# prikaza, debag rezim i tipke\n");
    
    /* Zatvaranje fajla */
    fclose(fajl);
}

void ucitaj_igru(void)
{
    /* Otvaranje fajla sa sacuvanom
     * igrom u rezimu za citanje */
    FILE* fajl = fopen(SAVEGAME, "r");
    
    /* Ukoliko fajl nije mogao da bude
     * otvoren ili ne sadrzi sve neophodne
     * podatke, zasad se prosto odustaje */
    if (fajl == NULL || fscanf(fajl, "%*f %*f %*f \
                            %*d %*d %*d \
                            %*f %*f %*f \
                            %*f %*f \
                            %*d %*d %*d") == EOF){
        return;
    }
    
    /* Resetovanje offseta, koji je zbog
     * provere pomeren na kraj fajla */
    rewind(fajl);
    
    /* Citanje parametara oka */
    fscanf(fajl, "%lf %lf %lf", &oko.r, &oko.phi, &oko.theta);
    
    /* Citanje razlika oka */
    fscanf(fajl, "%d %d %d", &raz.r, &raz.phi, &raz.theta);
    
    /* Citanje polozaja klikera */
    fscanf(fajl, "%lf %lf %lf", &klik.x, &klik.y, &klik.z);
    
    /* Citanje skoka i rotacije */
    fscanf(fajl, "%lf %lf", &klik.s, &rot.u);
    
    /* Citanje stanja indikatora */
    fscanf(fajl, "%d %d %d", &fulskrin, &debag, &tipke);
    
    /* Zatvaranje fajla */
    fclose(fajl);
    
    /* Postavljanje rezima prikaza na stanje
     * pre cuvanja igre, sto se postize novim
     * obrtanjem ucitanog vec obrnutog stanja
     * (dupla negacija daje pocetno stanje) */
    fullscreen();
    
    /* Osvezavanje prozora */
    glutPostRedisplay();
}
