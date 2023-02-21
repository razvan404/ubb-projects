#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

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
    short n, i, suma = 0;
    char* addr;
    c = accept(s, (struct sockaddr *) &client, &l);
    
    if (fork() == 0) {
      printf("S-a conectat clientul cu adresa: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
      // deservirea clientului
      recv(c, &n, sizeof(n), MSG_WAITALL);
      n = ntohs(n);
      
      short v[n];
      recv(c, &v, sizeof(v), MSG_WAITALL);

      for (i = 0; i < n; ++i) {
        v[i] = ntohs(v[i]);
        suma += v[i];
      }

      suma = htons(suma);
      send(c, &suma, sizeof(suma), 0);
      close(c);

      exit(EXIT_SUCCESS);
      // sfarsitul deservirii clientului;
    }
  }
}
