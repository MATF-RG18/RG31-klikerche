#include "../include/cuvanje.h"

/* Odbaceni nacin promene rezima prikaza
 * pomocu indikatora u korist ugradjene
 * FreeGLUT-ove fje i indikatora */
/*void fullscreen(void)
{
    if (fulskrin == AKTIVAN){
        glutReshapeWindow(PROZ_DIM, PROZ_DIM);
    } else {
        glutFullScreen();
    }
    
    fulskrin = !fulskrin;
}*/

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
    
    /* Upisivanje stanja indikatora */
    fprintf(fajl, "%d %d %d\n",
            glutGet(GLUT_FULL_SCREEN), zicani, ntipke);
    
    /* Upisivanje dokumentacionih komentara
     * u fajl pre njegovog zatvaranja */
    fputc('\n', fajl);
    fprintf(fajl, "# Sacuvana igra zadrzi pet redova;\n");
    fprintf(fajl, "# detalji se mogu naci u samom kodu;\n");
    fprintf(fajl, "# prvi: sferni parametri oka/kamere;\n");
    fprintf(fajl, "# drugi: razlike oka, za resetovanje;\n");
    fprintf(fajl, "# treci: polozaj igracevog klikera;\n");
    fprintf(fajl, "# cetvrti: parametri skoka i rotacije;\n");
    fprintf(fajl, "# peti: stanja indikatora za rezim\n");
    fprintf(fajl, "# prikaza, zicani rezim i tipke\n");
    
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
    
    /* Sacuvane tipke pamte da li
     * su u toku skok ili pauza */
    int nprikaz, ntipke;
    
    /* Citanje stanja indikatora */
    fscanf(fajl, "%d %d %d", &nprikaz, &zicani, &ntipke);
    
    /* Zatvaranje fajla */
    fclose(fajl);
    
    /* Promena rezima prikaza u slucaju
     * da se stari i ucitani razlikuju */
    if (nprikaz != glutGet(GLUT_FULL_SCREEN)){
        glutFullScreenToggle();
    }
    
    /* Tekucim tipkama dodaju se stari
     * sacuvani parametri, pri cemu se
     * zanemaruju oni od pre citanja koji
     * nemaju veze sa kretanjem, mada se
     * pauza ipak nezavisno pamti */
    int bila_pauza = tipke & PAUZA;
    tipke = (tipke & ~RESET & ~SKOK & ~PAUZA) | ntipke;
    
    /* Ukoliko je bilo pauze pre citanja,
     * a posle ne, postavlja se tajmer,
     * a usput se i resetuje vreme */
    if (bila_pauza && !(tipke & PAUZA)){
        vreme.staro = glutGet(GLUT_ELAPSED_TIME);
        glutTimerFunc(TAJMER, na_tajmer, TAJMER);
    }
    
    /* Ukoliko je ucitana igra pauzirana,
     * osvezava se prozor, posto u suprotnom
     * biva prikazana stara zaledjena slika */
    if (tipke & PAUZA){
        glutPostRedisplay();
    }
}
