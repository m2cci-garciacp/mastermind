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

typedef struct {
    int nbCorrect; int nbMalPlaces; int trouve;
} ResultTentative;

int initialisation(int combinaisonSecrete[LmaxSeq], char * niveauDiff) ;
const char * printRegles() ;

ResultTentative  tentative(int seq[LmaxSeq],int seq_cible[LmaxSeq]);

char * fin() ;

// faudra changer cettes fonctions, une fois on a decide le format d'envoi
int * texteASeqInt(char *txt) ;
const char * resultatATexte(ResultTentative resultat) ;

//Client
const char *introTentative(int nv_diff);
void ecritureTentative(char str[], char str0[], int nv_diff);


