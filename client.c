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
#include <curses.h> 		/* Primitives de gestion d'ecran */
#include <sys/signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "fon.h"   		/* primitives de la boite a outils */

#define SERVICE_DEFAUT "1111"
#define SERVEUR_DEFAUT "127.0.0.1"

void client_appli (char *serveur, char *service);


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
	char msg_in [11] ;
	char msg_out [11]="0123456789" ;
	int answer ; 
	
	// commun
	socket_id = h_socket ( AF_INET , SOCK_STREAM ) ;          // int h_socket ( int domaine, int mode );
	adr_socket( service+1, NULL , SOCK_STREAM , &p_adr_socket); // void adr_socket( char *service, char *serveur, int typesock, struct sockaddr_in **p_adr_serv);
	// comme on est dans la meme machine, le port doit etre different.
	// quand tu essaiyais, le serveur deja tournait sur le port, donc le client pouvait pas occuper le meme
	h_bind( socket_id , p_adr_socket ) ;                      // void h_bind ( int num_soc, struct sockaddr_in *p_adr_socket );
	
	//client : on refait la meme chose pour le serveur
	adr_socket( service, serveur , SOCK_STREAM , &p_adr_serveur); // void adr_socket( char *service, char *serveur, int typesock, struct sockaddr_in **p_adr_serv);
	h_connect( socket_id, p_adr_serveur );

	printf ("Client va dire : %s\n", msg_out);
	h_writes ( socket_id , msg_out, 10 );

	h_reads( socket_id , msg_in, 10 );
	printf ("Serveur dit : %s\n", msg_in);
	
	// commun
	h_close ( socket_id ) ;
	

 }

/*****************************************************************************/

