#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  int i;
  printf("%d\n", argc);
  if (argc != 3) {
    printf("Invalid input!\n");
    printf(" Syntax: %s IP PORT\n", argv[0]);
    exit(-1);
  }

  int c;
	struct sockaddr_in server;
 	short n, suma;

	c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(atoi(argv[2]));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  printf ("Lungimea sirului: "); 
  scanf("%hd", &n);
  n = htons(n);
  send(c, &n, sizeof(n), 0);
  n = ntohs(n);
  short v[n];

  printf ("Elementele sirului: ");
  for (i = 0; i < n; ++i) {
    scanf("%hd", &v[i]);
    v[i] = htons(v[i]);
  }
  
  send(c, &v, sizeof(v), 0);
  recv(c, &suma, sizeof(suma), MSG_WAITALL);
  suma = ntohs(suma);
  printf("Suma ceruta: %hd\n", suma);
  close(c);
}
