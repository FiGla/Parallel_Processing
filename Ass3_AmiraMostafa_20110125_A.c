#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <time.h>

int main(int argc , char * argv[]){
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

    if (my_rank == 0 ){
         int st, en , r,index=0,TotalCount=0,i;
         st = 2 ;
         en = 10;
         r=(en-st)/(p-1);

        for(i=1;i<p; ++i){
            if (i == p-1 )
                ++r;
            st+=index;
            MPI_Send( &st,1, MPI_INT,i, tag, MPI_COMM_WORLD);
            MPI_Send( &r,1, MPI_INT,i, tag, MPI_COMM_WORLD);
            index+=r;
        }


        for (i=1;i<p ; ++i){
            int co ;
            MPI_Recv(&co, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &status );

            TotalCount +=co;
        }
        printf("total is %d \n" , TotalCount);
        printf("time is %.2f\n", (double)(time(NULL) - sto));


    }
    if(my_rank != 0 ){
        int beg,range,subCount=0,i;
        MPI_Recv(&beg, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status );
        MPI_Recv(&range, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status );

         for (i=0; i < range ; ++i){
            int j,prime = 0;
            if (beg == 2 ) ++prime;
            for (j=2; j <beg; ++j){
                if (beg%j == 0 )prime++;}
            if(prime==0)++subCount;
            beg++;
        }


        MPI_Send(&subCount,1, MPI_INT,0, tag, MPI_COMM_WORLD);
    }


	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
