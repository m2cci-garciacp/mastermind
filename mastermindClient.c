#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "verificationInput.h"
#include "mastermindClient.h"
#include "outils.h"

// #define LmaxSeq 4
// #define LmaxMess 1000

void texteASeqInt(char txt[], int* seq_tentative, int* L) ;

void imprimerRegles () 
{
    printf("\nBienvenue dans Mastermind ! \nLe but de ce jeu est de deviner le plus rapidement possible une ");
    printf("séquence de 4 couleurs dans le bon ordre.\n\nVous allez devoir tenter de deviner la combinaison ");
    printf("secrète en soumettant une séquence de 4 couleurs qui vous semble correcte.\n Après chaque tentative ");
    printf("il vous sera fait un retour sur le nombre de couleurs correctement placées dans votre séquence ainsi ");
    printf("que le nombre de couleurs bien présente dans la combinaison secrète mais mal placées.\n Attention il ");
    printf("est possible que la même couleur soit présente plusieurs fois dans la combinaison secrète. Lors de la ");
    printf("rentrée d'une tentative il est nécessaire de faire attention à l'orthographe des couleurs et de rentrer ");
    printf("la séquence avec des tirets entre chaque couleurs (exemple: jaune-vert-rouge-vert)\nEnfin, il est possible ");
    printf("de choisir le nombre de couleurs différentes qui pourra être présente dans la combinaison secrète et donc ");
    printf("augmenter la difficulté du jeu !");
}


int demanderDifficulte () 
{
	char input[2000] = "a";
    char msg[] = "\n\nAvec combien couleurs voulez-vous jouer? [5-7]: ";

    while (!digitsOnly(input)) {
		printf("%s", msg);
		scanf("%s", input );
	}
	sprintf( input , "%d", intoRange(input, 4, 7) ) ;
	return atoi(input) ;
}

// Fonction d'initialisation du jeu, préparation de la séquence à découvrir
void introduirTentative(char niveauDiff)
{
    // Afficher les couleurs possibles
    char introTentative[1000] = "\nPour rappel les couleurs possibles sont:  " ;
    int j;
    for (j = 0; j < niveauDiff-1; ++j)
    {
        sprintf(introTentative, "%s%s-", introTentative,conversion[j].str);
    }
    sprintf(introTentative, "%s%s-", introTentative,conversion[niveauDiff-1].str);

    strcat( introTentative, "\nEntrez la séquence de couleur proposée (séparé par des tirets):\n");

    printf( "%s", introTentative) ;
}


void ecritureTentative(int sequence[], int*L, int nv_diff)
{
    char seq_tentative_str[1000] = "a";

    // Verifier:
    //  - 4 couleurs
    //  - separes par des '-'
    //  - les couleurs correspondent aux couleurs donnés
    while (!strEnFormat(seq_tentative_str, nv_diff))
    {
        introduirTentative(nv_diff) ;
        scanf("%s", seq_tentative_str);
    }

    //
    texteASeqInt(seq_tentative_str, sequence, L) ;
}

// Affichage du message relié au résultat de la tentative
void faireRetour(int nbBienPlaces, int nbMalPlaces) 
{
    char mess_tentative[1000] = "\nVous avez trouvé ";

    sprintf(mess_tentative, "%s%d", mess_tentative, nbBienPlaces);
    strcat(mess_tentative, " bonnes couleurs bien placées et ");
    sprintf(mess_tentative, "%s%d", mess_tentative, nbMalPlaces);
    strcat(mess_tentative, " couleurs présentes mais mal placées\n");

    printf("%s", mess_tentative);
}

// Affichage du message de fin de jeu quand la séquence a été découverte
void donnerPoints(int nbTours, int score)
{
    char messFin[1000] = "\nBravo, vous avez trouvé la séquence secrète en ";

    sprintf(messFin, "%s%d tours !\n", messFin, nbTours);
    sprintf(messFin, "%sVotre score est de %d points !\n\n", messFin, score);

    printf("%s", messFin);
}

// CONVERSION DU TEXTE EN SEQUENCE D'ENTIERS

// Fonction de conversion
Couleurs
str2enum(const char *str)
{
    int j;
    for (j = 0; j < sizeof(conversion) / sizeof(conversion[0]); ++j)
    {
        if (!strcmp(str, conversion[j].str))
        {
            return conversion[j].val;
        }
    }
    return 0;
}

void texteASeqInt(char txt[], int* seq_tentative, int* L)
{

    char couleur[1000];
    Couleurs nomCouleur;
    int i, j, c;
    j = 0;
    c = 0;
    
    // Séparation des 4 couleurs différentes
    for (i = 0; i < 4; i++)
    {
        // Vider le tableau pour prendre en compte la prochaine couleur
        memset(couleur, 0, sizeof(couleur));
        while ((txt[j] != '-') && (txt[j] != '0'))
        {

            couleur[c] = txt[j];

            j = j + 1;
            c = c + 1;
        };
        nomCouleur = str2enum(couleur);
        seq_tentative[i] = nomCouleur;
        c = 0;
        j = j + 1;
    }
    *L = i ;
}



