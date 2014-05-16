#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10
#define LONG 4096

#define CONSUMER 2

#define HELLO_WORLD_SERVER_PORT 7754
#define LENGTH_OF_LISTEN_QUEUE 10
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <unistd.h>

void *pth_functionProducer();
void *pth_functionConsumer(void *);

int count=0;
int fp;

pthread_mutex_t Rmutex;

typedef struct node
{
   off_t offset;
   char data[LONG];
}NODE;

struct BUF
{
    int flag;
    NODE *node;
}buf[SIZE];

int isEmpty();
int isFull();

int main(int argc,char *argv[])
{
   int err;
   int index=0;
   int m;
   void *pRslt=NULL;
   for(m=0;m<SIZE;m++)
   {
     buf[m].flag=0;
   }
   
   pthread_t  pthR_t;//生产者线程ID
   pthread_t  pthW_t[CONSUMER];
   
   if((fp=open(argv[1],O_RDONLY))<0)
   {
      printf("can't open file %s.\n",argv[1]);
   }
   
   
   
  //设置服务器套接口
  
  struct sockaddr_in server_addr;
   bzero(&server_addr,sizeof(server_addr)); //把一段内存区的内容全部设置为0
   //struct sigaction act;   //定义结构变量
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = htons(INADDR_ANY);
   server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
   
   int server_socket = socket(AF_INET,SOCK_STREAM,0);
   if( server_socket < 0)
   {
      printf("Create Socket Failed!");
      exit(1);
   }
     if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
       printf("Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT);
       exit(1);
    }
//server_socket用于监听
if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
{
printf("Server Listen Failed!");
exit(1);
}

    //创建生成者线程
        if(pthread_mutex_init(&Rmutex,NULL)!=0)
        {
          printf("create mutex failed!\n");
          pthread_mutex_destroy(&Rmutex);
          exit(0);
        }
        if((err=pthread_create(&pthR_t,NULL,pth_functionProducer,NULL))!=0)
        {
          printf("Create Producer Thread %d Failed . exit !\n",err);
          exit(0);
        }

	while(1)  //服务器要一直运行
	{
	    pthread_t  pthC;
      int new_server_socket = accept(server_socket,NULL,NULL);
	    if (new_server_socket< 0)
        {
             perror("accept");
             continue;
        }
      	//创建消费者线程       
      		if((err=pthread_create(&pthC,NULL,pth_functionConsumer,(void*)new_server_socket))!=0)
      		{
      			printf("Create Consumer Thread Failed . exit !\n");
      			exit(0);
      		}     
      	//等待消费者线程退出	
      		if((err=pthread_join(pthC,pRslt))!=0)
      		{
      			printf("Can not join Consumer Thread .exit");
      			exit(0);
      		}
      		else
      		{
      			printf("Consumer Thread %d exit.!\n",(int)pRslt);
      		}   
  } 
        //等待生产者线程退出
        
        if((err=pthread_join(pthR_t,NULL))!=0)
        {
          printf("Can not join Producer Thread . exit\n");
          exit(0);
        }
        else
        {
          printf("Producer Thread  exit.!\n" );
        }
  pthread_mutex_destroy(&Rmutex);
	close(server_socket);
	close(fp);
  return 0;
}

 int isEmpty()
      {
      	int  flag;
      	int i;
      	for(i=0;i<SIZE;i++)
      	{
      		if(buf[i].flag==0)
      		{
      			flag=1;
      			break;
      		}
      	}
      
      	if(flag)
      	{
      		return 1;
      	}
      	else
      	{
      		return 0;
      	}
      
      }
      
int isFull()
{
      	int flag;
      	int i;
      	for(i=0;i<SIZE;i++)
      	{
      		if(buf[i].flag==1)
      		{
      			flag=1;
      			break;
      		}
      	}		
      	if(flag)
      	{
      		return 1;
      	}
      	else
      	{
      		return 0;
      	}
}


void * pth_functionProducer()
{
    int i;
	printf("Producer Thread Create !\n");
	while(1)
	{
	     if(isEmpty())
		 {
		     for(i=0;i<SIZE;i++)
			 {
			     if(buf[i].flag==0)
				 {
				    NODE *node;
					node=(NODE *)malloc(sizeof(NODE));
					if(read(fp,node->data,sizeof(node->data))>0)
                                        {
					  node->offset=count*LONG;
					  count++;
					  pthread_mutex_lock(&Rmutex);
					  buf[i].flag=1;
					  buf[i].node=node;		  
					  pthread_mutex_unlock(&Rmutex);
					
					}
					else
					{
					goto p1;
					}
				
				 }
			 }
		 }
	
	
	}
	p1: printf("du jie shu");
    return 0;
}
void * pth_functionConsumer(void * arg)
{
      	int socket;
      	socket = (int)arg;
      	int i;
      	printf("Consumer  Thread Create !\n");
      	
      	while(1)
      	{
      		if(isFull())
      		{
      			for(i=0;i<SIZE;i++)
      			{	
              pthread_mutex_lock(&Rmutex);				
      				if(buf[i].flag==1)
      				{
                                    
                  buf[i].flag=0;
      				   if(send(socket,buf[i].node,4100,0)<0)
                                   {
		                    printf("Send File is Failed\n");   
                                    break;
	                            }
				        free(buf[i].node);
				   
      				}
              pthread_mutex_unlock(&Rmutex);
              close(socket);
              break;					
      			}
      		}
       		usleep(1);
      		if(isEmpty())
      		{
      		    close(socket);
              break;
      		}  
      	}	
      	return arg;
}


