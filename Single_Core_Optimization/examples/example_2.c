#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

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

	float a[10000]; /* a is an array of 10000 floats */
	float b[10000]; /* b is an array of 10000 floats */

	/* initialize elements of array n to 0 */
	for (int i = 0; i < 10000; i++) {
		a[i] = i + 1; /* set element at location i to i + 1 */
		b[i] = i + 1; /* set element at location i to i + 1 */
	}

	struct timeval start, end;
	double elapsedTime;
	gettimeofday(&start, NULL);
	compute1(a, 10000);
	gettimeofday(&end, NULL);
	elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;   // us to ms
	printf("In compute1 work took %f ms\n", elapsedTime);

	gettimeofday(&start, NULL);
	compute2(b, 10000);
	gettimeofday(&end, NULL);
	elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;   // us to ms
	printf("In compute2 work took %f ms\n", elapsedTime);
}