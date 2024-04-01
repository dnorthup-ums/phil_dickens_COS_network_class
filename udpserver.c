#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#define IP "127.0.0.1"
#define PORT 8255

int send_size, recv_size;
int main(int argc, char *argv[])
{
    int socket_fd, client_sock, recv_size;
    //socklen_t c;
    struct sockaddr_in server, client, my_addr;
    char client_message[20000];
    socklen_t client_addr_len = sizeof(client);

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    //client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("Socket Error");
    }
    
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &(server.sin_addr)); // fill in server ip address
    if (bind(socket_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        close(socket_fd);
        return 1;
    }
    printf("Socket is bound! Waiting for dgrams!\n");

    recv_size = recvfrom(socket_fd, client_message, 32, 0, (struct sockaddr *) &client, &client_addr_len);
    if (recv_size <= 0)
    {
        perror("Receive Failed");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Got this from Client:\n %s\n", client_message);
    //snprintf(client_message, sizeof(client_message), "How Now MONJO1! Yo.\n");
    send_size = sendto(socket_fd, client_message, strlen(client_message), 0, (struct sockaddr *) &client, client_addr_len);
    if (send_size <= 0)
    {
        perror("Send Failed");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    close(socket_fd);
    return 0;
}
