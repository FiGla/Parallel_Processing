#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc , char * argv[]){
	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
	int source = 0;		/* rank of sender	*/
	int des;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	int j,i,k;
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

    /*the size of message for each process*/

	if( my_rank != 0){
		int Cut;
		/* receive number of rows and cols for 2 matrices */
		MPI_Recv(&Cut, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );

		/* allocate matrix #1 */
		int *arr = malloc(Cut*sizeof( int ));

		for (i = 0; i < Cut; i++){
           MPI_Recv(&(arr[i]), 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
		}

        double res =0;

		for (i = 0; i < Cut; i++)
            res += arr[i];

			MPI_Send(&(res), 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD);

	}else{

		int arr[10] = {10,10,10,10,10,10,10,10,10,10};
		double res;
		int size =10;
		int Cut = size / (p - 1);
	    int index = 0;

		for( des = 1; des < p ; des++){
		    if(des == p - 1)
			   Cut = Cut + (size % (p - 1));

			MPI_Send(&Cut, 1, MPI_INT, des, tag, MPI_COMM_WORLD);
           for (i=0; i <Cut; ++i)
            MPI_Send(&(arr[i+index]), 1 , MPI_INT, des, tag, MPI_COMM_WORLD);

			index += Cut;
		}

		Cut = size / (p - 1);
		index = 0;

		for( des = 1; des < p ; des++){
            double X;
		    if(des == p - 1)
			   Cut = Cut + (size % (p - 1));

            MPI_Recv(&X, 1 , MPI_DOUBLE, des, tag, MPI_COMM_WORLD, &status );
            res += X;
        }

		printf("the final result\n");
        res = res/(double)size;
        printf("%f " , res);
	}
	/* shutdown MPI */

	MPI_Finalize();
	return 0;
}

