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
#include "mastermindClient.h"   	/* fonctions mastermind cote client */
#include "verificationInput.h"   	/* verification Input */
#include "outils.h"             	/* outils de conversion */

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
	char message[2000] ;
	char strTampon[2000] = "a";
	int nv_diff;
	int L;
	int sequence[4];

	// regles
	imprimerRegles();

	// demander la difficulte
	nv_diff = demanderDifficulte() ;
	seqIntToStr(&nv_diff, 1, message) ;
	sendMessage ( socket , message ) ;

	while( L!=4 )
	{ 
		// Lire la sequence du joueur
		ecritureTentative(sequence, &L, nv_diff) ;
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
	// On sort de la boucle quand la sequence de retour est plus longue que de normal : 4
	// parce qu'on inclu le nombre de tours dans sequence[2] et le score en sequence[3]
	donnerPoints(sequence[2], sequence[3]) ;
}
