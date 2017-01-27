/* RATO Antoine, DUBOIS Fabien, Licence 3 Informatique Apprentissage */
#include "fonctionsSudoku.h"

int main (int argc, char **argv)
{ 
  if( final_sudoku(argc, argv) == 0) /* Si la fonction final de résoltion du sudoku retourne 0 alors tout doit s'étre correctement effectué */
  { 
    printf("\n Tous les sudoku ont été traité \n");
    return 0;
  } 
  else
  {
    printf("\n problème lors de la résolution d'un sudoku \n");
    return 1;
  }
}
