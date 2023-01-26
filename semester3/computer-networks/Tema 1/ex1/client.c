#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
 
int main() {
  int c;
	struct sockaddr_in server;
 	short n, i, x, suma;

	c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1337);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  printf ("Lungimea sirului: "); 
  scanf("%hd", &n);
  n = htons(n);
  send(c, &n, sizeof(n), 0);
  n = ntohs(n);

  printf ("Elementele sirului: ");
  for (i = 0; i < n; ++i) {
    scanf("%hd", &x);
    x = htons(x);
    send(c, &x, sizeof(x), 0);
  }

  recv(c, &suma, sizeof(suma), MSG_WAITALL);
  suma = ntohs(suma);
  printf("Suma ceruta: %hd\n", suma);
  close(c);
}
