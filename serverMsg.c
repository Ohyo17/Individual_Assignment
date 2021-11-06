#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<signal.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc , char *argv[])
{
	int socket_desc , new_socket , c;
	struct sockaddr_in server , client;
	char *message,serverMsg[20000],buff[20000],buffer[20000];

	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
		
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;//Bind any IP address with the SERVER
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	printf("**** Waiting for CLIENT Message *****\n\n");
	//Message with CLIENT
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
			puts("Connection Accepted");
			if((recv(new_socket,buff,20000,0))>0)
			{
				
				recv(socket_desc,buff,20000,0);
				printf("CLIENT: %s\n",buff);
				printf("****Received Message from CLIENT !!!****\n");
				return 1;
			
			}
	}
	
	if (new_socket<0)
	{
		perror("accept failed");
		return 1;
	}
	close(socket_desc);
	return 0;
	
}
