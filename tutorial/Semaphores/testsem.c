#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <pthread.h>

  

sem_t mutex;


int mahInt = 0;

pthread_t t1; //the thread declaration
pthread_t t2; //the thread declaration


void * change_a()
{
    sem_wait(&mutex);
    for (size_t i = 0; i < 5; i++)
    {
        mahInt++;
    }

    sem_post(&mutex);
    
    return NULL;
}

void * change_b()
{
	sem_wait(&mutex);
    for (size_t i = 0; i < 5; i++)
    {
        mahInt--;
    }

    sem_post(&mutex);
    
    return NULL;
}

int main()
{
	
	//Incrementing 5 times mahInt, then decrementing it 5 times, the semaphore structure assures that it will be 0 at the end
	
	sem_init(&mutex,0,1);

    printf("mahInt before : %d", mahInt);
    
    //Creating and joining thread1
    if(pthread_create(&t1, NULL, &change_a,NULL))
	{
		
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	if(pthread_join(t1, NULL)) 
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}	

//Creating andjoining thread2
    if(pthread_create(&t2, NULL, &change_b,NULL))
	{
		
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	if(pthread_join(t2, NULL)) 
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}	
    printf("mahInt after : %d", mahInt);


}
