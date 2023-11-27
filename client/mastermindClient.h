#define LmaxSeq 4

typedef enum
{
    bleu,
    rouge,
    vert,
    jaune,
    orange,
    magenta,
    noir
} Couleurs;

//"Tableau" de conversion des string en enum Couleurs
const static struct
{
    Couleurs val;
    const char *str;
} conversion1[] = {
    {bleu, "bleu"},
    {rouge, "rouge"},
    {vert, "vert"},
    {jaune, "jaune"},
    {orange, "orange"},
    {magenta, "magenta"},
    {noir, "noir"},
};
const static struct
{
    Couleurs val;
    const char *str;
} conversion2[] = {
    {bleu, "b"},
    {rouge, "r"},
    {vert, "v"},
    {jaune, "j"},
    {orange, "o"},
    {magenta, "m"},
    {noir, "n"},
};

void imprimerRegles () ;

int demanderDifficulte () ;

void ecritureTentative(int sequence[], int*L, int nvDiff) ;

void faireRetour(int nbBienPlaces, int nbMalPlaces) ;

void donnerPoints(int nbTours, int score) ;


