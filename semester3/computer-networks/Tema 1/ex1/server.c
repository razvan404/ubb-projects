#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
  int s;
  struct sockaddr_in server, client;
  int c, l;
  
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1337);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }
 
  listen(s, 5);
  
  l = sizeof(client);
  memset(&client, 0, sizeof(client));
  
  while (1) {
    short n, i, x, suma = 0;
    char* addr;
    c = accept(s, (struct sockaddr *) &client, &l);

    addr = inet_ntoa(client.sin_addr);
    printf("S-a conectat clientul cu adresa: %s:%d\n", addr, ntohs(client.sin_port));
    // deservirea clientului
    recv(c, &n, sizeof(n), MSG_WAITALL);
    n = ntohs(n);

    for (i = 0; i < n; ++i) {
      recv(c, &x, sizeof(x), MSG_WAITALL);
      x = ntohs(x);
      suma += x;
    }

    suma = htons(suma);
    send(c, &suma, sizeof(suma), 0);
    close(c);
    // sfarsitul deservirii clientului;
  }
}
