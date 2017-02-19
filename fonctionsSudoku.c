/* RATO Antoine, DUBOIS Fabien, Licence 3 Informatique Apprentissage */
#include "fonctionsSudoku.h"

/* Creation d'un tableau de tableaux d'entiers, allocation de mémoire avec malloc, utilisation des pointeurs */
int **createSudoku(int nbLignes, int nbColones)
{
  int **tableau = malloc(sizeof(int *) * nbLignes);
  int *tableau2 = malloc(sizeof(int) * nbColones * nbLignes);
  int i;
  for(i = 0 ; i < nbLignes ; i++)
  {
    tableau[i] = &tableau2[i*nbColones];
  }
  return tableau;
}

/* A partir de la ligne representant le suduko dans le fichier on va remplir le double tableau */
int **remplirSudoku(int **tab,int iMax, int jMax, char *line)
{
  int i,j,h;
  h = 0;
  for(i = 0 ; i  < iMax ; i++)
  {
    for(j = 0 ; j < jMax ; j++)
    {
      tab[i][j] = line[h++] - 48; /* Ici on soustrait -48, sinon nous obtenons une confusion avec les nomres ASCII et nous n'avons pas les chiffres corrects. */
    }
  }
  return (tab);
}

/* On ecris dans le fichier solution{DUBOIS}{RATO}.txt le sudoku passé en argument */
void ecrireSudoku(int **tab,int iMax, int jMax)
{
  FILE* fichier2 = NULL;

  /* Ouverture du fichier result.txt, utilisation du mode a+ pour l'ajout à la fin du fichier des lignes de résultats. Si le fichier n'existe pas alors il sera créé. */
  fichier2 = fopen("solution.txt", "a+");
  int i,j,h;
  h = 0;
  for(i = 0 ; i  < iMax ; i++)
  {
    for(j = 0 ; j < jMax ; j++)
    {
      fprintf(fichier2, "%d",tab[i][j]); /* ecriture dans le fichier */
    }
  }
  fprintf(fichier2, "\n");
  fclose(fichier2); /*fermueture du fichier */
}


/* Parcours du Sudoku passé en argument, et affichage de celui ci */
void afficherSudoku(int **tab, int iMax, int jMax)
{
  int i,j;
  printf("\n _____________________________________");
  for(i = 0 ; i < iMax ; i++) /* parcours typique d'un double tableau, avec 2 for imbriqué l'un dans l'autre */
  {
    if(i % 3 == 0 && i != 0)
    {
      if(i == 0)
        printf("|\n");
      printf("\n _____________________________________");
    }
    
    printf("\n\n");
    
    for(j = 0 ; j < jMax ; j++)
    {
      if(j % 3 == 0)
        printf(" | ");

      printf(" %d ", tab[i][j]);

      if (j == 8)
        printf(" |");
    }
  }
  printf("\n _____________________________________");
}

/* Passage en argument de la ligne d'une valeur et du Sudoku, on return 1 si elle est présente sur la ligne */
int est_sur_ligne(int valeur, int **tab, int ligne)
{
  int i;
  for (i = 0 ; i < 9 ; i++)
  {
    if (tab[i][ligne] == valeur) /* Effectivement si en parcourant la ligne on trouve la valeur alors on retourne 1 */
      return 1;
  }
  return 0;
}

/* Passage en argument de la colone d'une valeur et du Sudoku, on return 1 si elle est présente sur la colone */
int est_sur_colonnes(int valeur, int **tab, int colonne)
{
  int i;
  for (i = 0 ; i < 9 ; i++)
  {
    if (tab[colonne][i] == valeur) /* Effectivement si en parcourant la colonne on trouve la valeur alors on retourne 1 */
      return 1;
  }
  return 0;
}

/* Passage en argument des coodonées d'une valeur et du Sudoku, on return 1 si elle est présente sur le carre */
int est_sur_carre(int valeur, int **tab, int ligne, int colonne)
{
  int limiteLigne = ligne - (ligne % 3), limiteColonne = colonne - (colonne % 3);
  for (colonne = limiteColonne ; colonne < limiteColonne + 3 ; colonne++)
  {
      for (ligne = limiteLigne ; ligne < limiteLigne + 3 ; ligne++)
    {
      if (tab[colonne][ligne] == valeur)
        return 1;
    }
  }
  return 0;
}

