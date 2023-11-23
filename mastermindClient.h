#define LmaxSeq 4

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

void imprimerRegles () ;

int demanderDifficulte () ;

void ecritureTentative(int sequence[], int*L, int nvDiff) ;

void faireRetour(int nbBienPlaces, int nbMalPlaces) ;

void donnerPoints(int nbTours, int score) ;


