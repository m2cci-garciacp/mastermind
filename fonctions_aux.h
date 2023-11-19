

typedef struct {char   code ;
                char*  msg ;
                } messageCode ;

void sendMessage ( int socket_client , messageCode codeAndMessage ) ;
messageCode lireMessage ( int socket_client ) ;