/* Vérfie que les 3 fonctions du dessus retournent toutes 1, return 1 si oui si non 0 */
int is_ajouter_valeur(int **tab, int nb, int i, int j)
{
  /* Si toutes les fonctions retournent 0 alors la valeur n'a pas était trouvé donc on retourne 1 */
  if ((est_sur_carre(nb, tab, j, i) == 0) && (est_sur_ligne(nb, tab, j) == 0 ) && (est_sur_colonnes(nb, tab, i) == 0))
    return 1;
  else
    return 0; 
}


int resoudre_sudoku(int ** tab, int position, char * line, int option)
{
  int nb = 0; /* compteur */
  
  /* Si la position atteint 81, le sudoku est résolu (la taille étant 80) */
  if(position == 81)
  {
    if ( option == 3 ) /* Vérification de l'option */
    {
      printf("\n 100 / 100\n");
      return 1;
    }
    return 1;
  }
  
  /* Actualisation de la progression d'execution */
  if((option == 3) && (position > temps))
  {
    temps = position;
    int tmp = ((temps * 100)/81) + 1; ;
    printf("\n %d / 100 ", tmp);
  }

  /* cela permet d'obtenir la position sur la matrice, savoir si nous sommes sur la 1e case, 2e case ..... 81e case */
  int i = position / 9;
  int j = position % 9;

  if(line[position] != '0') /* On vérifie si c'est une case définie dans le fichier, si oui on ne peut pas la modifier sinon on peut la traiter */
    return resoudre_sudoku(tab, position + 1, line, option);

  /* Parcours de la grille en récurrence */
  for(nb = 1; nb <= 9; nb++)
  {
    /* Si la valeur est possible ... */
    if(is_ajouter_valeur(tab, nb, i, j))
    {
      tab[i][j] = nb; /* ... on l'ajoute ... */

      /* ... puis nous rappellons la fonction avec la position incrémenté de 1, de cette manière, si l'appelle réussit (si position = 81), la fonction récurrente
             va renvoyer 1 (vrai), et donc chaque occurence de la fonction va valider la condition suivante et va renvoyer 1 (vrai) et le sudoku sera donc résolu */
      if(resoudre_sudoku(tab, position + 1, line, option)) /*  */
      {
        return 1;
      }
    }
  }

  tab[i][j] = 0;
  return 0;
}

