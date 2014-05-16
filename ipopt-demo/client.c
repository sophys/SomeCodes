#include	"my.h"

int
main(int argc, char **argv)
{
	int					c, sockfd, len = 0;
	int optind=1;
	u_char				*ptr = NULL;
	struct addrinfo		*ai;

	if (argc < 2)
		printf("usage: tcpcli01 [ -[gG] <hostname> ... ] <hostname>");
	while ( (c = getopt(argc, argv, "gG")) != -1) {
		switch (c) {
		case 'g':			/* loose source route */
			if (ptr)
				printf("can't use both -g and -G");
			ptr = inet_srcrt_init(0);
			break;

		case 'G':			/* strict source route */
			if (ptr)
				printf("can't use both -g and -G");
			ptr = inet_srcrt_init(1);
			break;

		case '?':
			printf("unrecognized option: %c", c);
		}
	}

	if (ptr)
		while (optind < argc-1)
			len = inet_srcrt_add(argv[optind++]);
	else
		if (optind < argc-1)
			printf("need -g or -G to specify route");

	if (optind != argc-1)
		printf("missing <hostname>");
		
	printf("%s\n",argv[optind]);

	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr)); 
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[optind]);
	server_addr.sin_port = htons(50000);

	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if (ptr) {
		len = inet_srcrt_add(argv[optind]);	/* dest at end */
		setsockopt(sockfd, IPPROTO_IP, IP_OPTIONS, ptr, len);
		free(ptr);
	}

	if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))==-1)
	{
    	printf("%s\n",strerror(errno));
		return -1;
	}

	str_cli(stdin, sockfd);		/* do it all */

	exit(0);
}
