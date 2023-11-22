#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mastermind.h"

#define LmaxSeq 4
#define LmaxMess 1000

/* int nv_diff;
char regles[LmaxMess];
char messFin[LmaxMess]; */

int main()
{
    char mess_tentative[LmaxMess];
    char seq_tentative_str[LmaxMess];
    int *seq_tentative;
    // Pour test avec la fonction main
    int combinationSecrete[LmaxSeq];
    char msg_out[LmaxMess];
    ResultTentative resultat;
    resultat.trouve = 0;
    strcpy(msg_out, printRegles());
    printf("%s", msg_out);
    initialisation(combinationSecrete, "5"); // 5 est la difficulte, en string

    while (resultat.trouve == 0)
    {

		strcpy( msg_out , introTentative() ) ;
        printf("%s", msg_out);
        scanf("%s", seq_tentative_str);
        seq_tentative = texteASeqInt(seq_tentative_str);
        resultat = tentative(seq_tentative, combinationSecrete);

        if (resultat.trouve != 0)
        {
            strcpy(msg_out, fin());
        }
        else
        {
            strcpy(msg_out, resultatATexte(resultat)); // convertir result_tentative a bonne format str pour client
        }
        printf("%s", msg_out);
    }
}
