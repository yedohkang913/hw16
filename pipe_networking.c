#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  char * toClnt = "/toClnt";
  mkfifo(toClnt, 0666);
  char toSend[512];
  while (1){
    int fd = open(toClnt, O_WRONLY);
    fgets(toSend, 512, stdin);
    write(fd, toSend, strlen(toSend) + 1);
    close(fd);
  return 0;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char * toClnt = "/toClnt";
  mkfifo(toClnt, 0666);
  char toRcv[512];
  return 0;
}
