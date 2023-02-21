#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    if (s < 0) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server, client;
    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));
    server.sin_port = htons(5555);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Bind error");
        exit(EXIT_FAILURE);
    }

    socklen_t l = sizeof(client);
    while (1) {    
        char request;
        recvfrom(s, &request, sizeof(request), MSG_WAITALL, (struct sockaddr *) &client, &l);
        
        //sleep(5);

        int t = time(NULL);
        t = htonl(t);
        sendto(s, &t, sizeof(t), 0, (struct sockaddr *) &client, sizeof(client));
    }

    close(s);
}
