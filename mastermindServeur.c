#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mastermindServeur.h"


int calculerPontuation(int nbTours) ;


// Fonction d'initialisation du jeu, préparation de la séquence à découvrir
void initialisation(int* combinationSecrete, int niveauDiff)
{

    int i;
    srandom(time(NULL));
    // Choix de la séquence de couleur
    for (i = 0; i < 4; i++)
    {
        combinationSecrete[i] = random() % niveauDiff;
    }

    printf("Sequence secrete: ");
    for (i = 0; i < 4; i++)
    {
        printf("%d ", combinationSecrete[i]);
    }
    printf("\n");
}




// Fonction appelée à chaque tentative de découverte. On soumet une séquence pour tenter de deviner la séquence
// mystère. Cette fonction retourne une structure du type <Int : Nombre de couleurs bien placée, Int: Nombre de couleur présentes mais mal placées, Booléén: Est-ce que la séquence à été découverte ou pas
void tentative(int seq[LmaxSeq],int sequenceSecrete[LmaxSeq], int* reponse, int*L, int nbTours)
{
    int seq_aide_cible[LmaxSeq];
    int seq_aide_tentative[LmaxSeq];
    int i,j;
    int nb_ok, nb_mp;
    nb_mp = 0;
    nb_ok = 0;
    (*L) = 2;

    // Initialisation de la séquence aide à 0
    for (i = 0;i<4;i++){
        seq_aide_cible[i]=0;
        seq_aide_tentative[i]=0;
    }

    //Calcul du nombre de correctes
    printf("NbCOrrectes:\n");
    for (i = 0; i < 4; i++)
    {   

        printf("%d-%d=%d\n",seq[i], sequenceSecrete[i],seq[i]-sequenceSecrete[i]);
        if (seq[i] == sequenceSecrete[i])
        {
            nb_ok = nb_ok + 1;
            seq_aide_cible[i]=1;
            seq_aide_tentative[i]=1;
        }

    }
    reponse[0] = nb_ok;

    if (nb_ok != 4) {
    //Puis calcul du nombre de mal placés
        for (i= 0; i < 4; i++)
        {
            for (j=0;j<4;j++){
            if ((seq[i] == sequenceSecrete[j]) && (seq_aide_cible[j] == 0)&& (seq_aide_tentative[i]==0) )
            {
                nb_mp = nb_mp + 1;
                seq_aide_cible[j]=1;
                seq_aide_tentative[i]=1;
            
            }
            }
        

        }
        reponse[1] = nb_mp;
    } else { // nb_ok == 4
    printf("tous bien places\n");
        reponse[1] = nb_mp;
        reponse[2] = nbTours;
        reponse[3] = calculerPontuation(nbTours);
        (*L) = 4 ;
    }

}

int calculerPontuation(int nbTours) {
    switch (nbTours){
        case 1: return 100;
        case 2: return 90;
        case 3: return 80;
        case 4: return 70;
        case 5: return 60;
        case 6: return 50;
        case 7: return 40;
        case 8: return 30;
        case 9: return 20;
        case 10: return 15;
        case 11: return 10;
        case 12: return 7;
        case 13: return 5;
        case 14: return 4;
        case 15: return 3;
        case 16: return 2;
        case 17: return 1;
        default: return 0;
    }
}

