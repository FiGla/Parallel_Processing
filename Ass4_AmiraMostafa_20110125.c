#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc , char * argv[]){
	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
	int source=0;		/* rank of sender	*/
	int dest;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	int message;	/* storage for message	*/
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/
    MPI_Init( &argc , &argv );
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    int size =1000,i , x,root=0,cut = size/p;
    int arr[size],arrB[size];
    float totalAvg=0;

    if ( size%p !=0);

    if (my_rank == 0 ){
        FILE *myfile;
        myfile = fopen("Test.txt", "r");
        i=0;
        while ( i != size){
                fscanf(myfile, "%d",&x);
                arr[i] = x;
                ++i;
        }
    }
     MPI_Scatter(&arr,cut, MPI_INT,arrB,cut,MPI_INT,root,MPI_COMM_WORLD);

       float Avg=0;
       for (i=0 ; i <cut;++i){
            Avg+= arrB[i];
       }
        Avg /= cut;

    MPI_Reduce(&Avg,&totalAvg,1,MPI_FLOAT,MPI_SUM,root,MPI_COMM_WORLD);
     if (my_rank == 0){
            totalAvg/=p;
     }

    MPI_Bcast( &totalAvg,1, MPI_FLOAT,0, MPI_COMM_WORLD);


     for (i=0 ; i <cut;++i){
            arrB[i]-=totalAvg;
    }

    MPI_Gather(&arrB,cut, MPI_INT,arr,cut,MPI_INT,root,MPI_COMM_WORLD);

    printf("HELLLO\n");
     if (my_rank == 0 ){
        FILE *newMyFile;
        newMyFile = fopen("Out.txt", "w");
        i=0;
        while ( i != size){
                fprintf(newMyFile,"%d \n",arr[i]);
                ++i;
        }
    }

	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}
