Compilation avec gcc sous Linux 

#Pour compiler
gcc -W -Wextra -pedantic main.c fonctionsSudoku.c -o prog

#Pour executer sans options 
./prog fichier.txt

## Avec l'option -print
./prog fichier.txt -print

## Avec l'option -verbose
./prog fichier.txt -verbose

## Avec l'option -timeAlert
./prog fichier.txt -
Pour cette option il faut saisir un temps du type "X.X" ou "X".