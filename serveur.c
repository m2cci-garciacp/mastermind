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

#include "fon.h"     		    /* Primitives de la boite a outils */
#include "mastermind.h"     	/* Fontions du jeu */
#include "fonctions_aux.h"     	/* Fontions aux. de connexion mais specifiques au jeu */     	

#define SERVICE_DEFAUT "1111"
#define READ_SIZE 1000
#define N_COLORS 4


void serveur_appli (char *service);   /* programme serveur */
void partieMasterMind ( int socket_client ) ;



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
	
	serveur_appli(service);
}


/******************************************************************************/	
void serveur_appli(char *service)

/* Procedure correspondant au traitemnt du serveur de votre application */

{
	struct sockaddr_in *p_adr_socket, p_adr_client ;
	int socket_id, socket_client ;
	unsigned int nb_req_att = 100 ;
	int pid ; 
	
	// Ouverture du socket et bind du serveur
	socket_id = h_socket ( AF_INET , SOCK_STREAM ) ;
	adr_socket( service, NULL , SOCK_STREAM , &p_adr_socket);
	h_bind( socket_id , p_adr_socket ) ;

	// On ecoute pour des connexions entrantes
	h_listen ( socket_id, nb_req_att ) ;
	while (true) 
	{
		// Des qu'un client essaie de se connecter, on l'accepte
		socket_client = h_accept ( socket_id , &p_adr_client ) ;
		// La connexion est etablie. Maintenant on "clone" le processus avec fork
		pid = fork () ;
		if (pid == 0 )
		{
	   		// Processus fils : on commence la partie. Une fois la partie finie, on
			// ferme la connexion de chaque coté et on fini le processus fils.
			h_close ( socket_id ) ; 
			partieMasterMind ( socket_client ) ;
			h_close ( socket_client ) ; 
    		exit ( 0 ) ; 
		} 
		else 
		{
	   		// Processus père : on ferme la connexion unilateralement (la connexion
			// est toujours ouverte dans le processus fils).
			h_close ( socket_client ) ; 
		}		
	}	

	// Fermer le socket du serveur. En faite, on va jamais attendre ce ligne de code 
	// car on est dans une boucle infinit.
	h_close ( socket_id ) ;
	
}

/******************************************************************************/	


void partieMasterMind ( int socket_client ) 
/* Cette fonction est le corps principal d'une partie MasterMind. Elle initialise la combination secrete,
   communique avec le client et avec le jeu pendant la partie.

    Input: 
        int socket :
                socket de la connexion avec le client. La connexion est deja etablie.
*/
{
	int combinationSecrete[N_COLORS];
	int *combinationJoueur;
	int playing = 1 ;
	char strTampon[200] ;
	messageCode codeAndMessage ; 
	ResultTentative resultat ;
	int nv_diff ;
	resultat.trouve = 0 ; // continuons a jouer


	// Initialiser le jeu: calculer la combinaison secrete et envoyer les régles
	// au client.

	codeAndMessage.code = 0 ;                                                                  // initialisation de la partie
	strcpy( strTampon , printRegles() ) ;                                             // message des Regles a transmettre
	codeAndMessage.msg = strTampon ;
	sendMessage ( socket_client , codeAndMessage ) ;

	// Demander la difficulte
	codeAndMessage.code = 2 ;
	codeAndMessage.msg = "\n\nAvec combien couleurs voulez-vous jouer? [5-7]: " ;
	sendMessage ( socket_client , codeAndMessage ) ;
	codeAndMessage = lireMessage ( socket_client ) ;
	// initialiser
	nv_diff = initialisation ( combinationSecrete , codeAndMessage.msg ) ;

	// On a explique les régles, ici on joue.
	while ( ! resultat.trouve ) 
	{
		// Proposition du client
		codeAndMessage.code = 1 ;                                                                  // message de intro de sequence
		strcpy( strTampon , introTentative(nv_diff) ) ;
		codeAndMessage.msg = strTampon ;

		sendMessage ( socket_client , codeAndMessage ) ;

		codeAndMessage = lireMessage ( socket_client ) ;                                           // recevoir sequence

		strcpy( strTampon, codeAndMessage.msg);

		combinationJoueur = texteASeqInt( strTampon ) ;
        //memset(strTampon, 0, sizeof(strTampon));
		for (int i=0; i<N_COLORS; i++) {printf("\t%d", combinationJoueur[i]);}
		resultat = tentative( combinationJoueur , combinationSecrete );

		// Repondre a la proposition du joueur
		codeAndMessage.code = 1 + resultat.trouve ;                                  // si la partie continue: je t'ecoute, sinon je reparle
		strcpy ( strTampon , resultatATexte( resultat ) ) ;                            // message a transmettre
		codeAndMessage.msg = strTampon ;
        //memset(strTampon, 0, sizeof(strTampon));

		sendMessage ( socket_client , codeAndMessage ) ;
		
		memset(strTampon, 0, sizeof(strTampon));
		codeAndMessage.msg = "";

	}

	//  Finaliser la partie
	codeAndMessage.code = 3 ;                                                        
	codeAndMessage.msg = fin () ;                                                    // message de fin a transmettre
	sendMessage ( socket_client , codeAndMessage ) ;

}
