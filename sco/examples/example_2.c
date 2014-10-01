#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


void compute1(float a[], unsigned int N) {
	for (unsigned int i=0; i<N; ++i) {
		if (i==0) {
			a[i] = a[i+1]/2;
		}
		else if (i==N-1) {
			a[i] = a[i-1]/2;
		}
		else { // 0<i<N-1
			a[i] = (a[i-1]+a[i+1])/2;
		}
	}
}

void compute2(float a[], unsigned int N) {
	a[0]=a[1]/2;
	for (unsigned int i=1; i<N-1; ++i) {
		a[i] = (a[i-1]+a[i+1])/2;
	}
	a[N-1]=a[N-2]/2;
}

int main(){

	float a[10000]; /* a is an array of 100 floats */

	/* initialize elements of array n to 0 */
	for (int i = 0; i < 1000; i++) {
		a[i] = i + 1; /* set element at location i to i + 1 */
		}

	double start1 = omp_get_wtime();
	compute1(a, 10000);
	double dif1 = 1.0e6 *(omp_get_wtime() - start1);
	printf("In compute1 work took %f micro-sec\n", dif1);

	double start2 = omp_get_wtime();
	compute1(a, 10000);
	double dif2 = 1.0e6 *(omp_get_wtime() - start2);
	printf("In compute2 work took %f micro-sec\n", dif2);

}


/*how to compile
(X=0,1,2,3)
gcc -OX -std=c99 -o test1.e test1.c -fopenmp -lgomp 
gcc -Ofast -std=c99 -o test1.e test1.c -fopenmp -lgomp
adding -S we generate the assembly and see what happend
*/
