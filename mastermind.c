#include <stdio.h>
#include <stdlib.h>
#include "mastermind.h"
#define LmaxSeq 4
#define LmaxMess 200


char mess_tentative[LmaxMess];
int seq_cible[LmaxSeq];
int seq_tentative[LmaxSeq];


typedef enum {bleu, rouge, vert, jaune, orange,rose,noir} Couleurs;



//Fonction retournant 1 si l'entier est présent dans une séquence ou 0 si il est absent 
int EstPresent(int x, int seq_cible[LmaxSeq])
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

//Fonction d'initialisation du jeu, préparation de la séquence à découvrir
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

//Présentation des règles
char * printRegles(){    
    char rules[LmaxMess] = "Ce jeu blablabla Tiret entre les couleurs rentrées et terminé par un tiret (-) pour l'instant parce que j'ai pas finit " ;
    return rules;
}

//Fonction appelée à chaque tentative de découverte. On soumet une séquence pour tenter de deviner la séquence
//mystère. Cette fonction retourne une structure du type <Int : Nombre de couleurs bien placée, Int: Nombre de couleur présentes mais mal placées, Booléén: Est-ce que la séquence à été découverte ou pas>
ResultTentative  tentative(int seq[LmaxSeq])
{
    int seq_tent[LmaxSeq];
    int i;
    int nb_ok, nb_mp;
    nb_mp = 0;
    nb_ok = 0;
    ResultTentative Res;
    Res.trouve=0;
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
        Res.trouve=1;
    }
    else {
    printf("\nNombre de mal placé %d \n", nb_mp);
    printf("Nombre de justes %d \n", nb_ok);
    }
    Res.nbCorrect=nb_ok;
    Res.nbMalPlaces=nb_mp;
    
    return Res;
}

//Affichage du message relié au résultat de la tentative

char *resultatATexte(ResultTentative resultat)
{
    memset(mess_tentative, 0, LmaxMess);
    char numToText[10];
    strcpy(mess_tentative,"Vous avez trouvé " );
    sprintf(numToText,"%d",resultat.nbCorrect);
    strcat(mess_tentative,numToText);

    strcat(mess_tentative," bonnes couleurs bien placées et ");
    sprintf(numToText,"%d",resultat.nbMalPlaces);
    strcat(mess_tentative,numToText);
    strcat(mess_tentative," couleurs présentes mais mal placées");
    
    return mess_tentative; 
}

//Affichage du message de fin de jeu quand la séquence a été découverte
char * fin(){
    char messFin[] ="Bravo, vous avez trouvé la séquence";
    return messFin;

}


//CONVERSION DU TEXTE EN SEQUENCE D'ENTIERS

//"Tableau" de conversion des string en enum Couleurs
const static struct {
    Couleurs      val;
    const char *str;
} conversion [] = {
    {bleu, "bleu"},
    {rouge, "rouge"},
    {vert, "vert"},
    {jaune, "jaune"},
    {orange, "orange"},
    {noir, "noir"},
};
//Fonction de converison 
Couleurs
strToEnum (const char *str)
{
     int j;
     for (j = 0;  j < sizeof (conversion) / sizeof (conversion[0]);  ++j){
         if (!strcmp (str, conversion[j].str)){
             return conversion[j].val;
         }
     }
    return 0;
    }


int *texteASeqInt(char *txt) {
    
    char couleur[LmaxSeq];
    Couleurs nomCouleur;
    int i, j, c;
    j = 0;
    c = 0;
    //Séparation des 4 couleurs différentes
    for (i = 0; i < 4; i++)
    {
        while (txt[j] != '-')
        {
            couleur[c] = txt[j];
            printf("couleur: %s",couleur);
            printf("j: %d\n",j);
            j = j + 1;
            c = c+1;
        };
        nomCouleur = str2enum(couleur);
        seq_tentative[i] = nomCouleur;
        c = 0;
        j = j+1;
        //Vider le tableau pour prendre en compte la prochaine couleur
        memset(couleur, 0, LmaxSeq);
    
       
    }
     return seq_tentative;
}



