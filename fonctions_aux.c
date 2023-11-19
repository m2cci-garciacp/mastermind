#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "fonctions_aux.h"
#include "fon.h"

#define SIZE_MAX_MSG 1024

// Format du strReseau:
// xyyystr
// yyy est la taille du message
// str est le message a envoyer
// x est un code : 0 init partie
//                 1 en jeu
//                 2 partie fini


void sendMessage ( int socket_client , messageCode codeAndMessage )
{
    char strReseau[SIZE_MAX_MSG] = "" ;
    char code[2] ;
    code[0] = codeAndMessage.code + 0x30 ;
    code[1] = 0x0 ;
    char size[4] ;
    sprintf(size, "%03d", strlen(codeAndMessage.msg));

    strcat( strReseau , code ) ;
    strcat( strReseau , size ) ;
    strcat( strReseau , codeAndMessage.msg ) ;

    h_writes ( socket_client , strReseau , strlen(strReseau) ) ;
}

messageCode lireMessage ( int socket_client )
{
    char message[SIZE_MAX_MSG] = "" ;
    char taille[4] ;
    messageCode codeAndMessage ;

    // Lire code du message. On lit un byte, et puis on rajoute manuellement une marque de fin de string.
    h_reads ( socket_client , message , 1 ) ;
    message[1] = 0x0 ;
    codeAndMessage.code = (char) atoi(message) ;
    // Lire taille du message. On lit trois bytes, et puis on rajoute manuellement une marque de fin de string.
    h_reads ( socket_client , taille , 3 ) ;
    // Lire le message.
    h_reads ( socket_client , message , atoi(taille)+1 ) ;  // +1 ou pas???!!!
    codeAndMessage.msg = message ;

     return codeAndMessage ;
}