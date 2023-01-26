#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Invalid syntax\n");
        printf(" Usage: %s IP_ADDR PORT\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int c = socket(AF_INET, SOCK_STREAM, 0); // descriptorul socket-ului clientului
    if (c < 0) {
        perror("Eroare la crearea socketului client\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server; // structura serverului
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(atoi(argv[2]));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);

    // incercam conectarea la server, daca esueaza vom afisa un mesaj de eroare
    if (connect(c, &server, sizeof(server)) < 0) {
        perror("Eroare la conectarea la server\n");
        exit(EXIT_FAILURE);
    }

    // trimitem serverului datele necesare
    char s1[1000], s2[1000];
    printf("First string: ");
    scanf("%s", s1);
    printf("Second string: ");
    scanf("%s", s2);
    
    uint16_t len1 = strlen(s1), len2 = strlen(s2);
    
    // trimitem primul sir
    len1 = htons(len1);
    send(c, &len1, sizeof(uint16_t), 0);
    send(c, s1, (strlen(s1) + 1) * sizeof(char), 0);

    // trimitem al doilea sir
    len2 = htons(len2);
    send(c, &len2, sizeof(uint16_t), 0);
    send(c, s2, (strlen(s2) + 1) * sizeof(char), 0);

    // primim datele trimise de server
    char cMax;
    uint16_t frecMax;

    recv(c, &cMax, sizeof(char), MSG_WAITALL);
    recv(c, &frecMax, sizeof(uint16_t), MSG_WAITALL);
    frecMax = ntohs(frecMax);
    
    if (cMax == '\0') {
        printf("There are no characters in corresponding positions\n");
    }
    else {
        printf("The character '%c' appears in both the string in corresponding positions %hu times\n", cMax, frecMax); 
    }
    //inchidem socket-ul clientului, acesta a fost deservit
    close(c);
    return EXIT_SUCCESS;
}
