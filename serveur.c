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
void partie1Joueur ( int socket_client ) ;



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
			partie1Joueur ( socket_id ) ;
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


void partie1Joueur ( int socket_client ) 

/*  C'est la function main du jeu coté serveur. */

{
	int combinationSecrete[N_COLORS];
	int playing = 1 ;
	messageCode codeAndMessage ; 
	ResultTentative resultatTentative ;


	// Initialiser le jeu: calculer la combinaison secrete et envoyer les régles
	// au client.
	initialisation ( combinationSecrete ) ;
	codeAndMessage.code = 0 ;            // initialisation de la partie
	codeAndMessage.msg = printRegles() ; // message a transmettre
	sendMessage ( socket_client , codeAndMessage ) ;

	// On a explique les régles, ici on joue.
	while ( playing ) 
	{
		
		codeAndMessage = lireMessage ( socket_client ) ;
		resultatTentative = tentative( texteASeqInt( codeAndMessage.msg ),combinationSecrete );

		
		if ( resultatTentative.trouve ) 
		{   
			//  si trouve on arrete de jouer
			playing = 0 ;                                              // on arrete de jouer
			
			codeAndMessage.code = 2 ;                                  // je reparle
			codeAndMessage.msg = resultatATexte( resultatTentative ) ; // message a transmettre
			sendMessage ( socket_client , codeAndMessage ) ;
			
			codeAndMessage.code = 3 ;                                  // finalisation de la partie
			codeAndMessage.msg = finPartie () ;                        // message a transmettre
			sendMessage ( socket_client , codeAndMessage ) ;

			break ;
		} 
		else 
		{   
			//  si on a pas trouve on continue a jouer
			codeAndMessage.code = 1 ;                                  // continuer la partie: je t'ecoute
			codeAndMessage.msg = resultatATexte( resultatTentative ) ; // message a transmettre

		}		
	}
}
