#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "fonctions_aux.h"
#include "fon.h"

#define SIZE_MAX_MSG 1024


// Format du strReseau:
// yystr
// yy est la longeur du string
// str est le message


void sendMessage ( int socket , char str[] )
/* Cette fonction envoi un message dans le socket. Le message a envoyer compte avec un
   code et un msg text. Le message envoyé sera dans le format au début du fichier:
    - 2 pour la taille du message a recevoir
    - le message a recevoir de taille variable
   Ce format permet de lire la taille exacte de octets.

    Input: 
        int socket :
                socket à lire. La connexion est deja etablie. 
        char str[] :
                message a envoyer. 
    Output:
        void
*/
{
    char strReseau[SIZE_MAX_MSG] = "" ;
    char size[3] ;
    sprintf(size, "%02ld", strlen(str) );

    strcat( strReseau , size ) ;
    strcat( strReseau , str ) ;
    strcat( strReseau , "" ) ;

    h_writes ( socket , strReseau , strlen(strReseau) ) ;
}

void lireMessage ( int socket , char * str)
/* Cette fonction attendre jusqu'a un message arrive dans le socket et le lit.
   Ce message suit le format au début du fichier:
    - 2 pour la taille du message a recevoir
    - le message a recevoir de taille variable
   Ce format permet de lire la taille exacte de octets.

    Input: 
        int socket :
                socket à lire. Il doit avoir la connexion deja etablie. 
        char * str :
                Pointeur ou on va ecrire le message. 
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
