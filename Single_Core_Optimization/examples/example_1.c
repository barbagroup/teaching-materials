#include <stdio.h>
#include <sys/time.h>

int main(){
	struct timeval start, end;
	double elapsedTime;
	gettimeofday(&start, NULL);
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
		e = g[i];
	}
	gettimeofday(&end, NULL);
	elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;   // us to ms
	printf("Work took %f ms\n", elapsedTime);
return 0;
}

