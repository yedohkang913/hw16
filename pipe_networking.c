#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {

	mkfifo("beaver", 0644);
	printf("Waiting for connection with client...\n");
  
	int wkp = open("beaver", O_RDONLY);
	remove("beaver");
	
	char buffer[HANDSHAKE_BUFFER_SIZE];
  read(wkp, buffer, sizeof(buffer));
  printf("received from client: %s\n", buffer);
  
	int p = open(buffer, O_WRONLY);
	//char c[] = "server confirmed!";
  write(p, ACK, sizeof(ACK));
	
  read(wkp, buffer, sizeof(buffer));
  printf("sent message to client: %s\n", buffer);
	
	*to_client = p;

  return wkp;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {

  char s[HANDSHAKE_BUFFER_SIZE];
  sprintf(s, "%d", getpid());
  mkfifo(s, 0644);
  printf("connecting to server...\n");
	
  int wkp = open("beaver", O_WRONLY);
	write(wkp, s, sizeof(s));
	printf("sent pipe %s to server\n", s);

  int p = open(s, O_RDONLY);
	char ack[sizeof(ACK)];
  read(p, ack, sizeof(ack));
  printf("received from server: %s\n", ack);
	remove(s);

	//char a[] = "client confirmed!";
  write(wkp, ACK, sizeof(ACK));
	//printf("sending response to server: %s\n", a);

	*to_server = wkp;
  return p;
}
