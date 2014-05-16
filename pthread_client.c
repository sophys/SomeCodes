#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10
#define LONG 4096

#define CONSUMER 2

#define HELLO_WORLD_SERVER_PORT 7754
//#define LENGTH_OF_LISTEN_QUEUE 10
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <unistd.h>

//void *pth_functionProducer();
void *pth_functionConsumer(void *);

int count=0;
int fp;

//pthread_mutex_t Rmutex;

typedef struct node
{
   off_t offset;
   char data[LONG];
}NODE;
struct sockaddr_in server_addr;
socklen_t server_addr_length;

int main(int argc, char *argv[])
{
    // if (argc != 2)
    // {
    //    printf("Usage: ./%s ServerIPAddress\n",argv[0]);
    //    exit(1);
    // }
	//设置一个socket地址结构server_addr,代表服务器的internet地址, 端口
    char ip[16];
    scanf("%s",ip);

bzero(&server_addr,sizeof(server_addr));
server_addr.sin_family = AF_INET;
if(inet_aton(ip,&server_addr.sin_addr) == 0) //服务器的IP地址来自程序的参数
{
   printf("Server IP Address Error!\n");
   exit(1);
}
server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
server_addr_length = sizeof(server_addr);
     
     if((fp=open("file", O_WRONLY|O_CREAT, 0666))<0) 
    { 
       printf("cant't open file.\n"); 
       exit(0);
    }
    int index;
    pthread_t  pthW_t[CONSUMER];
    void *pRslt=NULL;
	//创建消费者线程
    int err;
    for(index=0;index<CONSUMER;index++)
    {
    
     if((err=pthread_create(&pthW_t[index],NULL,pth_functionConsumer,(void*)index))!=0)
      {
       printf("Create Consumer Thread %d Failed . exit !\n",index);
       exit(0);
      }
      sleep(2);
    }
    //等待消费者线程退出	
     for(index=0;index<CONSUMER;index++)
        {
           if((err=pthread_join(pthW_t[index],&pRslt))!=0)
               {
                        printf("Can not join Consumer Thread .exit");
                        exit(0);
                }
               else
               {
                       printf("Consumer Thread %d exit.!\n",(int)pRslt);
             }
        }
           //关闭 文件
        close(fp);  	
   return 0;
}

void * pth_functionConsumer(void * arg)
{
        int th_t;
        th_t = (int) arg;
    
        printf("Consumer %d Thread Create !\n",th_t);
        int client_socket = socket(AF_INET,SOCK_STREAM,0);
        if( client_socket < 0)
        {
           printf("Create Socket Failed!\n");
           exit(1);
        }
       if(connect(client_socket,(struct sockaddr*)&server_addr, server_addr_length) < 0)
        {
           printf("Can Not Connect To sever!\n");
           exit(1);
        }
        
		NODE node;
		bzero(&node,sizeof(NODE));
		int len;
          // printf("Can Not Connect To sever!\n");
     recv(client_socket,&node,sizeof(NODE),0);
     
        pwrite(fp,node.data,sizeof(node.data),node.offset);
        printf("Recieve File From Server[] Finished\n");

        return arg;
}
