
#define L 4

typedef struct {
    int nbCorrect; int nbMalPlaces; int trouve;
} ResultTentative;

void initialisation(int combinaisonSecrete[L]) ;
char * printRegles() ;
ResultTentative tentative(int Seq[L]) ;
char * fin() ;
// faudra changer cettes fonctions, une fois on a decide le format d'envoi
int * texteASeqInt(char *txt) ;
char * resultatATexte(ResultTentative resultat) ;


