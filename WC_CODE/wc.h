#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NombreDeLigne(FILE *file);
int NombreDeCaractere(FILE *file);
int bytes(FILE* file);
int word(FILE *file);
int MaximalLine(FILE *file);
void option(int argc,char *argv[]);
void version();
void help();