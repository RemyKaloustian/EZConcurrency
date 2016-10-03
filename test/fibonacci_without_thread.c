#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 28

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
  int data[N] = {1000, 3000, 750000, 15000,
		 40000, 50000, 33000,
			2700, 3000, 44000, 42000,
			18000, 19000, 49000, 180000, 20000
			, 12000, 40000, 12000, 40000, 67000,
		2000, 12400, 89000, 5600, 4000, 120000, 8000};
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
