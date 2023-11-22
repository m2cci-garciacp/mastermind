#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mastermind.h"
#define LmaxSeq 4
#define LmaxMess 1000

int nv_diff;
char seq_tentative_str[LmaxMess];
int seq_tentative[LmaxSeq];
char messFin[LmaxMess];

typedef enum
{
    bleu,
    rouge,
    vert,
    jaune,
    orange,
    rose,
    noir
} Couleurs;
//"Tableau" de conversion des string en enum Couleurs
const static struct
{
    Couleurs val;
    const char *str;
} conversion[] = {
    {bleu, "bleu"},
    {rouge, "rouge"},
    {vert, "vert"},
    {jaune, "jaune"},
    {orange, "orange"},
    {rose, "rose"},
    {noir, "noir"},
};

// Fonction retournant 1 si l'entier est présent dans une séquence ou 0 si il est absent
/*int EstPresent(int x, int seq_cible[LmaxSeq],int seq_comment[LmaxSeq] )
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if ((x == seq_cible[i]) && (seq_comment[i] == 0))
        {
            seq_comment[i]=1;
            return 1;
        }
    }
    return 0;
}*/

// Fonction d'initialisation du jeu, préparation de la séquence à découvrir
void initialisation(int combinationSecrete[LmaxSeq], char * niveauDiff)
{

    nv_diff = atoi(niveauDiff);
    if (nv_diff<5) {nv_diff=5;}
    else if (nv_diff>7) {nv_diff=7;}

    int i;
    srand(time(NULL));
    // Choix de la séquence de couleur
    for (i = 0; i < 4; i++)
    {
        combinationSecrete[i] = rand() % nv_diff;
    }

    for (i = 0; i < 4; i++)
    {
        printf(" %d \n", combinationSecrete[i]); //A enlever
    }
}

// Présentation des règles
const char * printRegles()
{
    static char regles[2000] = "\nBienvenue dans Mastermind ! \nLe but de ce jeu est de deviner le plus rapidement possible une séquence de 4 couleurs dans le bon ordre.\n\nVous allez devoir tenter de deviner la combinaison secrète en soumettant une séquence de 4 couleurs qui vous semble correcte.\n Après chaque tentative il vous sera fait un retour sur le nombre de couleurs correctement placées dans votre séquence ainsi que le nombre de couleurs bien présente dans la combinaison secrète mais mal placées.\n Attention il est possible que la même couleur soit présente plusieurs fois dans la combinaison secrète. Lors de la rentrée d'une tentative il est nécessaire de faire attention à l'orthographe des couleurs et de rentrer la séquence avec des tirets entre chaque couleurs (exemple: jaune-vert-rouge-vert)\nEnfin, il est possible de choisir le nombre de couleurs différentes qui pourra être présente dans la combinaison secrète et donc augmenter la difficulté du jeu !";
    return regles ;
}
// Faire une fonction qui lit la séquence proposée

const char *introTentative()//A adapter au client
{
    // Afficher les couleurs possibles
    static char txt[200] = "" ;
    static char txtTampon[200] ;
    int j;
    strcpy( txt, "\nPour rappel les couleurs possibles sont: " );
    for (j = 0; j < nv_diff-1; ++j)
    {
        sprintf(txtTampon, "%s-", conversion[j].str);
        strcat( txt, txtTampon );
    }
    sprintf(txtTampon, "%s", conversion[nv_diff-1].str);
    strcat( txt, txtTampon );


    strcat( txt, "\nEntrez la séquence de couleur proposée (séparé par des tirets): ");
    return txt;
}
const char *ecritureTentative()//A adapter au client
{
    // Afficher les couleurs possibles
    static char seq_tentative_str[200] ;

    scanf("%s", seq_tentative_str);

    return seq_tentative_str;
}

// Fonction appelée à chaque tentative de découverte. On soumet une séquence pour tenter de deviner la séquence
// mystère. Cette fonction retourne une structure du type <Int : Nombre de couleurs bien placée, Int: Nombre de couleur présentes mais mal placées, Booléén: Est-ce que la séquence à été découverte ou pas>
ResultTentative tentative(int seq[LmaxSeq], int seq_cible[LmaxSeq])
{
    int seq_aide_cible[LmaxSeq];
    int seq_aide_tentative[LmaxSeq];
    int i,j;
    int nb_ok, nb_mp;
    nb_mp = 0;
    nb_ok = 0;
    ResultTentative Res;
    Res.trouve = 0;

    // Initialisation de la séquence aide à 0

    for (i = 0;i<4;i++){
        seq_aide_cible[i]=0;
        seq_aide_tentative[i]=0;
    }

    //Calcul du nombre de correctes
    for (i = 0; i < 4; i++)
    {
        if (seq[i] == seq_cible[i])
        {
            nb_ok = nb_ok + 1;
            seq_aide_cible[i]=1;
            seq_aide_tentative[i]=1;
        }

    }
    //Puis calcul du nombre de mal placés
    for (i= 0; i < 4; i++)
    {
        for (j=0;j<4;j++){
           if ((seq[i] == seq_cible[j]) && (seq_aide_cible[j] == 0)&& (seq_aide_tentative[i]==0) )
        {
            nb_mp = nb_mp + 1;
            seq_aide_cible[j]=1;
            seq_aide_tentative[i]=1;
           
        }
        }
       

    }
    
    if (nb_ok == 4)
    {
        Res.trouve = 1;
    }

    Res.nbCorrect = nb_ok;
    Res.nbMalPlaces = nb_mp;

    return Res;
}

// Affichage du message relié au résultat de la tentative

const char *resultatATexte(ResultTentative resultat)
{
    static char mess_tentative[LmaxMess];
    memset(mess_tentative, 0, LmaxMess);
    char numToText[10];
    strcpy(mess_tentative, "\nVous avez trouvé ");
    sprintf(numToText, "%d", resultat.nbCorrect);
    strcat(mess_tentative, numToText);

    strcat(mess_tentative, " bonnes couleurs bien placées et ");
    sprintf(numToText, "%d", resultat.nbMalPlaces);
    strcat(mess_tentative, numToText);
    strcat(mess_tentative, " couleurs présentes mais mal placées");

    return mess_tentative;
}

// Affichage du message de fin de jeu quand la séquence a été découverte
char *fin()
{
    strcpy(messFin, "\nBravo, vous avez trouvé la séquence !\n");
    return messFin;
}

// CONVERSION DU TEXTE EN SEQUENCE D'ENTIERS

// Fonction de converison
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

int *texteASeqInt(char txt[])
{

    char couleur[LmaxMess];
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
        printf(">>%s", couleur);
        nomCouleur = str2enum(couleur);
        printf("\t%d\n", nomCouleur);
        seq_tentative[i] = nomCouleur;
        c = 0;
        j = j + 1;
    }

    return seq_tentative;
}

/* int main()
{
    // Pour test avec la fonction main
    int combinationSecrete[LmaxSeq];
    char msg_out[LmaxMess];
    ResultTentative resultat;
    resultat.trouve = 0;
    strcpy(msg_out, printRegles());
    printf("%s", msg_out);
    initialisation(combinationSecrete);

    while (resultat.trouve == 0)
    {

        strcpy(seq_tentative_str, ecritureTentative());
        texteASeqInt(seq_tentative_str);
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
} */
