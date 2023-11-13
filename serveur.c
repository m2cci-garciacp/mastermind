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

#include "fon.h"     		/* Primitives de la boite a outils */
#include "mastermind.h"     	

#define SERVICE_DEFAUT "1111"
#define READ_SIZE 100
#define N_COLORS 4

void serveur_appli (char *service);   /* programme serveur */



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
	unsigned int nb_req_att;
	char msg_in [READ_SIZE] ;
	char msg_out [READ_SIZE] ;
	int result_read ;
	int pid ; 

	int combinationSecrete[N_COLORS];
	int playing = 1 ;
	ResultTentative result_tentative ;
	
	// commun
	socket_id = h_socket ( AF_INET , SOCK_STREAM ) ;
	adr_socket( service, NULL , SOCK_STREAM , &p_adr_socket);
	h_bind( socket_id , p_adr_socket ) ;


	h_listen ( socket_id, nb_req_att ) ;
	// Serveur iteratif
	while (true) {
		socket_client = h_accept ( socket_id , &p_adr_client ) ;
		// connexion etablie
		playing = 1 ;
		initialisation ( combinationSecrete ) ;
		strcpy( msg_out , printRegles() );
		h_writes ( socket_client , msg_out , sizeof(msg_out) ) ;
		// on commence a jouer
		while ( playing ) {
			strcpy( msg_in , "" ) ;
			strcpy( msg_out , "" ) ;
			result_read = h_reads ( socket_client , msg_in , READ_SIZE );   // ceci possera de problemes car il lit jusque atteint le READ_SIZE
			 
			result_tentative = tentative ( texteASeqInt( msg_in ) ) ;
			//  si reussi -> fin
			if ( result_tentative.trouve ) {
				playing = 0 ;
				strcpy( msg_out , fin () ) ;
			} else {
				strcpy ( msg_out , resultatATexte( result_tentative ) ) ; // convertir result_tentative a bonne format str pour client
			}			
			h_writes ( socket_client , msg_out , strlen(msg_out) );
		}
	}
	// // Serveur : parallele
	// while (true) {
	// 	socket_client = h_accept ( socket_id , p_p_adr_client ) ; // int h_accept( int num_soc, struct sockaddr_in *p_adr_client );
	//    	pid = fork ()
	//    	if (pid == 0 ) {
	//    		// fils
	//    		h_close( socket_id ) ;
	//    		answer = h_reads ( socket_client , msg , 100 );       // int h_reads ( int num_soc, char *tampon, int nb_octets );
	//    		h_close ( socket_client ) ; 
    // 		exit ( 0 ) ; 
	//    	} else {
	//    		// pere
	//   		h_close ( socket_client ) ;                          // void h_close ( int socket ); 
	//   	}                 
	// }

	

	// commun
	h_close ( socket_id ) ;                                      // void h_close ( int socket );
	
}

/******************************************************************************/	
