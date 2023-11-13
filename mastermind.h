
#define L 5

typedef struct {
    int nbCorrect; int nbMalPlaces; int trouve;
} ResultTentative;

void initialisation( &combinationSecrete ) ;
char * printRegles() ;
ResultTentative tentative(int Seq[L]) ;
int Seq[L] texteASeqInt(char *txt) ;
char * resultatATexte(ResultTentative resultat) ;
char * fin() ;


