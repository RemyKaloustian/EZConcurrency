#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 28
static int data[N] = {100, 300, 75000, 15000,
	 4000, 5000, 3300,
		2700, 3000, 4400, 4200,
		1800, 1900, 4900, 18000, 20000
		, 1200, 40000, 12000, 4, 67,
	20, 124, 89, 5600, 4000, 1200, 8000};

long long int fibb(int n) {
	int fnow = 0, fnext = 1, tempf;
	while(--n > 0){
			tempf = fnow + fnext;
			fnow = fnext;
			fnext = tempf;
	}
}
  //printf("N = %d\n", n);
	void * run (void * ptr_data){
		int nb =*((int * ) ptr_data);
		for (size_t i = nb - (N / 4); i < nb; i++) {
			time_t t1 = clock();
			fibb(data[i]);
			time_t t2 = clock();
			printf("%f %d\n",
			 (float) (t2 - t1)/ CLOCKS_PER_SEC,data[i]);
		}

     return NULL;
}

pthread_t threads[4];

int main(int argc, char const *argv[]) {
	size_t i = 0;
  // for (; i < N/4 ; i++) {
  //   pthread_create(&threads[i], NULL, run, &data[i]);
  // }
	// for (; i < 2*N/4 ; i++) {
	// 	pthread_create(&threads[i], NULL, run, &data[i]);
	// }
	//
	// for (; i < 3*N/4 ; i++) {
	// 	pthread_create(&threads[i], NULL, run, &data[i]);
	// }
	//
	// for (; i < N ; i++) {
	// 	pthread_create(&threads[i], NULL, run, &data[i]);
	// }
	int b1 = N / 4;
	int b2 = 2*N / 4;
	int b3 = 3*N / 4;
	int b4 = N;
 	pthread_create(&threads[0], NULL, run, &b1);
	pthread_create(&threads[1], NULL, run, &b2);
	pthread_create(&threads[2], NULL, run, &b3);
	pthread_create(&threads[3], NULL, run, &b4);

  int rc = 0;
  int t = 0;
  void *  status;
  for(t=0; t<4; t++) {
       rc = pthread_join(threads[t], &status);
  }
  return 0;
}
