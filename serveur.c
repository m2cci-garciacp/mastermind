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

#include<sys/signal.h>
#include<sys/wait.h>
#include<stdlib.h>

#include "fon.h"     		/* Primitives de la boite a outils */

#define SERVICE_DEFAUT "1111"
#define READ_SIZE 1000

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
	char msg [READ_SIZE] ;
	int result_read ;
	int pid ; 
	
	// commun
	socket_id = h_socket ( AF_INET , SOCK_STREAM ) ;             // int h_socket ( int domaine, int mode );
	adr_socket( service, NULL , SOCK_STREAM , &p_adr_socket);    // void adr_socket( char *service, char *serveur, int typesock, struct sockaddr_in **p_adr_serv);
	h_bind( socket_id , p_adr_socket ) ;                         // void h_bind ( int num_soc, struct sockaddr_in *p_adr_socket );


	h_listen ( socket_id, nb_req_att ) ;
	// Serveur iteratif                         // void h_listen ( int num_soc, int nb_req_att );
	while (true) {
		socket_client = h_accept ( socket_id , &p_adr_client ) ; // int h_accept( int num_soc, struct sockaddr_in *p_adr_client );
		printf ("socket: %d\tclient en: %d\n", socket_id , socket_client ) ;
		answer = h_reads ( socket_client , msg , READ_SIZE );           // int h_reads ( int num_soc, char *tampon, int nb_octets );
		h_close ( socket_client ) ;                              // void h_close ( int socket ); 
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
