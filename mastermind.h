#define LmaxSeq 4

typedef struct {
    int nbCorrect; int nbMalPlaces; int trouve;
} ResultTentative;

void initialisation(int combinaisonSecrete[LmaxSeq]) ;
char * printRegles() ;

ResultTentative  tentative(int seq[LmaxSeq],int seq_cible[LmaxSeq]);

char * finPartie() ;

// faudra changer cettes fonctions, une fois on a decide le format d'envoi
int * texteASeqInt(char *txt) ;
char * resultatATexte(ResultTentative resultat) ;

//Client
char *ecritureTentative();


