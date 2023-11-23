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

#include "fon.h"   		            /* primitives de la boite a outils */
#include "fonctions_aux.h"   		/* fonctions auxiliaires de connexion */
#include "mastermind.h"   		    /* fonctions mastermind */
#include "verificationInput.h"   	/* verification Input */

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
void client_appli (char *serveur,char *service)

/* procedure correspondant au traitement du client de votre application */

{
	struct sockaddr_in *p_adr_socket, *p_adr_serveur ;
	int socket_id, socket_serveur ;
	//unsigned int nb_req_att;
	char msg_out [200] ;
	char msg_in [200]="" ;
	int answer ; 

	// commun
	socket_id = h_socket ( AF_INET , SOCK_STREAM ) ;          // int h_socket ( int domaine, int mode );

	adr_socket( service, serveur , SOCK_STREAM , &p_adr_serveur); // void adr_socket( char *service, char *serveur, int typesock, struct sockaddr_in **p_adr_serv);
	h_connect( socket_id, p_adr_serveur );

	partieEnCours ( socket_id ) ;

	// commun
	h_close ( socket_id ) ;
	

 }

/*****************************************************************************/

void partieEnCours ( int socket ) 
{
	messageCode codeAndMessage ;
	char strTampon[2000] = "a";
	int nv_diff;

	// attendre pour l'initialisation
	codeAndMessage = lireMessage ( socket ) ;
	if (codeAndMessage.code == 0) {
		// regles
		printf("%s", codeAndMessage.msg);
	}

	// demander la difficulte
	codeAndMessage = lireMessage ( socket ) ;
	while (!digitsOnly(strTampon)) {
		printf("%s", codeAndMessage.msg);
		scanf("%s", strTampon );
	}
	sprintf( strTampon , "%d", intoRange(strTampon, 4, 7) ) ;
	nv_diff = atoi(strTampon) ;
	
	
	codeAndMessage.code = 2 ;
	codeAndMessage.msg = strTampon ;
	sendMessage ( socket , codeAndMessage ) ;



	printf("client: to loop\n");
	while(codeAndMessage.code != 3)
	{ 
		// Lire la proposition du joueur
		codeAndMessage = lireMessage ( socket ) ;
		//printf("%s", codeAndMessage.msg) ;
		ecritureTentative(strTampon, codeAndMessage.msg, nv_diff) ;
		codeAndMessage.msg = strTampon ;
		//printf("Sequence : %s\n", codeAndMessage.msg) ;
		codeAndMessage.code = 1 ;                    // tour a lautre de parler
		sendMessage ( socket , codeAndMessage ) ;

		// Repondre a la proposition du joueur
		codeAndMessage = lireMessage ( socket ) ;
		printf("code: %d %s", codeAndMessage.code, codeAndMessage.msg);
		// Verifier s'il y a quelque chose encore a dire: fin
		while (codeAndMessage.code == 2)
		{	
			codeAndMessage = lireMessage ( socket ) ;
			printf("%s", codeAndMessage.msg);
		}

		memset(strTampon, 0, sizeof(strTampon));
		codeAndMessage.msg = "";
	}


}
