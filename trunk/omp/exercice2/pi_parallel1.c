#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#define NUM_THREADS 2


static long num_steps = 10000000;
double step;
int main(int argc, char **argv)
{
				int i;
				double x, pi;
				double sum[NUM_THREADS] = {0.0};
				int N;
				double start, stop;
				int startIndex, stopIndex;
				int chunkSize;
				int ID;
				step = 1.0/(double)(num_steps);


				start = omp_get_wtime();
#pragma omp parallel num_threads(NUM_THREADS) private(ID, N, startIndex, stopIndex) shared(sum)
				{
								//get omp num threads
								N = omp_get_num_threads();
								ID = omp_get_thread_num();				
								chunkSize = num_steps/N;

								startIndex = ID*chunkSize;
								stopIndex = startIndex+chunkSize;
								//pi calculation
								for(i=startIndex;i<stopIndex;i++){
												x=(i+0.5)*step;
												sum[ID]=sum[ID]+4.0/(1.0+x*x);
								}
				}
				for (i=0;i<NUM_THREADS;i++)
				  pi += sum[i];
				pi*=step;

				stop = omp_get_wtime();

        printf("found pi   = %lf \n", pi);

				printf("Elapsed time parallel version : %lf s\n", stop-start);

				return 0;
}
