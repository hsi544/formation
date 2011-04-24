#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

static long num_steps = 100000000;
double step;
int main(int argc, char **argv)
{
				int i;
				double x, pi, sum = 0.0;
				//unsigned long long start, stop;
				double start, stop;
				step = 1.0/(double)(num_steps);

        start = omp_get_wtime();
				//pi calculation
				for(i=0;i<num_steps;i++){
								x=(i+0.5)*step;
								sum=sum+4.0/(1.0+x*x);
				}
				pi = sum*step;
        
        stop = omp_get_wtime();
				
				printf("found pi = %lf \n", pi);
				
				printf("Elapsed time serial version : %lf s\n", stop-start);
				
				return 0;
}
