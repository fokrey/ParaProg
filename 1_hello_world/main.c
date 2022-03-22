#include <mpi/mpi.h>

int main (int argc, char *argv[]) {
    int commsize = 0, my_rank = 0;

    MPI_Init (&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

    printf ("Communicator size = %d; My rank = %d\n", commsize, my_rank);

    MPI_Finalize ();
}