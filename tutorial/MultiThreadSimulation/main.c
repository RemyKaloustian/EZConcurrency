#include <pthread.h>
#include <stdio.h>
#include	<stdint.h>
#include <inttypes.h>
#include <unistd.h>


//THIS PROGRAM TESTS THE DIFFERENT CASES OF THREADS

int grid[5] = {0,1,2,3,4};

pthread_t one_thread; //the thread declaration
	char decision=' ';

void move(int id)
{
	printf("Moving  %d \n", id);	
	
	
}

void * one_thread_move()
{
	printf("Moving the elements one by one with one thread\n");
	int i;
	for (i=0; i<5  ; i++)
	{
		//printf("moving in for");
		move(grid[i]);
	}
	
}

void * four_thread_move()
{
	printf(" ");
}

void * max_thread_move()
{
	
}


int main()
{
	
	
	printf("What type of thread do you want ? \n (0 = 1 general thread,1 = 4 threads (cuz four parts of the map), 2 = a thread per moving element)\n  (0/1/2)");
	scanf("%c",&decision);
	
	if(decision == '0')
	{
		//printf("Decision =0");
		if(pthread_create(&one_thread, NULL, &one_thread_move,NULL))
		{
			
			fprintf(stderr, "Error creating thread\n");
			return 1;
		}
		if(pthread_join(one_thread, NULL)) 
		{
			fprintf(stderr, "Error joining thread\n");
			return 2;
		}	
	}

	
	printf("In the main program");
	
	return 0;
	
}//main()

