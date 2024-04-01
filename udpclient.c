#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <netdb.h>
#define IP "127.0.0.1"
#define PORT 8255

struct sockaddr_in sa;
int main()
{
  //int err;
  char my_buf[1024];
  //char *msg = "I am your main socket squeeze";

  snprintf(my_buf, sizeof(my_buf), "%s", "YO BRO!\n");

  int my_sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (my_sock==-1)
  {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }
  
  sa.sin_family = AF_INET;
  sa.sin_port = htons(PORT);
  inet_pton(AF_INET, IP, &(sa.sin_addr)); // fill in IP address of client
  printf("BEFORE CONNECT\n");
  int x = connect(my_sock, (struct sockaddr *)&sa, sizeof(sa));
  if (x < 0)
  {
    perror("Connect");
    close(my_sock);
    exit(EXIT_FAILURE);
  }
  printf("Sending Message to Server!\n");
  int sent = sendto(my_sock, my_buf, 32, 0, (struct sockaddr *)NULL, sizeof(sa));
  if (sent < 0)
  {
    perror("Error sending message");
    close(my_sock);
    exit(EXIT_FAILURE);
  }
  
  printf("Receiving Message from Server!\n");
  int recv_size = recvfrom(my_sock, my_buf, 32, 0, (struct sockaddr *)NULL, NULL);
  if (recv_size==-1)
  {
    perror("Error receiving reply");
    close(my_sock);
    exit(EXIT_FAILURE);
  }
  
  printf("Here is the message from server: \n%s\n", my_buf);
  close(my_sock);
  exit(EXIT_SUCCESS);
}
