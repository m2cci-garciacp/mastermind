#include <stdio.h>
#include <stdlib.h>
#include "mastermind.h"
#define L 5




int EstPresent(int x, int seq_cible[L]);
int trouve;
// typedef {}ls_color
int seq_cible[L];

void initialisation(int combinationSecrete[])
{
    int nv_diff;
    // printf("Choix de la difficulté \n");
    // scanf("%d", &nv_diff);
    int i;
    // Choix de la séquence de couleur 
    for (i = 0; i < 4; i++)
    {
        combinationSecrete[i] = rand() % 5 ;
    }

    // for (i = 0; i < 4; i++)
    // {
    //     printf(" %d", seq_cible[i]);
    // }
}

ResultTentative  tentative(int seq[L])
{
    int seq_tent[L];
    int i;
    int nb_ok, nb_mp;
    nb_mp = 0;
    nb_ok = 0;
    ResultTentative Res;
    Res.Trouve=0;
    // traduction de la seq ?
    // Lecture de la tentative
    for (i = 0; i < 4; i++)
    {
        printf("Entrez la couleur %d : ", i);
        scanf("%d", &seq_tent[i]);
    }
    printf("Sequence tapée: \n");
    for (i = 0; i < 4; i++)
    {
        printf(" %d", seq_tent[i]);
    }

    for (i = 0; i < 4; i++)
    {
        if (seq_tent[i] == seq_cible[i])
        {
            nb_ok = nb_ok + 1;
        }
        else
        {

            nb_mp = nb_mp + EstPresent(seq_tent[i], seq_cible);
        }
    }
    if (nb_ok==4){
        printf("\nBravo, séquence trouvée");
        trouve=1;
    }
    else {
    printf("\nNombre de mal placé %d \n", nb_mp);
    printf("Nombre de justes %d \n", nb_ok);
    }
    Res.nbCorrect=nb_ok;
    Res.nbMalPlaces=nb_mp;
    Res.Trouve = trouve;
    
    return Res;
}

int EstPresent(int x, int seq_cible[L])
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (x == seq_cible[i])
        {
            return 1;
        }
    }
    return 0;
}

char * printRegles(){
    char rules[] = "Ce jeu blablabla" ;
    return rules;
}



char * fin(){
    char messFin[] ="Bravo, vous avez trouvé la séquence";
    return messFin;

}

/*int main()
{
    trouve = 0;
    initialisation(seq_cible);
    while (trouve != 1)
    {
        tentative();
    }

    return 0;
}
*/