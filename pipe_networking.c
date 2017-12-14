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
  char * toSrv = "/toSrv";
  char * toChck = "/toChck";
  mkfifo(toClnt, 0666);
  mkfifo(toSrv, 0666);
  mkfifo(toChck, 0666);
  char toSend[512], toRcv[512], toCheck[512];
  while (1){
    int fd2 = open(toSrv, O_RDONLY);
    read(fd2, toRcv, sizeof(toRcv));
    close(fd2);
    
    if(strcmp(toRcv, PIN) == 0){
      int fd1 = open(toClnt, O_WRONLY);
      //fgets(toSend, 512, stdin);
      strcpy(toSend, PIN);
      write(fd1, toSend, strlen(toSend) + 1);
      close(fd1);
      
      
      int fd3 = open(toChck, O_RDONLY);
      read(fd3, toCheck, sizeof(toCheck));
      close(fd3);

      if (strcmp(toCheck, PIN) == 0){
	printf("Handshake successful!\n");
      }
    }
    return 0;
  }
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
  char * toSrv = "/toSrv";
  char * toChck = "/toChck";
  mkfifo(toClnt, 0666);
  mkfifo(toSrv, 0666);
  mkfifo(toChck, 0666);
  char toRcv[512], toSend[512], toCheck[512];
  while(1){

    
    int fd2 = open(toSrv, O_WRONLY);
    //fgets(toSend, 512, stdin);
    strcpy(toSend, PIN);
    write(fd2, toSend, strlen(toSend) + 1);
    close(fd2);
    
    int fd1 = open(toClnt, O_RDONLY);
    read(fd1, toRcv, sizeof(toRcv));
    close(fd1);

    if(strcmp(toRcv, PIN) == 0){
      int fd3 = open(toChck, O_WRONLY);
      //fgets(toSend, 512, stdin);
      strcpy(toSend, PIN);
      write(fd3, toSend, strlen(toSend) + 1);
      close(fd3);
    } 
  }
  return 0;
}
