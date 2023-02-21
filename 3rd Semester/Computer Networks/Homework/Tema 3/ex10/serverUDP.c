#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdbool.h>

/*
typedef struct PC {
    char name[50];
    int ip_addr;
} PC_t;

PC_t pc[100];

// loads into list the PC name - IP addr pairs
// @returns the length of the list
int loadDB(char* filename) {
    FILE* f = fopen(filename, "r");
    int len = 0;
    
    while (!feof(f)) {
        char name[50];
        fscanf(f, "%s", name);
        strcpy(pc[len].name, name);
        char IP[20];
        fscanf(f, "%s", IP);
        pc[len].ip_addr = htonl(inet_addr(IP));
        ++len;
    }

    return len;
}*/

int main(int argc, char* argv[]) {
    uint16_t OK_FLAG = htons(200);
    uint16_t ERR_FLAG = htons(404);

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server, client;
    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));
    server.sin_port = htons(4444);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    socklen_t l = sizeof(client);

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Bind error");
        exit(EXIT_FAILURE);
    }

    //int len = loadDB("ips.db");

    while(true) {
        // deservirea clientului
        uint16_t str_len;
        recvfrom(s, &str_len, sizeof(str_len), MSG_WAITALL, (struct sockaddr *) &client, &l);
        str_len = ntohs(str_len);
        char* str = malloc(str_len + 1);
        recvfrom(s, str, str_len + 1, MSG_WAITALL, (struct sockaddr *) &client, &l);
        
        /*int i = 0;
        for (; i < len; ++i) {
            if (strcmp(str, pc[i].name) == 0) {
                sendto(s, &OK_FLAG, sizeof(OK_FLAG), 0, (struct sockaddr *) &client, sizeof(client));
                sendto(s, &pc[i].ip_addr, sizeof(pc[i].ip_addr), 0, (struct sockaddr *) &client, sizeof(client));
                break;
            }
        }*/

        struct hostent *remote_host = gethostbyname(str);
        if (remote_host == NULL) {
            sendto(s, &ERR_FLAG, sizeof(ERR_FLAG), 0, (struct sockaddr *) &client, sizeof(client));
        }
        else {
            sendto(s, &OK_FLAG, sizeof(OK_FLAG), 0, (struct sockaddr *) &client, sizeof(client));
            struct in_addr* addr = (struct in_addr *)remote_host->h_addr;
            int ip_addr = htonl(addr->s_addr);
            sendto(s, &ip_addr, sizeof(ip_addr), 0, (struct sockaddr *) &client, sizeof(client));
        }
    }
    close(s);
}
