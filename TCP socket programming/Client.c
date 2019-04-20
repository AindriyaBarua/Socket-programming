#include	<netinet/in.h>
#include	<stdlib.h>
#include	<string.h>
#include	<arpa/inet.h>
#include	<sys/socket.h>
#include	<stdio.h>
#include	<unistd.h>
int main()
{
	int sockfd;
	struct sockaddr_in serv_addr;

	bzero ((char*)&serv_addr, sizeof (serv_addr));
	serv_addr.sin_family 	= AF_INET;
	serv_addr.sin_addr.s_addr	= inet_addr ("127.0.0.1");
	serv_addr.sin_port	= htons (2345);

	sockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

	connect (sockfd, (struct sockaddr*)&serv_addr, sizeof (serv_addr));

	char data[100] = {0};
	
	write (sockfd, "helloP", 6);
	read (sockfd, data, 6);
	printf ("%s", data);
	close (sockfd);
	exit (0);
	return 0;	
}
