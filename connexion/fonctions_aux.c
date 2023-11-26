#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "fon.h"                  /* Fonctions de connexion */
#include "fonctions_aux.h"        /* Fonctions auxiliares de connexion */

#define SIZE_MAX_MSG 1024


// Format du strReseau:
// yystr
// yy est la longeur de la string
// str est le message


void sendMessage ( int socket , char str[] )
/* Cette fonction envoie un message dans la socket en regardant sa taille avant de l'envoyer. 
Le message a envoyer possède un entier indiquant sa taille et un message texte. Le message envoyé 
sera dans le format:
    - 2 bytes du début servant à indiquer la taille du message à recevoir
    - le message à recevoir de taille variable
   Ce format permettra de pouvoir lire la taille exacte du nombre d'octets qui cherche à être envoyé pour permettre par la suite la lecture du messages 
   sans perte d'information.

    Input: 
        int socket :
                socket à lire. Il doit y avoir la connexion deja d'établie. 
        char str[] :
                message a envoyer. 
    Output:
        void
*/
{
    char strReseau[SIZE_MAX_MSG] = "" ;
    char size[3] ;
    sprintf(size, "%02ld", strlen(str) );

    strcpy( strReseau , size ) ;
    strcat( strReseau , str ) ;
    strcat( strReseau , "" ) ;

    h_writes ( socket , strReseau , strlen(strReseau) ) ;
}

void lireMessage ( int socket , char * str)
/* Cette fonction attend jusqu'à ce qu'un message arrive dans la socket et le lit.
   Ce message suit le format au début du fichier:
    - 2 bytes pour la taille du message a recevoir
    - + le message à recevoir qui est de taille variable
   Ce format permet de lire au préalable la taille exacte du message que l'on souhaite lire.

    Input: 
        int socket :
                socket à lire. Il doit y avoir la connexion deja d'établie. 
        char * str :
                Pointeur vers l'adresse où on va ecrire le message. 
    Output:
        void
*/
{
    char taille[3] ;

    
    // Lire taille du message. On lit trois bytes, et puis on rajoute manuellement une marque de fin de string.
    h_reads ( socket , taille , 2 ) ;
    taille[2] = 0 ;

    // Lire le message.
    h_reads ( socket , str , atoi(taille) ) ;  // +1 ou pas???!!! -1...
    str[atoi(taille)] = 0 ;
}
