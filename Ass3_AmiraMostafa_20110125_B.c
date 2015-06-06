#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <time.h>

int main(int argc , char * argv[])
{
	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
	int source;		/* rank of sender	*/
	int dest;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	int message;	/* storage for message	*/
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

    time_t sto = time(NULL);
    int st, en , r,rem;
    if (my_rank == 0 ){
         st = 2 ;
         en = 9;
         r= (en-st+1)/p;
    }

    MPI_Bcast( &st,1, MPI_INT,0, MPI_COMM_WORLD);
    MPI_Bcast( &r,1, MPI_INT,0, MPI_COMM_WORLD);
    MPI_Bcast( &en,1, MPI_INT,0, MPI_COMM_WORLD);


	    int i  , beg=st+r*my_rank,subCount=0,TotalCount;
        if (my_rank == p-1){
            r = (en-beg);
        }

        printf("beg is %d r is %d \n" , beg,r);

	    for (i=0; i < r ; ++i){
            int j,prime = 0;
            if (beg == 2 ) ++prime;
            for (j=2; j <beg; ++j){
                if (beg%j == 0 )prime++;}
            if(prime==0)++subCount;
            beg++;
	    }
    MPI_Reduce(&subCount,&TotalCount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if (my_rank == 0){
        printf("total is %d \n" , TotalCount);
        printf("time is %.2f\n", (double)(time(NULL) - sto));
        }

	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
