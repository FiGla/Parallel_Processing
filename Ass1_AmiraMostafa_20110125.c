#include <stdio.h>
#include <stdlib.h>


 int ** multiply(int **arr1 , int **arr2,int **res , int row1, int col1 , int col2){
        int k ,i , j ;
        for (i=0 ; i < row1 ; ++i ){
            for ( j =0 ; j < col2; ++j){
                res[i][j] =0;
                for (k=0; k < col1 ; ++k)
                    res[i][j] +=(arr1[i][k]*arr2[k][j]);
            }

        }

    return res;
 }


int **add(int **arr1 , int **arr2,int **res , int row1, int col1 ){
        int i , j ;
        for (i=0 ; i < row1 ; ++i )
            for ( j =0 ; j < col1; ++j)
                res[i][j] =arr1[i][j] +arr2[i][j];
    return res;
 }


int **subtract(int **arr1 , int **arr2,int **res , int row1, int col1 ){
         int i , j ;
        for (i=0 ; i < row1 ; ++i )
            for ( j =0 ; j < col1; ++j)
                res[i][j] =arr1[i][j] -arr2[i][j];
    return res;
 }


void fill( int **arr , int row , int col ){
	int i ,j,x;
	for (i=0;i<row;i++){
		for (j=0; j < col ; ++j){
			scanf("%d",&x);
			arr[i][j] = x;
		}
	}
}


void print( int **arr , int row , int col ){
    int i , j ;
    for (i=0;i<row;i++){
		for (j=0; j <col ; ++j){
			printf("%d ",arr[i][j]);
		}
        printf("\n");
    }

}


main(){
	int row1 , col1,row2,col2 ,i,j;
	int **Mat1, **Mat2, **Mult, **sub , **ad;

	printf("Please enter the dimensions of the first matrix\n");
	scanf("%d",&row1 );
	scanf("%d",&col1);

	printf("Please enter the dimensions of the second matrix\n");
	scanf("%d",&row2);
	scanf("%d",&col2);

	Mat1 = (int**)malloc(row1*sizeof(int*));
    for (i=0;i<row1;i++)
        Mat1[i]=(int*)malloc(col1*sizeof (int));

    Mat2 = (int**)malloc(row2*sizeof(int*));
    for (i=0;i<row2;i++)
        Mat2[i]=(int*)malloc(col2*sizeof (int));

	printf("Please enter the first matrix: \n");
	fill (Mat1,row1,col1);

	printf("Please enter the second matrix: \n");
	fill (Mat2,row2,col2);

	printf("\nFirst matrix is: \n************************\n");
    print(Mat1,row1,col1);
    printf("************************\n\n\n");

	printf("second matrix is: \n************************\n");
    print(Mat2,row2,col2);
    printf("************************\n\n\n");

     if (col1 != row2)
        printf("These matrices can't be multiplied\n\n");
    else {
        Mult = (int**)malloc(row1*sizeof(int*));
        for (i=0;i<row1;i++)
            Mult[i]=(int*)malloc(col2*sizeof (int));

        multiply(Mat1,Mat2,Mult,row1,col1,col2);
        printf("The result of multiplication is:  \n************************\n");
        print(Mult,row1,col2);
        printf("************************\n\n\n");

    }

    if (row1 == row2 && col1 == col2){
        ad = (int**)malloc(row1*sizeof(int*));
        sub = (int**)malloc(row1*sizeof(int*));

        for (i=0;i<row1;i++){
            ad[i]=(int*)malloc(col1*sizeof (int));
            sub[i]=(int*)malloc(col1*sizeof (int));
        }

        ad = add(Mat1,Mat2,ad,row1,col1);
        sub = subtract(Mat1,Mat2,sub,row1,col1);
        printf("the result of addition is:   \n************************\n");
        print(ad,row1,col1);
        printf("************************\n\n\n");
        printf("the result of subtraction is:  \n************************\n");
        print(sub,row1,col1);
        printf("************************\n\n\n");
    }
    else
        printf("These matrices can't be added \n\n\nThese matrices can't be subtracted\n\n");


    printf("BYE BYE !! ");
    return 0;
}
