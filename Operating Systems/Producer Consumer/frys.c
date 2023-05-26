#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define queuesize 5
#define MAX 5000000
//#define INITIAL_CUSTOMERS 1
//#define NUM_CASHIERS 15
//#define NONSHARED 1-

pthread_cond_t consumer_c;
pthread_cond_t producer_c;
pthread_mutex_t mutex;
char* message;
char a;
int front =-1;
int end =-1;
int index=0;
int size;
char q[queuesize];

void* producer(void *pointer)
{
	while(index<size)
	{
		pthread_mutex_lock(&mutex);
		while((front==0&&end==queuesize-1)||front==end+1)//if q is full, then wait
		{
			pthread_cond_wait(&producer_c,&mutex);
		}

		if(front==-1)
		{
			front =0;
		}
		end = end+1;
		end=end % queuesize;
		q[end]=message[index];
		pthread_cond_signal(&consumer_c);//prime consumer into action
		index++;
		pthread_mutex_unlock(&mutex);//releases
	}
	pthread_exit(0);
}

void* consumer(void *pointer)
{
	while(index<size)
	{
		pthread_mutex_lock(&mutex);
		while(front==-1)
		{
			pthread_cond_wait(&consumer_c,&mutex);
		}
		a = q[front];//grabs first element in q
		if(front==end)//checks to see if it is empty
		{
			front=-1;
			end=-1;

		}
		else
		{
			front+=1;
			front = front % queuesize;
		}
		printf("%c",a);

		pthread_cond_signal(&producer_c);
		pthread_mutex_unlock(&mutex);
	}
	printf("\n");
	pthread_exit(0);
}

int main( int argc, char *argv[] )
{
	FILE *fp;
	fp = fopen("message.txt","r");
	message = (char *)malloc(sizeof(char)*MAX);
	message=fgets(message, MAX, fp);
	size = strlen(message);
	printf("- Entered String: -\n%s\n",message);
	printf("- String printed (through producer and consumer) -\n");
  	pthread_t producer_t;
  	pthread_t consumer_t;
  	pthread_mutex_init(&mutex,NULL);
  	pthread_cond_init(&consumer_c,NULL);
  	pthread_cond_init(&producer_c,NULL);
  	pthread_create(&consumer_t,NULL,consumer,NULL);
  	pthread_create(&producer_t,NULL,producer,NULL);
  	pthread_join(consumer_t,NULL);
  	pthread_join(producer_t,NULL);

}
