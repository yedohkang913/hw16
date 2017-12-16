#include "pipe_networking.h"

char *change(char *str) {
	int i = strlen(str) -1;
	int j = 0;
	char ch;
	while (i>j) {
		ch = str[i];
		str[i] = str[j];
		str[j] = ch;
		i--;
		j++;
	}
	return str;
}


int main() {

	int to_client;
	int from_client;
	
	from_client = server_handshake( &to_client );

	while(1){
		char buffer[BUFFER_SIZE];
		read(from_client, buffer, sizeof(buffer));
		printf("received from client: %s\n", buffer);
		char *c = change(buffer);
		printf("modified text and sending to client: %s\n", buffer);
		write(to_client, buffer, sizeof(buffer));
	}
	
	return 0;
}
