#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  while(1){
    from_client = server_handshake( &to_client );

    while(read(from_client, buffer, sizeof(buffer))){
      printf("recieved: [%s]\n", buffer);
      //process
      write(to_client, buffer, sizeof(buffer));
    }
  }
}
