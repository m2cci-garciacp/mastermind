#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mastermindServeur.h"         // Fonctions du jeu , coté serveur


int calculerPontuation(int nbTours) ;



void initialisation(int* combinationSecrete, int niveauDiff)
/*
    Fonction d'initialisation du jeu. Etant donné le niveau de difficulté
    crée la combination secrète de manière pseudo-aleatoire, et la stocke
    dans combinationSecrete.

    Input:
        int niveauDiff :
                niiveau de difficulte: nombre de couleurs en jeu
    int* combinationSecrete :
                pointeur du tableau ou on stocke la combination secrète.

    Output :
        void
*/
{
    srandom(time(NULL));
    // Choix de la combination secrète
    printf("Sequence secrete: ");
    for (int i = 0; i < 4; i++)
    {
        combinationSecrete[i] = random() % niveauDiff;
        printf("%d ", combinationSecrete[i]);
    }
    printf("\n");
}




void tentative(int seq[],int combinationSecrete[], int* reponse, int*L, int nbTours)
/*
    Fonction appelée à chaque tour. On soumet une combination du joueur, seq, pour tenter de 
    deviner la séquence mystère, combinationSecrete . Elle calcule les nombre de couleurs bien places
    et le nombre de couleurs mal places.
    
    Input :
        int seq[] :
                Tableau avec combination du joueur.
        int combinationSecrete[] :
                Tableau avec combination secrète à deviner.
        int* reponse :
                Tableau avec la reponse: 
                    - reponse[0] : les couleurs bien placés
                    - reponse[1] : les couleurs mal placés
                    - reponse[2] : si la combination du joueur est correcte : nombre de tours.
                    - reponse[1] : si la combination du joueur est correcte : score final.
        int*L :
                Taille de la reponse:
                    - L=2 : si la combination du joueur est incorrecte, la partie continue.
                    - L=4 : si la combination du joueur est   correcte, la partie est finie.
        int nbTours :
                Nombre de tours courant.
    Output :
        void
*/
{
    int seqAide[LmaxSeq], seqAideJoueur[LmaxSeq]; 
    int i,j;
    int nb_ok, nb_mp;
    nb_mp = 0;
    nb_ok = 0;
    (*L) = 2;

    //Calcul du nombre de correctes
    printf("NbCOrrectes:\n");
    for (i = 0; i < 4; i++)
    {   
        if (seq[i] == combinationSecrete[i])
        {
            nb_ok = nb_ok + 1;
            seqAide[i]=1;
            seqAideJoueur[i]=1; 
        } 
        else
        {
            seqAide[i]=0;
            seqAideJoueur[i]=0;
        }

    }
    reponse[0] = nb_ok;

    if (nb_ok != 4) 
    {
        // Puis calcul du nombre de mal placés
        for (i= 0; i < 4; i++)
        {
            for (j=0;j<4;j++)
            {
                if ( (seq[i] == combinationSecrete[j]) && (seqAideJoueur[i]==0)  && (seqAide[j]==0) )
                {
                    nb_mp = nb_mp + 1;
                    seqAide[j]=1;
                    seqAideJoueur[i]=1;         
                }
            }
        }
        reponse[1] = nb_mp;
    } 
    else 
    {
        // Tous correctes : la taille de la reponse est 4.
        reponse[1] = nb_mp;
        reponse[2] = nbTours;
        reponse[3] = calculerPontuation(nbTours);
        (*L) = 4 ;
    }

}

int calculerPontuation(int nbTours)
/*
    Cette fonction calcule la ponctuation en fonction du nombre de tours, nbTours.

    Input :
        int nbTours :
                nombre de tours tuilisés pour trouver la combination secrète
    
    Output :
        int :
            ponctuation qui vaut dans les cas extremes: 100 pour nbTours=1, 0 pour nbTours>=18
    
*/
{
    switch (nbTours)
    {
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

