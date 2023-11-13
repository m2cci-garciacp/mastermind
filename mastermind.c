#include <stdio.h>
#include <stdlib.h>
#define L 5


int EstPresent(int x, int seq_cible[L]);
int trouve;
// typedef {}ls_color
int seq_cible[L];

void initialisation(int T[L])
{
    int nv_diff;
    printf("Choix de la difficulté \n");
    scanf("%d", &nv_diff);
    int i;
    // Choix de la séquence de couleur 
    for (i = 0; i < 4; i++)
    {
        T[i] = rand() % (nv_diff+1);
    }

    for (i = 0; i < 4; i++)
    {
        printf(" %d", T[i]);
    }
}

void tentative()
{
    int seq_tent[L];
    int i;
    int nb_ok, nb_mp;
    nb_mp = 0;
    nb_ok = 0;
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

int main()
{
    trouve = 0;
    initialisation(seq_cible);
    while (trouve != 1)
    {
        tentative();
    }

    return 0;
}