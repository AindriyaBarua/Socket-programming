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
	
	int sockfd, newsockfd, clientlen = sizeof (client_addr), childpid;
	int msg[100] = {0};

	sockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

	bzero ((char*)&serv_addr, sizeof (serv_addr));
	serv_addr.sin_family 		= AF_INET;
	serv_addr.sin_addr.s_addr 	= inet_addr ("127.0.0.1");
	serv_addr.sin_port		= htons (2345);
	bind (sockfd,(struct sockaddr*) &serv_addr, sizeof (serv_addr));

	listen (sockfd, 5);
	for (;;)
	{
		clientlen = sizeof (client_addr);
		newsockfd = accept (sockfd, (struct sockaddr*)&client_addr, &clientlen);

		if ((childpid = fork ()) == 0)
		{
			close (sockfd);
			//write (newsockfd, "hai", 4);
			read (newsockfd, msg, 6);
			printf ("CLIENT SENT %s", msg);
			for(int i=0;i<6;i++)
  { int c=0;
	    for(int j=1; j<6; j++)
	    {
			if(msg[i]%j==0)
			c++;
		}
		if(c==0)
		write (newsockfd, msg[i], 1);
		
  }
  
  
  			
			
			exit (0); //free the resourses
		}
		close (newsockfd);
	}
	return 0;
}
