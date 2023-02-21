#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Invalid syntax!\n");
        printf(" Usage: %s IP_DEST PORT_DEST\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int c = socket(AF_INET, SOCK_DGRAM, 0);
    if (c < 0) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(atoi(argv[2]));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    socklen_t l = sizeof(server);

    char name[50];
    printf("Give a computer name: ");
    fgets(name, 50, stdin);
    name[strlen(name) - 1] = '\0';

    uint16_t len = strlen(name);
    len = htons(len);
    sendto(c, &len, sizeof(len), 0, (struct sockaddr *) &server, sizeof(server));
    sendto(c, name, strlen(name) + 1, 0, (struct sockaddr *) &server, sizeof(server));

    uint16_t flag;
    recvfrom(c, &flag, sizeof(flag), MSG_WAITALL, (struct sockaddr *) &server, &l);

    int ip_addr;
    switch(ntohs(flag)) {
        case 404:
            printf("There is no such a computer\n");
            break;
        case 200:
            recvfrom(c, &ip_addr, sizeof(ip_addr), MSG_WAITALL, (struct sockaddr *) &server, &l);
            ip_addr = ntohl(ip_addr);
            
            struct in_addr addr;
            addr.s_addr = ip_addr;
            printf("Computer's IP address: %s\n", inet_ntoa(addr));
            break;
    }
    close(c);
    return EXIT_SUCCESS;
}
