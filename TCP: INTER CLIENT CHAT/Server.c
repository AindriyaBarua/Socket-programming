
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	struct sockaddr_in serv_addr, client_addr;
	
	int sockfd, sockfd2, newsockfd, newsockfd2, clientlen = sizeof (client_addr), childpid;
	char msg[100] = {0};

	sockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockfd2 = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

	bzero ((char*)&serv_addr, sizeof (serv_addr));
	serv_addr.sin_family 		= AF_INET;
	serv_addr.sin_addr.s_addr 	= inet_addr ("127.0.0.1");
	serv_addr.sin_port		= htons (2341);
	bind (sockfd,(struct sockaddr*) &serv_addr, sizeof (serv_addr));
	serv_addr.sin_port		= htons (2340);
	bind (sockfd2,(struct sockaddr*) &serv_addr, sizeof (serv_addr));

	listen (sockfd, 5);
	listen (sockfd2, 5);
	for (;;)
	{
		clientlen = sizeof (client_addr);
		newsockfd = accept (sockfd, (struct sockaddr*)&client_addr, &clientlen);
		newsockfd2 = accept (sockfd2, (struct sockaddr*)&client_addr, &clientlen);

		if ((childpid = fork ()) == 0)
		{
			close (sockfd);
			close (sockfd2);
			read (newsockfd2, msg, 5);
			write (newsockfd, msg, 5);
			read (newsockfd, msg, 5);
			write (newsockfd2, msg, 5);
			exit (0); //free the resourses
		}
		close (newsockfd);
		close (newsockfd2);
	}
	return 0;
}
