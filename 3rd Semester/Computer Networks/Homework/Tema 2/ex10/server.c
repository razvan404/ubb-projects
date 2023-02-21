#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int s = socket(AF_INET, SOCK_STREAM, 0); // descriptorul socket-ului server
    if (s < 0) {
        perror("Eroarea la crearea socket-ului server\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server, client; // structura de server si de client
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1337);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    memset(&client, 0, sizeof(client));

    if (bind(s, &server, sizeof(server)) < 0) {
        perror("Eroare la bind\n");
        exit(EXIT_FAILURE);
    }

    // serverul poate deservi maxim 10 clienti simultan
    listen(s, 10);
    
    printf("Server online. Adresa: %s:%d\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));

    while(true) {
        int l = sizeof(client);
        int c = accept(s, &client, &l); // descriptorul socket-ului client
        // cand un client incearca sa se conecteaze, cream un proces pentru deservirea acestuia si vom astepta ca un alt client sa se conecteze
        if (fork() == 0) {
            // vom face deservirea clientului
            printf("S-a conectat un client folosind adresa: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            
            uint16_t len1, len2;
            // primim primul sir
            recv(c, &len1, sizeof(uint16_t), MSG_WAITALL);
            len1 = ntohs(len1);
            char* s1 = malloc((len1 + 1) * sizeof(char));
            recv(c, s1, (len1 + 1) * sizeof(char), 0);
            
            // primim al doilea sir
            recv(c, &len2, sizeof(uint16_t), MSG_WAITALL);
            len2 = ntohs(len2);
            char* s2 = malloc((len2 + 1) * sizeof(char));
            recv(c, s2, (len2 + 1) * sizeof(char), 0);

            uint16_t frec[256], i;
            memset(frec, 0, sizeof(frec));
            uint16_t lenMin = len1 < len2 ? len1 : len2;
            for (i = 0; i < lenMin; ++i) {
                if (s1[i] == s2[i]) {
                    frec[s1[i]]++;
                }
            }
            char max = '\0';
            for (i = 1; i < 256; ++i) {
                if (frec[i] > frec[max]) {
                    max = i;
                }
            }
            uint16_t frecMax = frec[max];
            frecMax = htons(frecMax);
            // trimitem rezultatul
            send(c, &max, sizeof(char), 0);
            send(c, &frecMax, sizeof(uint16_t), 0);
            
            close(c);
            exit(EXIT_SUCCESS);
        }
    }
}
