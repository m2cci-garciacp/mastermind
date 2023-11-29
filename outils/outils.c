#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "outils.h"            /* Outils de conversion */



void strToSeqInt ( char str[] , int* Seq, int* L) 
/*
    Convertit un string d'entiers et espaces à une sequence d'entiers de longeur L.
    Les espaces sont les delimitateur des numèros.

    Input: 
        char str[] :
                string d'entree.
        int* Seq :
                Pointeur de sequence d'integer ou on va stocker la sequence. 
        int* L :
                Pointeur de longeur de sequence. 
    Output:
        void
*/
{
    
    int i=0, j=0;
    *L=0;
    char number[20] = "" ;
    while ( 1 ) {
        //printf("(i,j)=(%d,%d)  s[i] = %c  number:%s S[i]=%d L=%d\n", i,j,str[i], number, Seq[*L],*L );
        if (str[i] == 0 && j!= 0) {
            number[j] = 0;
            Seq[*L] = atoi(number) ;
            (*L)++;
            break ;
        } else if (str[i] != ' ' && str[i] != 0) {
            number[j] = str[i] ;
            j++;
        } else if (str[i] == ' ' && j!= 0){
            number[j] = 0;
            j=0;
            Seq[(*L)] = atoi(number) ;
            (*L)++;
        } else {
            break;
        }
        i++;
    }
}

void seqIntToStr ( int* Seq, int L, char *str ) 
/*
    Convertit à une sequence d'entiers de longeur L à un string d'entiers separés par espaces.

    Input: 
        int* Seq :
                Pointeur de sequence des entiers pour ecrire dans str. 
        int  L :
                Longeur de sequence. 
        char str[] :
                string de sortie.
    Output:
        void
*/
{
    str[0] = 0 ;
    for (int i=0; i<L; i++) {
        sprintf(str, "%s%d ", str, Seq[i]);
    }
}


void strlwr(char * str) {
    int i = 0 ;
    while(str[i] != 0 )
    {
        str[i] = tolower(str[i]) ;
        i++ ;
    }
}