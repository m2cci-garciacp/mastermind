#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "outils.h"

void strToSeqInt ( char str[] , int* Seq, int* L) {
    
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
{
    str[0] = 0 ;
    for (int i=0; i<L; i++) {
        sprintf(str, "%s%d ", str, Seq[i]);
    }
}