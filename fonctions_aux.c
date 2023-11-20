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
//                 1 en jeu: je t'ecoute
//                 2 en jeu: je reparle
//                 3 partie fini


void sendMessage ( int socket , messageCode codeEtMessage )
/* Cette fonction envoi un message dans le socket. Le message a envoyer compte avec un
   code et un msg text. Le message envoyé sera dans le format au début du fichier:
    - 1 octet pour un code
    - 3 pour la taille du message a recevoir
    - le message a recevoir de taille variable
   Ce format permet de lire la taille exacte de octets.

    Input: 
        int socket :
                socket à lire. Il doit avoir la connexion deja etablie. 
    Output:
        messageCode codeEtMessage :
                structure messageCode = {char code; char * msg}
                ceci contient le code transmit, en fonction de l'état du jeu
                           et le mmsg transmit, en format string.
*/
{
    char strReseau[SIZE_MAX_MSG] = "" ;
    char code[2] ;
    code[0] = codeEtMessage.code + 0x30 ;
    code[1] = 0x0 ;
    char size[4] ;
    sprintf(size, "%03d", strlen(codeEtMessage.msg));

    strcat( strReseau , code ) ;
    strcat( strReseau , size ) ;
    strcat( strReseau , codeEtMessage.msg ) ;

    h_writes ( socket , strReseau , strlen(strReseau) ) ;
}

messageCode lireMessage ( int socket )
/* Cette fonction attendre jusqu'a un message arrive dans le socket et le lit.
   Ce message suit le format au début du fichier:
    - 1 octet pour un code
    - 3 pour la taille du message a recevoir
    - le message a recevoir de taille variable
   Ce format permet de lire la taille exacte de octets.

    Input: 
        int socket :
                socket à lire. Il doit avoir la connexion deja etablie. 
    Output:
        messageCode codeEtMessage :
                structure messageCode = {char code; char * msg}
                ceci contient le code transmit, en fonction de l'état du jeu
                           et le mmsg transmit, en format string.
*/
{
    char message[SIZE_MAX_MSG] = "" ;
    char taille[4] ;
    messageCode codeEtMessage ;

    // Lire code du message. On lit un byte, et puis on rajoute manuellement une marque de fin de string.
    h_reads ( socket , message , 1 ) ;
    message[1] = 0x0 ;
    codeEtMessage.code = (char) atoi(message) ;
    // Lire taille du message. On lit trois bytes, et puis on rajoute manuellement une marque de fin de string.
    h_reads ( socket , taille , 3 ) ;
    // Lire le message.
    h_reads ( socket , message , atoi(taille)+1 ) ;  // +1 ou pas???!!!
    codeEtMessage.msg = message ;

     return codeEtMessage ;
}


// TODO: tester fonctions aux

