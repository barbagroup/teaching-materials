#include <stdio.h>
#include <omp.h>

int main(){
	double start = omp_get_wtime();
	float a[100] = {0.};
	float g[100] = {0.};
	float c=2, d=3, e;
	for (int i=0;i<100;++i) {
		a[i] = 2.0*i;
		g[i] = 3.0*i;
	}
	float ans[100] = {0.};
	for (int i=0;i<100;++i) {
		ans[i] =  a[i]*c + g[i]*d;
//		printf("%f ", ans[i]);
		e = g[i];
	}
	double dif = 1.0e6 *(omp_get_wtime() - start);
	printf("Work took %f micro-sec\n", dif);
return 0;
}

/*
To compile:
	gcc -std=c99 -O3 -o example_2 example_2.c -fopenmp -lgomp
If you want to generate the assembly code:
	gcc -std=c99 -O3 -S  example_2.c -fopenmp -lgomp
*/

