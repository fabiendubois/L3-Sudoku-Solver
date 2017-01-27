/* RATO Antoine, DUBOIS Fabien, Licence 3 Informatique Apprentissage */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

static int temps; /* Définition d'une variable globale, utilise à la résolution du -verbose */
static clock_t debutChrono; /* Définition d'une variable globale, utilise à la résolution du -timeAlert */

int **createSudoku(int, int);
int **remplirSudoku(int **, int, int, char *);
void afficherSudoku(int **, int, int);
void ecrireSudoku(int **, int, int);
int est_sur_ligne(int, int **, int);
int est_sur_colonnes(int, int **, int);
int est_sur_carre(int, int **, int, int);
int is_ajouter_valeur(int **, int, int, int);
int resoudre_sudoku(int **, int, char *, int);
int final_sudoku(int, char **);
