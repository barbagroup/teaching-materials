#include<iostream>
#include<sys/time.h>

#define POWER 10

const int N = 1<<POWER;
const int REPS = 1;

void init(float *A, float *B, float *C, int N)
{
	for(int i=0; i<N; i++)
	{	
		for(int j=0; j<N; j++)
		{
			C[i*N+j] = 0.0;
			A[i*N+j] = 1.0;
			B[i*N+j] = 1.0;
		}
	}
}

void MMMNaive(float *C, float *A, float *B, int N)
{
	for(int i=0; i<N; i++)
	{	
		for(int j=0; j<N; j++)
		{
			for(int k=0; k<N; k++)
			{
				C[i*N+j] += A[i*N+k] * B[k*N+j];
			}
		}
	}
}

double time_MMMNaive(float *C, float *A, float *B, int N)
{
	struct timeval start, end;
	double elapsedTime;

	MMMNaive(C, A, B, N);

	gettimeofday(&start, NULL);
	for(int l=0; l<REPS; l++)
	{
		MMMNaive(C, A, B, N);
	}
	gettimeofday(&end, NULL);

	elapsedTime = (end.tv_sec - start.tv_sec);
	elapsedTime += (end.tv_usec - start.tv_usec)*1e-6;

	return elapsedTime/REPS;
}

int main()
{
	float *A = new float[N*N];
	float *B = new float[N*N];
	float *C = new float[N*N];

	init(A, B, C, N);
	double runTime = time_MMMNaive(C, A, B, N);
	std::cout << "Size of each input matrix: " << N*4.0*N/(1024.0*1024.0) << " MB" << std::endl;
	std::cout << "MMMNaive run time: " << runTime << " seconds" << std::endl;
	std::cout << "FLOPS: " << 2.0*N*N*(N/runTime)/1e9 << " GFLOP/s" << std::endl;

	return 0;
}