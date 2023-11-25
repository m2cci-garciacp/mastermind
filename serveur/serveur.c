/******************************************************************************/
/*			Application: ....			              */
/******************************************************************************/
/*									      */
/*			 programme  SERVEUR 				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs :  ....						      */
/*		Date :  ....						      */
/*									      */
/******************************************************************************/	

#include<stdio.h>
#include <curses.h>
#include <string.h>

#include<sys/signal.h>
#include<sys/wait.h>
#include<stdlib.h>

#include "./../connexion/fon.h"     		        /* Primitives de la boite a outils */
#include "./../connexion/fonctions_aux.h"        	/* Fontions aux. de connexion mais specifiques au jeu */
#include "mastermindServeur.h"                  	/* Fontions du jeu */   
#include "./../outils/outils.h"     	            /* Fontions aux. de connexion mais specifiques au jeu */     	

#define SERVICE_DEFAUT "1111"
#define READ_SIZE 1000
#define N_COLORS 4


void serveurAppli (char *service);   /* programme serveur */
void partieMasterMind ( int socketClient ) ;



/******************************************************************************/	
/*---------------- programme serveur ------------------------------*/

int main(int argc,char *argv[])
{

	char *service= SERVICE_DEFAUT; /* numero de service par defaut */


	/* Permet de passer un nombre de parametre variable a l'executable */
	switch (argc)
 	{
   	case 1:
		  printf("defaut service = %s\n", service);
		  		  break;
 	case 2:
		  service=argv[1];
            break;

   	default :
		  printf("Usage:serveur service (nom ou port) \n");
		  exit(1);
 	}

	/* service est le service (ou numero de port) auquel sera affecte
	ce serveur*/
	
	serveurAppli(service);
}


/******************************************************************************/	
void serveurAppli(char *service)

/* Procedure correspondant au traitemnt du serveur de votre application */

{
	struct sockaddr_in *pAdrSocket, pAdrClient ;
	int socketId, socketClient ;
	unsigned int nbReqAtt = 100 ;
	int pid ; 
	
	// Ouverture du socket et bind du serveur
	socketId = h_socket ( AF_INET , SOCK_STREAM ) ;
	adr_socket( service, NULL , SOCK_STREAM , &pAdrSocket);
	h_bind( socketId , pAdrSocket ) ;

	// On ecoute pour des connexions entrantes
	h_listen ( socketId, nbReqAtt ) ;
	while (true) 
	{
		// Des qu'un client essaie de se connecter, on l'accepte
		socketClient = h_accept ( socketId , &pAdrClient ) ;

		// La connexion est etablie. Maintenant on "clone" le processus avec fork
		pid = fork () ;
		if (pid == 0 )
		{
	   		// Processus fils : on ferme le socket serveur d'ecoute et on commence la partie. 
			// Une fois la partie finie, on ferme la connexion de chaque coté et on fini le processus fils.
			h_close ( socketId ) ; 
			partieMasterMind ( socketClient ) ;
			h_close ( socketClient ) ; 
    		exit ( 0 ) ; 
		} 
		else 
		{
	   		// Processus père : on ferme la connexion client unilateralement (la connexion
			// est toujours ouverte dans le processus fils).
			h_close ( socketClient ) ; 
		}		
	}	

	// Fermer le socket du serveur. En faite, on va jamais attendre ce ligne de code 
	// car on est dans une boucle infinit.
	h_close ( socketId ) ;
	
}

/******************************************************************************/	


void partieMasterMind ( int socketClient ) 
/* 
	Cette fonction est le corps principal d'une partie MasterMind. Elle initialise la combination 
	secrete, communique avec le client et avec le jeu pendant la partie.

    Input: 
        int socket :
                socket de la connexion avec le client. La connexion est deja etablie.
*/
{
	int combinationSecrete[N_COLORS+1];     // Combinaison secrete.
	int combinationJoueur[N_COLORS+1];      // Combinaison du joueur.
	int reponse[N_COLORS+1];                // Reponse au joueur: sequence de taille L.
	int L=0 ;                               // Taille de la reponse au joueur: taille L de reponse.
	char message[200];                      // String utilise pour toute communication.
	int nvDiff ;                            // Niveau de difficulte.
	int nbTours = 0 ;                       // Nombre de tours.

	// Recevoir difficulté du jeu : nombre de couleurs
	lireMessage ( socketClient , message) ;
	strToSeqInt( message , &nvDiff, &L) ;
	// Initialiser la combination secrete
	initialisation ( combinationSecrete , nvDiff ) ;

	// Boucle principal: L depend de la combinaison du joueur par rapport la combinaison secrete.
	// Elle vaut normalement 2 sauf quand la partie est fini, qui vaut 4.
	// Normalement, la Sequence de retour inclu le nombre de bien places en Sequence[0],
	// et le nombre de mal places en Sequence [1]. Seulement quand la partie est finie,
	// la Sequence inclu le nbTours et le Score en Sequence[2] et Sequence[3] respectivement.
	while ( L!=4 ) 
	{	
		// Nombre de tours.
		nbTours ++;
		// Recevoir la combinaison du joueur
		lireMessage ( socketClient , message ) ;
		strToSeqInt( message , combinationJoueur, &L) ;
		// Comparer la combinaison du joueur avec la combination secrete
		tentative(combinationJoueur, combinationSecrete, reponse, &L, nbTours);
		// Repondre au joueur les couleurs bien et mal places, et eventuellement le nombre de tours et le score.
		seqIntToStr ( reponse , L , message ) ;
		sendMessage ( socketClient , message ) ;
	}

}
