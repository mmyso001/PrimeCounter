/*
*Meekaeel Mysorewala
* Finds if a number is prime or not. If the number is 1 or 0, or the number is even it returns 0.
* Nothing is printed if zero is returned. Else it prints the prime number and returns 1.
 */




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

#define LIMIT 50000               
#define MASTER_PROCESS 0               


 
int isPrime(int id, long int n) 
{
    long int i;

   
    if(n <= 1) 
    {
        return 0;
    }

    
    for (i = 2; i * i <= n; i++) 
    {
        if (n % i == 0) 
        {
            return 0;
        }
    }

   
    printf("%d... %ld is prime\n", id, n);
    fflush(stdout);
    return 1;
}


int main(int argc, char** argv) {

    int count;            
    double elapsed_time;  
    int global_count;     
    long int i;
    int id;               
    int p;                


    
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
    MPI_Comm_size (MPI_COMM_WORLD, &p);

    
    MPI_Barrier (MPI_COMM_WORLD);
    elapsed_time = - MPI_Wtime();

    
    count = 0;

    
    for (i = (long int)id; i <= LIMIT; i += p) 
    {
        count += isPrime(id, i);
    }

   
    MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM, MASTER_PROCESS,
                MPI_COMM_WORLD);

    
    elapsed_time += MPI_Wtime();

    
    MPI_Finalize();

    
    if (!id) 
    {
        printf ("Execution time %8.6f\n", elapsed_time);
        fflush (stdout);
    }

    
    if (!id) 
    {
        printf("There are %d  solutions\n",
                     global_count);
    }

    return 0;
}
