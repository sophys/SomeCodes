#ifndef	__my_h
#define	__my_h


#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#define MAXLINE 100
#define LENGTH_OF_LISTEN_QUEUE 20
u_char *
inet_srcrt_init(int type);
int
inet_srcrt_add(char *hostptr);
void
inet_srcrt_print(u_char *ptr, int len);
void
str_cli(FILE *fp, int sockfd);
void
str_echo(int sockfd);

#endif
