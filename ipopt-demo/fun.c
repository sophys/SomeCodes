/* include inet_srcrt_init */
#include	"my.h"

static u_char	*optr;		/* pointer into options being formed */
static u_char	*lenptr;	/* pointer to length byte in SRR option */
static int		ocnt;		/* count of # addresses */

u_char *
inet_srcrt_init(int type)
{
	optr = malloc(44);		/* NOP, code, len, ptr, up to 10 addresses */
	bzero(optr, 44);		/* guarantees EOLs at end */
	ocnt = 0;
	*optr++ = IPOPT_NOP;	/* NOP for alignment */
	*optr++ = type ? IPOPT_SSRR : IPOPT_LSRR;
	lenptr = optr++;		/* we fill in length later */
	*optr++ = 4;			/* offset to first address */

	return(optr - 4);		/* pointer for setsockopt() */
}
/* end inet_srcrt_init */

/* include inet_srcrt_add */
int
inet_srcrt_add(char *hostptr)
{
	int					len;
	struct in_addr a;

	if (ocnt > 9)
		printf("too many source routes with: %s", hostptr);
	if(inet_pton(AF_INET,"192.168.0.50",&a)!=1)
    {
       printf("inet_pton error:%s\n",strerror(errno));
       exit(0);
    }
	memcpy(optr, &a, sizeof(struct in_addr));

	optr += sizeof(struct in_addr);
	ocnt++;
	len = 3 + (ocnt * sizeof(struct in_addr));
	*lenptr = len;
	return(len + 1);	/* size for setsockopt() */
}
/* end inet_srcrt_add */

/* include inet_srcrt_print */
void
inet_srcrt_print(u_char *ptr, int len)
{
	u_char			c;
	char			str[INET_ADDRSTRLEN];
	struct in_addr	hop1;

	memcpy(&hop1, ptr, sizeof(struct in_addr));
	ptr += sizeof(struct in_addr);

	while ( (c = *ptr++) == IPOPT_NOP)
		;		/* skip any leading NOPs */

	if (c == IPOPT_LSRR)
		printf("received LSRR: ");
	else if (c == IPOPT_SSRR)
		printf("received SSRR: ");
	else {
		printf("received option type %d\n", c);
		return;
	}
	printf("%s ", inet_ntop(AF_INET, &hop1, str, sizeof(str)));

	len = *ptr++ - sizeof(struct in_addr);	/* subtract dest IP addr */
	ptr++;		/* skip over pointer */
	while (len > 0) {
		printf("%s ", inet_ntop(AF_INET, ptr, str, sizeof(str)));
		ptr += sizeof(struct in_addr);
		len -= sizeof(struct in_addr);
	}
	printf("\n");
}
/* end inet_srcrt_print */
void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];

	while (fgets(sendline, MAXLINE, fp) != NULL) {

		write(sockfd, sendline, strlen(sendline));

		if (read(sockfd, recvline, MAXLINE) == 0)
			printf("str_cli: server terminated prematurely");
		fputs(recvline, stdout);
	}
}

void
str_echo(int sockfd)
{
	ssize_t		n;
	char		buf[MAXLINE];
	//printf("socket is ===== %d\n",socket);
again:
	while ( (n = read(sockfd, buf, MAXLINE)) > 0)
		write(sockfd, buf, n);

	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		printf("str_echo: read error");
}

