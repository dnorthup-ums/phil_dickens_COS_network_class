#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <netdb.h>
#define IP "127.0.0.1"
#define PORT 8255

struct sockaddr_in sa ;
int main()
        { int err;
          char my_buf[1024] ;
          char *msg = "I am your main socket squeeze" ;

         sprintf(my_buf, "%s", "YO BRO!\n") ;

         int my_sock = socket(AF_INET, SOCK_STREAM, 0) ;
         sa.sin_family   = AF_INET ;
         sa.sin_port     = htons(PORT) ;
         inet_pton(AF_INET,IP , &(sa.sin_addr)) ; //fdill in IP address of client
         printf("BEFORE CONNECT\n") ;
         int x = connect(my_sock, (struct sockaddr *) &sa, sizeof(sa)) ;
         if(x < 0)
		perror("Connet") ;

         printf ("Sending Message to Server!\n") ;
         send (my_sock, my_buf, 32,  0) ;
         printf ("Receiving Message from Server!\n") ;
         int recv_size = recv(my_sock , my_buf , 32 , 0) ;
         printf("Here is the message from server: \n%s\n", my_buf) ;
         }

