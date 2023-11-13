
typedef struct {
    int nbCorrect; int nbMalPlaces; int Trouve;
}ResultTentative;
#define L 5

void initialisation();
char * getRules();
ResultTentative tentative(int Seq[L]);
char * fin();


