#include <string.h>
#include <stdlib.h>

#include "verificationInput.h"          /* Fonctions pour verifier les inputs du joueur */
#include "mastermindClient.h"           /* Fonctions du Jeu Client */

int strEnFormat(char *str, int nvDiff)
/*
    Verifie qu'un string est forme par les couleurs du niveau de difficulte.
    Qu'il y a le nombre de coleurs necessaire (=4).

    Input: 
        char str[] :
                string d'entrée.
        int nvDiff :
                Nivel de difficulté.
    Output:
        int : 1 si le str est du bon format, sino 0.
*/
{
	char * coleurs[2000] ;
	char word[2000] ;
    char cpt = 0;
    char separateur = '-' ;
	int i=0, j=0 ;

    strcpy( word ,  "");
    if (strlen(str)==0) return 0;
	while ( str[j] != 0) {
		if (str[j]!=separateur) {
			strncat(word, &(str[j]), 1) ;
		} else {
            cpt++;
			if ( 1-coleurEnJeu(word, nvDiff) ) {
                return 0;
            }			
			strcpy( word , "" ) ;
		}
		j++;
	}

    if ( (coleurEnJeu(word, nvDiff) && cpt==3) || (strcmp(word,"")==0 && cpt==4 )) {
        return 1;
    } else {
        return 0;
    }
}

int digitsOnly(char *s)
/*
    Verifie que le str est forme par chiffres. Selon le code ascii.

    Input: 
        char str[] :
                string d'entrée.
    Output:
        int : 1 si le str n'est forme que par chiffres, sino 0.
*/
{	
	int i=0;
    while (s[i]) {
        if ( s[i]<48 || s[i]>57 ) return 0;
		i++;
    }
	
    return 1;
}



int intoRange(char *s, int a, int b)
/*
    Verifie que le str, s, est entre a et b. 
    Si c'est plus petit que a, retourne a.
    Si c'est plus grand que b, retourne b.
    Sinon retourne atoi(s).

    Input: 
        char str[] :
                string d'entrée.
        int a :
                borne inferieur du range
        int b :
                borne superieur du range
    Output:
        int : si atoi(s) en [a,b] 
                retourne atoi(s) 
              si atoi(s)<a 
                retourne a 
              sinon 
                retourn b
*/
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



int coleurEnJeu (char * word, int nvDiff) 
/*
    Verifie que le str, word, appartient aux couleurs de jeu correspondant
    au niveau de difficulte, nvDiff.

    Input: 
        char /*word :
                couleur a tester.
        int nvDiff :
                niveau de difficulte
    Output:
        int : 1 si word appartient aux couleurs de jeu, sinon 0.
*/
{
    int i;
    for (i=0; i<nvDiff; i++) {
		if (strcmp(word, conversion[i].str)==0) break;
    }
	if (i==nvDiff) {
        return 0 ;
    } else {
        return 1 ;
    }
}