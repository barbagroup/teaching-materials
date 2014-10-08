#include<iostream>
#include<sys/time.h>
#include<assert.h>

#define POWER1 10
#define POWER2 7

const int N = 1<<POWER1;
const int BS = 1<<POWER2;
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

void MMMBlocked(float *C, float *A, float *B, int N)
{
	for(int i=0; i<N; i+=BS)
	{	
		for(int j=0; j<N; j+=BS)
		{
			for(int k=0; k<N; k+=BS)
			{
				for(int ii=i; ii<i+BS; ii++)
				{
					for(int jj=j; jj<j+BS; jj++)
					{
						for(int kk=k; kk<k+BS; kk++)
						{
							C[ii*N+jj] += A[ii*N+kk] * B[kk*N+jj];
						}
					}
				}
			}
		}
	}
}

double time_MMMBlocked(float *C, float *A, float *B, int N)
{
	struct timeval start, end;
	double elapsedTime;

	MMMBlocked(C, A, B, N);

	gettimeofday(&start, NULL);
	for(int l=0; l<REPS; l++)
	{
		MMMBlocked(C, A, B, N);
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

	assert(N%BS==0);
	init(A, B, C, N);
	double runTime = time_MMMBlocked(C, A, B, N);
	std::cout << "Size of each input matrix: " << N*4.0*N/(1024.0*1024.0) << " MB" << std::endl;
	std::cout << "Block size: " << BS*4.0*BS/(1024.0) << " kB" << std::endl;
	std::cout << "MMMBlocked run time: " << runTime << " seconds" << std::endl;
	std::cout << "FLOPS: " << 2.0*N*N*(N/runTime)/1e9 << " GFLOP/s" << std::endl;

	return 0;
}