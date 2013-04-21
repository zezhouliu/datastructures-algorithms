#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Prototypes
int print_matrices(int dim, int matrixarray1[dim][dim], int matrixarray2[dim][dim]);
int matrix_mult (int dim, int matrixarray1[dim][dim], int matrixarray2[dim][dim]);


int main (int argc, char* argv[])
{
    
    if (argc != 4) {
        printf ("Usage: ./strassen <0> <dimension> <inputfile> \n");
        return -1;
    }
    
    int dim = atoi(argv[3]);
    int row_counter = 0;
    int column_counter = 0;
    int buffer = 0;
    int matrixarray1[dim][dim];
    int matrixarray2[dim][dim];
    int flag = 1;
    
    // printf("%s \n", argv[3]);
    
    FILE* inFile = fopen(argv[3], "r");
    if (inFile == NULL)
    {
        printf("incorrect file \n");
    }
    
    while (!feof(inFile))
    {
        fscanf(inFile, "%d", &buffer);
        if (flag == 1)
            (matrixarray1)[row_counter][column_counter] = buffer;
        else
            (matrixarray2)[row_counter][column_counter] = buffer;
        if (column_counter < dim - 1)
        {
            column_counter++;
        }
        else if (row_counter < dim - 1)
        {
            column_counter = 0;
            row_counter++;
        }
        else
        {
            row_counter = 0;
            column_counter = 0;
            if (flag == 1)
                flag = 2;

            else
                break;
        }
    }
    
    print_matrices(dim, matrixarray1, matrixarray2);
    int matrix_result = matrix_mult(dim, matrixarray1, matrixarray2);
    
}

int matrix_mult (int dim, int matrixarray1[dim][dim], int matrixarray2[dim][dim])
{
    int matrix_result[dim][dim];
    
    int row,col,j,k,l;
    
    // Transpose matrix 1
    for (row = 0; row < dim; row++){
        for (col = 0; col < dim; col++){
            matrixarray2[row][col] = matrixarray2[col][row];
        }
    }

    print_matrices(dim, matrixarray1, matrixarray2);
    
    int c=0;
    do
    {
        for (row = 0; row < dim; row++)
        {
            for (col = 0; col < dim; col++)
            {
                    int suma = 0;
                    for (l = 0; l < dim; l++)
                            suma += matrixarray1[col][l]*matrixarray2[row][l];
                    printf ("%d", suma);
                    // matrix_result[j][k] = suma;
            }
         }
    c++;
    } while (c < dim);
    
    return 0;

}


int print_matrices(int dim, int matrixarray1[dim][dim], int matrixarray2[dim][dim])
{
    int row, column;
    
    printf("Matrix 1: \n");
    for (row = 0; row < (dim); row++)
    {   
        for (column = 0; column < dim; column++)
        {
            printf("%d ", matrixarray1[row][column]);
            if (column == dim - 1)
            {
                printf ("\n");
            }
        }
    }
    
    printf("\n Matrix 2: \n");
    
    for (row = 0; row < (dim); row++)
    {   
        for (column = 0; column < dim; column++)
        {
            printf("%d ", matrixarray2[row][column]);
            if (column == dim - 1)
            {
                printf ("\n");
            }
        }
    }
    
    return 0;
}