/* La fonction ouvre le fichier et va traiter ligne par ligne en fonction de l'option passée en argument (-print, -verbose, -timeAlert) */
int final_sudoku(int argc, char **argv)
{
  int sudokuValide;
  int** sudoku; //double tableau d'entiers
  FILE *file;
  char line [83], *filename, *option; /* line : tableau de char de taille 83, pour avoir la ligne de sudoku entierement */
  clock_t deb, fin; /*Permet de mesurer le temps, voir l'exemple dans le cour "BACA" de Complexité */
  double duree;
  temps = 0;
  filename = argv[1]; /* On doit passer en argument dans la commande le nom.txt du fichier où se trouve les grilles. Exemple : "./macommande fichier.txt" */
  file = fopen(filename, "r"); /* ouverture du fichier en lecture (R) */

  if(argc >= 3) /* Si il y a plus ou égal 3 chaines de caractères dans la commande d d'exection */
  {
    option = argv[2]; /* doit être passé en argument également une option */

    if (strcmp(option, "-print") == 0) /* Si le deuxième arguement correspond à "-print" alors nous executons la partie suivante */
    {
      if (file != NULL) /* Vérifie si le fichier existe bien */ 
      {
        system("clear"); /* On fait un clear de la console d'éxecution, pour que ce soit plus "propre" */
        while (fgets(line, sizeof line, file) != NULL) /* Lecture et traitement ligne par ligne du fichier */
        {
          printf("-------------------------------------------------------------------------------------------------------------------------- \n");
          printf("Sudoku avant \n");
          sudoku = createSudoku(9, 9); /* On créé un double tableau de taille 9 par 9 */
          sudoku = remplirSudoku(sudoku, 9, 9, line); /* On remplit le sudoku avec les chiffres correspondant se trouvant dans la ligne texte */
          afficherSudoku(sudoku, 9, 9); /* Affichage du sudoku */
          sudokuValide = resoudre_sudoku(sudoku, 0, line, 0);
          printf("\n \nSudoku après");
          afficherSudoku(sudoku, 9, 9);/* Affichage du sudoku final */
          ecrireSudoku(sudoku, 9, 9); /* Ecris le sudoku final dans le fichier de résultats */
          printf("\n\n");
        }
        fclose(file); /* fermeture du fichier de resultats */
        return 0; 
      }
      else
      {
        dprintf(2, "Saisir un nom de fichier correct"); //Ecris sur la sortie 2
        exit (1); // Coupe le programme en retournant le code 1
      } 
    }
    
    else  if (strcmp(option, "-timeAlert") == 0)
    {
      if (file != NULL)
      {
        int i = 1;
        system("clear");
        double tempsMaximum;
        printf("Entrez un temps en seconde : \n");
        scanf("%lf", &tempsMaximum);
        debutChrono = clock(); 

        while (fgets(line, sizeof line, file) != NULL) // lire ligne par ligne
        {
          fin = clock();
          duree = ((double)(fin - debutChrono)) / CLOCKS_PER_SEC;
          printf("%f\n", duree);
         
          if (duree >= tempsMaximum)
          {
            exit(1);
          }
          temps = 0;
          sudoku = createSudoku(9, 9);
          sudoku = remplirSudoku(sudoku, 9, 9, line);
          sudokuValide = resoudre_sudoku(sudoku, 0, line, 0);
          printf("\n Sudoku numéro : %d resolut\n",i++);
          ecrireSudoku(sudoku, 9, 9); 
          printf("\n");
        }
        fclose(file);
        return 0;

      }
      else
      {
        dprintf(2, "Saisir un nom de fichier correct"); //Ecris sur la sortie 2
        exit (1); // Coupe le programme en retournant le code 1
      } 
    }

    else if (strcmp(option, "-verbose") == 0)
    {
      if (file != NULL)
      {
        system("clear");
        int i = 1;
        while (fgets(line, sizeof line, file) != NULL)
        {
          temps = 0;
          sudoku = createSudoku(9, 9);
          sudoku = remplirSudoku(sudoku, 9, 9, line);
          deb = clock(); 
          sudokuValide = resoudre_sudoku(sudoku, 0, line, 3);
          fin = clock();
          duree = ((double)(fin - deb)) / CLOCKS_PER_SEC;
          printf("\n Sudoku numéro : %d resolut en  %f Secondes\n",i++,duree);      
          ecrireSudoku(sudoku, 9, 9); 
          printf("\n");
        }
        fclose(file);
        return 0;

      }
      else
      {
        dprintf(2, "Saisir un nom de fichier correct");
        exit (1);
      } 
    }
  }
    
  /* MODE SANS OPTION */
  printf("Résolution sans options");
  if (file != NULL) /* Vérifie si le fichier existe bien */ 
      {
        int i = 1;
        system("clear"); /* On fait un clear de la console d'éxecution, pour que ce soit plus "propre" */
        while (fgets(line, sizeof line, file) != NULL) /* Lecture et traitement ligne par ligne du fichier */
        {
          sudoku = createSudoku(9, 9); /* On créé un double tableau de taille 9 par 9 */
          sudoku = remplirSudoku(sudoku, 9, 9, line); /* On remplit le sudoku avec les chiffres correspondant se trouvant dans la ligne texte */
          sudokuValide = resoudre_sudoku(sudoku, 0, line, 0);
          printf("\n Sudoku numéro : %d resolut\n",i++);
          ecrireSudoku(sudoku, 9, 9); /* Ecris le sudoku final dans le fichier de résultats */
          printf("\n\n");
        }
        fclose(file); /* fermeture du fichier de resultats */
        return 0; 
      }
  
  return 0;
}
