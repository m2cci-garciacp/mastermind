
#define L 4

typedef struct {
    int nbCorrect; int nbMalPlaces; int trouve;
} ResultTentative;

void initialisation(int combinaisonSecrete[L]) ;
char * printRegles() ;
ResultTentative tentative(int Seq[L]) ;
int * texteASeqInt(char *txt) ;
char * resultatATexte(ResultTentative resultat) ;
char * fin() ;


