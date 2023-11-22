#define LmaxSeq 4

typedef struct {
    int nbCorrect; int nbMalPlaces; int trouve;
} ResultTentative;

void initialisation(int combinaisonSecrete[LmaxSeq], char * niveauDiff) ;
const char * printRegles() ;

ResultTentative  tentative(int seq[LmaxSeq],int seq_cible[LmaxSeq]);

char * fin() ;

// faudra changer cettes fonctions, une fois on a decide le format d'envoi
int * texteASeqInt(char *txt) ;
const char * resultatATexte(ResultTentative resultat) ;

//Client
const char *introTentative();
const char *ecritureTentative();


