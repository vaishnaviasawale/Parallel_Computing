#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int is_prime(int num) {
	if (num < 2) {
    	return 0;
	}
	for (int i = 2; i <= sqrt(num); i++) {
    	if (num % i == 0) {
        	return 0;
    	}
	}
	return 1;
}

int count_primes(int start, int end) {
	int count = 0;
	for (int num = start; num < end; num++) {
    	if (is_prime(num)) {
        	count++;
    	}
	}
	return count;
}

int main(int argc, char *argv[]) {
	int rank, size, n, chunk_size, start, end, local_count, total_count;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
    	printf("Enter the value of n: ");
    	fflush(stdout);
    	scanf("%d", &n);
	}

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	chunk_size = (n - 2) / size; // Each process will handle a chunk of numbers

	start = 2 + rank * chunk_size;
	end = (rank < size - 1) ? start + chunk_size : n;

	local_count = count_primes(start, end);

	MPI_Reduce(&local_count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
    	printf("Total number of primes up to %d is: %d\n", n, total_count);
	}

	MPI_Finalize();

	return 0;
}
