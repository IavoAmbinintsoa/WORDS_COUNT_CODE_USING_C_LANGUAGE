#include "wc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>

//line count
int NombreDeLigne(FILE *file)
{
    int nombre = 0;
    char ligne[3000];
    rewind(file);
    while(fgets(ligne,1500,file) != 0)
    {
        nombre++;
    }
    return (nombre);
}

//char count
int NombreDeCaractere(FILE *file)
{
    int nombre = 0;
    int c;
    rewind(file);
    while(!feof(file))
    {
        c = fgetc(file);
        if((c & 0xC0) != 0x80 && c != EOF)
            nombre++;
    }
    return (nombre);
}
void option(int argc,char *argv[])
{   
    FILE *file;
    int nombre;
    int i;
    if(argc == 1 )
    {
        printf("  Veillez indiquer le chemin vers le fichier\n");
        exit(EXIT_FAILURE);
    }
    if((strcmp(argv[1],"--version") == 0))
    {
        version();
    }
    if(strcmp(argv[1],"--help") == 0)
    {
        help();
        exit(EXIT_SUCCESS);
    }
    file = fopen(argv[argc-1],"r"); //recuperer l'argument
    if(file == NULL)
    {
        printf("  Erreur lors de l'ouverture\n");
        exit(EXIT_FAILURE);
    }
    for(i = 1;i<argc;i++)
    {
        if(strcmp(argv[i],"-m") == 0 || (strcmp(argv[i],"--chars") == 0))
        {
            nombre = NombreDeCaractere(file);
            printf("  %d %s\n",nombre,argv[argc-1]);
        }
        if((strcmp(argv[i],"--bytes") == 0) || (strcmp(argv[i],"-c") == 0))
        {
           nombre = bytes(file);
           printf("  %d %s\n",nombre,argv[argc-1]);
        }
        if(strcmp(argv[i],"-l") == 0 || (strcmp(argv[i],"--lines") == 0))
        {
            nombre = NombreDeLigne(file);
            printf("  %d %s\n",nombre,argv[argc-1]);
        }
        if(strcmp(argv[i],"-L") == 0 || (strcmp(argv[i],"--max-line-length") == 0))
        {
            nombre = MaximalLine(file);
            printf("  %d %s\n",nombre,argv[argc-1]);
        }
        if(strcmp(argv[i],"-w") == 0 || (strcmp(argv[i],"--words") == 0))
        {
            nombre = word(file);
            printf("  %d %s\n",nombre,argv[argc-1]);
        }
    }
    if(argc == 2)
    {
        //Si seule le nom de fichier est donne alor afficher
        //[Nombre de ligne] [nombre de mot ] [nombre de caractere]
        nombre = NombreDeLigne(file);
        printf("  %d",nombre);
        nombre = word(file);
        printf("  %d",nombre);
        nombre = NombreDeCaractere(file);
        printf("  %d %s\n",nombre,argv[argc-1]);
    }
    fclose(file);
}

int word(FILE *file)
{
    int nombre = 0;
    char mot[5000];
    char ligne[5000];
    rewind(file);
    //le fscanf ne prend pas en charge l'espace -> il stocke le mot trouve mais pas la ligne
    while(fscanf(file,"%s",mot) != EOF)
    {
        nombre++;       //On compte le nombre trouve pas fscanf
    }
    return (nombre);
}

int MaximalLine(FILE *file)
{
    int max;
    int i;
    int c;
    int nombre = 0;
    max = nombre;
    while(!feof(file))
    {
        c = fgetc(file);
        //le variable nombre est le nombre de caractere dans une phrase
        if((c & 0xC0) != 0x80 && c != EOF)
            nombre++;
        if(c == '\n')
        {
            //On reinitialise a 0 a la fin de chaque phrase
            nombre = 0;
        }
        if(nombre > max)
        {
            max = nombre;
        }
    }
    return (max);
}

int bytes(FILE *file)
{
    int nombre = 0;
    int c;
    while(1)
    {
        c = fgetc(file);
        if(c == EOF)
        {
            break;
        }
        nombre++;
    }
    return (nombre);
}
void help()
{
    printf("  Utilisation : wc [OPTION]... [FICHIER]...\n");
    printf("  ou : wc [OPTION]... --files0-from=F\n");
    printf("  Afficher le nombre de ligne, de mots et de caracteres pour chaque FICHIER\n");
    printf("  et une ligne totale si plus d'un fichier est specifie. Un mot est une sequence\n");
    printf("  de taille non nulle de caracteres delimites par une espace.\n");
    printf("  Sans FICHIER ou quand FICHIER est -, Demander une ajout de fichier.\n");
    printf("  Les options ci-dessous permettent de selectionner les compteurs a afficher,\n");
    printf("  qui sont toujours utilises dans l'ordre suivant : saut de ligne, mot, caractere,\n");
    printf("  octet, longueur de ligne maximale.\n");
    printf("        -c, --bytes            afficher le nombre d'octets\n");
    printf("        -m, --chars            afficher le nombre de caracteres\n");
    printf("        -l, --lines            afficher le nombre de sauts de lignes\n");
    printf("         -L, --max-line-length  afficher la largeur maximale d'affichage\n");
    printf("        -w, --words            afficher le nombre de mots\n");
    printf("        --help     afficher l'aide et quitter\n");
    printf("        --version  afficher des informations de version et quitter\n");
    printf("  Aide en ligne de GNU coreutils : <https://www.gnu.org/software/coreutils/>\n");
    printf("  Signalez les problemes de traduction de « wc » a : <traduc@traduc.org>\n");
    printf("  Documentation complete a : <https://www.gnu.org/software/coreutils/wc>\n");
    printf("  ou disponible localement via: info '(coreutils) wc invocation'\n");
    exit(EXIT_SUCCESS);
}
void version()
{
    printf("  ==> CE CODE EST UNE CODE EN C QUI EST TIREE DE LA VERSION DE WC : \n\n");
    printf("  wc (GNU coreutils) 8.32\n");
    printf("  Copyright (C) 2020 Free Software Foundation, Inc.\n");
    printf("  License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n");
    printf("  This is free software: you are free to change and redistribute it.\n");
    printf("  There is NO WARRANTY, to the extent permitted by law.\n");
    printf("  Written by Paul Rubin and David MacKenzie.\n\n");
    printf("  ==> Ce code est fait par RAMANDIAMANANA Iavonirina Ambinintsoa \n");
    exit(EXIT_SUCCESS);
}