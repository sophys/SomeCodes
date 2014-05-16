#include	"my.h"

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(50000);

	bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

	listen(listenfd, LENGTH_OF_LISTEN_QUEUE);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr*) &cliaddr, &clilen);
        printf("socket is------> %d\n",connfd);
		if ( (childpid = fork()) == 0) {	/* child process */
			close(listenfd);	/* close listening socket */
			//printf("socket is %d\n",connfd);
			str_echo(connfd);	/* process the request */
			exit(0);
		}
		//close(connfd);			/* parent closes connected socket */
	}
}
