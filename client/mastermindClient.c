#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mastermindClient.h"          // Fonctions du jeu, coté client
#include "./../outils/verificationInput.h"           // Fonctions de verification d'input
#include "./../outils/outils.h"                      // Fonctions de conversion


void texteASeqInt(char txt[], int* seqTentative, int* L) ;

void imprimerRegles ()
/*
    Imprime les régles du jeu.
*/
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
/*
    Demande la difficulté du jeu au joueur. Et verifie que la reponse est correcte.
    Reitere si ce n'est pas le cas.

    Output:
        int :
                difficulté du jeu: entre 5-7 couleurs.
*/ 
{
	char input[2000] = "a";
    const char msg[] = "\n\nAvec combien couleurs voulez-vous jouer? [5-7]: ";

    // Verifier si il y a que de chiffres dans le string
    while (!digitsOnly(input)) {
		printf("%s", msg);
		scanf("%s", input );
	}
    // Le forcer dans le range correcte.
	sprintf( input , "%d", intoRange(input, 5, 7) ) ;
	return atoi(input) ;
}


void introduirTentative(char niveauDiff)
/*
    Rappel au joueur les couleurs en jeu.

    Input :
        char niveauDiff :
                niveau de difficulté: nombre de couleurs en jeu.
    
    Output :
        void
*/
{
    // Afficher les couleurs possibles
    char introTentative[1000] = "\nPour rappel les couleurs possibles sont:  " ;
    
    // Obtenir les couleurs
    for (int j = 0; j < niveauDiff-1; ++j)
    {
        sprintf(introTentative, "%s%s-", introTentative, conversion[j].str);
    }
    sprintf(introTentative, "%s%s-", introTentative, conversion[niveauDiff-1].str);
    // Suite du message
    strcat( introTentative, "\nEntrez la séquence de couleur proposée (séparé par des tirets):\n");
    // Imprimer le message
    printf( "%s", introTentative) ;
}


void ecritureTentative(int sequence[], int*L, int nvDiff)
/*
    Ecrit le texte de chaque tour, rappelant les couleurs en jeu et recupere la
    combination du joueur, en verifiant que les couleurs correspondent aux couleurs en jeu
    et au format demandé. Sinon on reitere.

    Input :
        int sequence [] :
                tableau ou on va ecrire la sequence du joueur
        int* L :
                taille du tableau. Normalement est toujours 4.
        int nvDiff :
                niveau de difficulté, nombre de couleurs en jeu.

    Outpu :
        void
*/
{
    char seq_tentative_str[1000] = "a";

    // Verifier:
    //  - 4 couleurs
    //  - separés par des '-'
    //  - les couleurs correspondent aux couleurs donnés
    while (!strEnFormat(seq_tentative_str, nvDiff))
    {
        introduirTentative(nvDiff) ;
        scanf("%s", seq_tentative_str);
    }
	// Transformer le text des couleurs en sequence des entiers.
    texteASeqInt(seq_tentative_str, sequence, L) ;
}


void faireRetour(int nbBienPlaces, int nbMalPlaces)
/*
    Fait le retour au joueur en fonction de son combination:
    Il verbalise le nombre de couleurs bien placés, nbBienPlaces, et le nombre de 
    couleurs mal placés, nbMalPlaces.

    Input :
        int nbBienPlaces :
                nombre de couleurs bien placés
        int nbMalPlaces :
                nombre de couleurs mal placés
    
    Output : 
        void
*/
{
    char mess_tentative[1000] = "\nVous avez trouvé ";

    sprintf(mess_tentative, "%s%d", mess_tentative, nbBienPlaces);
    strcat(mess_tentative, " bonnes couleurs bien placées et ");
    sprintf(mess_tentative, "%s%d", mess_tentative, nbMalPlaces);
    strcat(mess_tentative, " couleurs présentes mais mal placées\n");

    printf("%s", mess_tentative);
}


void donnerPoints(int nbTours, int score)
/*
    Affiche du message de fin de jeu quand la séquence a été découverte. 
    Il inclu le nombre de tours et le score final.

    Input :
        int nbTours :
                nombre de tours utilisés pour trouver la combination secrète.
        int score :
                le nombre de points obtenus.
    Output :
        void
*/
{
    char messFin[1000] = "\nBravo, vous avez trouvé la séquence secrète en ";

    sprintf(messFin, "%s%d tours !\n", messFin, nbTours);
    sprintf(messFin, "%sVotre score est de %d points !\n\n", messFin, score);

    printf("%s", messFin);
}

// CONVERSION DU TEXTE EN SEQUENCE D'ENTIERS


Couleurs str2enum(const char *str)
/*
    Fonction de conversion de string a couleur du jeu.

    Input :
        char *str :
                couleur du jeu en format string.

    Output :
        Couleurs :
                couleur du jeu
*/
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

void texteASeqInt(char txt[], int* seqTentative, int* L)
/*
    Converti un texte, txt, avec des couleurs en string, separés par de tirés, '-'
    a une séquence d'entiers, seqTentative, de taille L.

    Input :
        char txt[] :
                string d'entrée, a convertir.
        int* seqTentative :
                tableau où la séquence va être écrite.
        int* L :
                taille du tableau. Normalement L=4.
    
    Output :
        void

*/
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
        while ((txt[j] != '-') && (txt[j] != 0))
        {
            couleur[c] = txt[j];
            j = j + 1;
            c = c + 1;
        };
        couleur[c] = 0;
        nomCouleur = str2enum(couleur);
        seqTentative[i] = nomCouleur;
        c = 0;
        j = j + 1;
    }
    *L = i ;
}
