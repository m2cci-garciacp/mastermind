#include <string.h>
#include <stdlib.h>
#include "verificationInput.h"
#include "mastermind.h"

int strEnFormat(char *str, int nv_diff)
{
	char * coleurs[2000] ;
	char word[2000] ;
    char cpt = 0;
    char separateur = '-' ;
	int i=0, j=0 ;

    //printf("niv_diff=%d\n", nv_diff);  //TODO: nv_diff nest pas global
    strcpy( word ,  "");
    if (strlen(str)==0) return 0;
	while ( str[j] != 0) {
        //printf("%c %c", str[j], str[j]==separateur);
		if (str[j]!=separateur) {
			strncat(word, &(str[j]), 1) ;
		} else {
            //printf("%s(%d) : %d\n", word,strlen(word), coleurEnJeu(word, nv_diff)) ;
            cpt++;
			if ( 1-coleurEnJeu(word, nv_diff) ) {
                return 0;
            }
			
			strcpy( word , "" ) ;
		}
		j++;
	}

    if ( (coleurEnJeu(word, nv_diff) && cpt==3) || (strcmp(word,"")==0 && cpt==4 )) {
        return 1;
    } else {
        return 0;
    }
}

int digitsOnly(char *s)
{	
	int i=0;
    while (s[i]) {
        if ( s[i]<48 || s[i]>57 ) return 0;
		i++;
    }
	
    return 1;
}



int intoRange(char *s, int a, int b)
{	
	int answer ;
    if (digitsOnly(s)) {
        if (atoi(s)> b) {answer=b;}
        else if (atoi(s)<a) {answer=a;}
        else {answer=atoi(s);}
		return answer;
    }
	else { return 0;}
}



int coleurEnJeu (char * word, int nv_diff) {
    int i;
    for (i=0; i<nv_diff; i++) {
		if (strcmp(word, conversion[i].str)==0) break;
    }
	if (i==nv_diff) {
        return 0 ;
    } else {
        return 1 ;
    }
}