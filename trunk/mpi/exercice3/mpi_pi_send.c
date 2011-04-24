/**********************************************************************
 *  * FILE: mpi_pi_send.c
 *   * OTHER FILES: dboard.c
 *    * DESCRIPTION:  
 *     *   MPI pi Calculation Example - C Version 
 *      *   Point-to-Point communications example
 *       *   This program calculates pi using a "dartboard" algorithm.  See
 *        *   Fox et al.(1988) Solving Problems on Concurrent Processors, vol.1
 *         *   page 207.  All processes contribute to the calculation, with the
 *          *   master averaging the values for pi. This version uses low level 
 *           *   sends and receives to collect results.
 *            * AUTHOR: Blaise Barney. Adapted from Ros Leibensperger, Cornell Theory
 *             *   Center. Converted to MPI: George L. Gusciora, MHPCC (1/95) 
 *              * LAST REVISED: 04/13/05
 *              **********************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

void srandom (unsigned seed);
double dboard (int darts);
#define DARTS 50000     /* number of throws at dartboard */
#define ROUNDS 10       /* number of times "darts" is iterated */
#define MASTER 0        /* task ID of master task */

int main (int argc, char *argv[])
{
				double	homepi,         /* value of pi calculated by current task */
								pi,             /* average of pi after "darts" is thrown */
								avepi,          /* average pi value for all iterations */
								pirecv,         /* pi received from worker */
								pisum;          /* sum of workers pi values */
				int	taskid,         /* task ID - also used as seed number */
						numtasks,       /* number of tasks */
						source,         /* source of incoming message */ 
						mtype,          /* message type */
						rc,             /* return code */
						i, n;
				MPI_Status status;

				/* Obtain number of tasks and task ID */
				MPI_Init(&argc,&argv);
				MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
				MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
				printf ("MPI task %d has started...\n", taskid);
				if (taskid == MASTER)
								printf ("Using %d tasks to compute pi (3.1415926535)\n",numtasks);

				/* Set seed for random number generator equal to task ID */
				srandom (taskid);

				avepi = 0;
				for (i = 0; i < ROUNDS; i++) {
								/* All tasks calculate pi using dartboard algorithm */
								homepi = dboard(DARTS);

								/* Workers send homepi to master */
								/* - Message type will be set to the iteration count */
								if (taskid != MASTER) {
												mtype = i;
												rc = MPI_Send(&homepi, 1, MPI_DOUBLE,
																				MASTER, mtype, MPI_COMM_WORLD);
												if (rc != MPI_SUCCESS)
																printf("%d: Send failure on round %d\n", taskid, mtype);
								} 
								else
								{
												/* Master receives messages from all workers */
												/* - Message type will be set to the iteration count */
												/* - Message source will be set to the wildcard DONTCARE: */
												/*   a message can be received from any task, as long as the */
												/*   message types match */
												/* - The return code will be checked, and a message displayed */
												/*   if a problem occurred */
												mtype = i;
												pisum = 0;
												for (n = 1; n < numtasks; n++) {
																rc = MPI_Recv(&pirecv, 1, MPI_DOUBLE, MPI_ANY_SOURCE,
																								mtype, MPI_COMM_WORLD, &status);
																if (rc != MPI_SUCCESS) 
																				printf("%d: Receive failure on round %d\n", taskid, mtype);
																/* keep running total of pi */
																pisum = pisum + pirecv;
												}
												/* Master calculates the average value of pi for this iteration */
												pi = (pisum + homepi)/numtasks;
												/* Master calculates the average value of pi over all iterations */
												avepi = ((avepi * i) + pi)/(i + 1); 
												printf("   After %8d throws, average value of pi = %10.8f\n",
																				(DARTS * (i + 1)),avepi);
								}    
				} 

				MPI_Finalize();
				return 0;
}

