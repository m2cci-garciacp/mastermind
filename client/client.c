/******************************************************************************/
/*			Application: ...					*/
/******************************************************************************/
/*									      */
/*			 programme  CLIENT				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs : ... 					*/
/*									      */
/******************************************************************************/	


#include <stdio.h>
#include <curses.h> 		        /* Primitives de gestion d'ecran */
#include <sys/signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "./../connexion/fon.h"   		            /* primitives de la boite a outils */
#include "./../connexion/fonctions_aux.h"   		/* fonctions auxiliaires de connexion */
#include "mastermindClient.h"     	/* fonctions mastermind cote client */
#include "./../outils/verificationInput.h"   	    /* verification Input */
#include "./../outils/outils.h"             	    /* outils de conversion */

#define SERVICE_DEFAUT "1111"
#define SERVEUR_DEFAUT "127.0.0.1"

void client_appli ( char *serveur, char *service ) ;
void partieEnCours ( int socket ) ;


/*****************************************************************************/
/*--------------- programme client -----------------------*/

int main(int argc, char *argv[])
{

	char *serveur= SERVEUR_DEFAUT; /* serveur par defaut */
	char *service= SERVICE_DEFAUT; /* numero de service par defaut (no de port) */


	/* Permet de passer un nombre de parametre variable a l'executable */
	switch(argc)
	{
 	case 1 :		/* arguments par defaut */
		  printf("serveur par defaut: %s\n",serveur);
		  printf("service par defaut: %s\n",service);
		  break;
  	case 2 :		/* serveur renseigne  */
		  serveur=argv[1];
		  printf("service par defaut: %s\n",service);
		  break;
  	case 3 :		/* serveur, service renseignes */
		  serveur=argv[1];
		  service=argv[2];
		  break;
    default:
		  printf("Usage:client serveur(nom ou @IP)  service (nom ou port) \n");
		  exit(1);
	}

	/* serveur est le nom (ou l'adresse IP) auquel le client va acceder */
	/* service le numero de port sur le serveur correspondant au  */
	/* service desire par le client */
	
	client_appli(serveur,service);
}

/*****************************************************************************/
void client_appli (char *serveur, char *service)

/* procedure correspondant au traitement du client de votre application */

{
	struct sockaddr_in *pAdrServeur ;
	int socketId ;

	// init socket
	socketId = h_socket ( AF_INET , SOCK_STREAM ) ;

	// Configuration pour la connexion du serveur
	adr_socket( service, serveur , SOCK_STREAM , &pAdrServeur);

	// Connect the serveur
	h_connect( socketId, pAdrServeur );

	// Initier partie
	partieEnCours ( socketId ) ;

	// Fermer connexion
	h_close ( socketId ) ;	

 }

/*****************************************************************************/

void partieEnCours ( int socket )
/*
	C'est la fonction principal d'un jeu de MasterMind. Elle presente les regles, demande la difficulte
	communique avec le serveur a chaque tour et imprime les reponses au joueur..

	Input:
		int socket : 
		 		socket de la connexion avec le serveur. La connexion est deja etablie.
	Output:
		void
*/
{
	char message[2000] ;         // String tampon pour les messages
	int nvDiff;                  // Niveau de difficulté
	int sequence[4];             // Tableau contenant la sequence de la combination du joueur: taille L
	int L=0;                     // Taille de la sequence de la combination du joeueur.

	
	// Presenter les regles du jeu
	imprimerRegles();

	// Demander la difficulte: nombre coleurs
	nvDiff = demanderDifficulte() ;
	seqIntToStr(&nvDiff, 1, message) ;
	sendMessage ( socket , message ) ;

	// Boucle principal: L depend de la reponse du serveur.
	// Elle vaut normalement 2 sauf quand la partie est fini, qui vaut 4.
	// Normalement, la Sequence de retour inclu le nombre de bien places en Sequence[0],
	// et le nombre de mal places en Sequence [1]. Seulement quand la partie est finie,
	// la Sequence inclu le nbTours et le Score en Sequence[2] et Sequence[3] respectivement.
	while( L!=4 )
	{ 
		// Lire la sequence du joueur (verification d'input)
		ecritureTentative(sequence, &L, nvDiff) ;
		// Convertir la sequence en message
		seqIntToStr( sequence , L, message) ;
		// Envoyer la sequence au serveur
		sendMessage ( socket , message ) ;

		// Recevoir reponse du serveur
		lireMessage ( socket , message) ;
		// Reponse str a reponse en SeqInt
		strToSeqInt( message, sequence, &L) ;
		// Faire le retour: sequence[0] sont les bien places et sequence[1] sont les mal places
		faireRetour(sequence[0], sequence[1]) ;
		
	}
	// Informer du score.
	donnerPoints(sequence[2], sequence[3]) ;
}
