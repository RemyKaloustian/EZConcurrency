#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 30

long long int fibb(int n) {
  //printf("N = %d\n", n);
	long int fnow = 0, fnext = 1, tempf;
	while(--n>0){
		tempf = fnow + fnext;
		fnow = fnext;
		fnext = tempf;
		}
    //printf("is : %ld \n", fnext);
		return fnext;
}

int main(int argc, char const *argv[]) {
  int data[N] = {100, 300, 8000, 15000,
     4000, 5000, 3300, 2200,
      2700, 3000, 4400, 4200,
      1800, 1900, 4900, 18000, 20000
      , 1200, 40000, 12000, 4, 67, 9000,
    20, 124, 89, 5600, 4000, 1200, 8000};
  int rc = 0;
  int t = 0;
  time_t t1, t2;
  for(t=0; t<N; t++) {
      t1 = clock();
      fibb(data[t]);
      t2 = clock();
      printf("%f %d\n",
       (float) (t2 - t1)/ CLOCKS_PER_SEC,data[t]);
  }
  return 0;
}
