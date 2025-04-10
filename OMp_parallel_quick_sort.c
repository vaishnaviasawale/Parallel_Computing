#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include<omp.h>

// Function to swap two numbers
void swap(int* arr, int i, int j)
{
	int t = arr[i];
	arr[i] = arr[j];
	arr[j] = t;
}

void quicksort(int* arr, int start, int end)
{
	int pivot, index;

	// Base Case
	if (end <= 1)
    	return;

	// Pick pivot and swap with first
	// element Pivot is middle element
	pivot = arr[start + end / 2];
	swap(arr, start, start + end / 2);

	// Partitioning Steps
	index = start;

	// Iterate over the range [start, end]
	for (int i = start + 1; i < start + end; i++) {

    	// Swap if the element is less
    	// than the pivot element
    	if (arr[i] < pivot) {
        	index++;
        	swap(arr, i, index);
    	}
	}

	// Swap the pivot into place
	swap(arr, start, index);

	// Recursive Call for sorting
	// of quick sort function
	#pragma omp parallel sections
    	{
   		 #pragma omp section
        	{
            	// Evaluating the left half
   			 quicksort(arr, start, index - start);
   		 }
   		 #pragma omp section
        	{
            	// Evaluating the right half
   			 quicksort(arr, index + 1, start + end - index - 1);
   		 }
    	}   			 
}

// Driver Code
int main(int argc, char* argv[])
{
	int number_of_elements;
	int* data = NULL;
	FILE* file = NULL;
	double startTime, endTime;
   	 
	printf("Enter the size of array: ");
	 scanf("%d", &number_of_elements);
    
    data = (int*)malloc(number_of_elements * sizeof(int));

	srand(0);
	for (int i = 0; i < number_of_elements; i++)
	{
   	 data[i] = rand() % number_of_elements;
   }

	// Starts Timer
	startTime = omp_get_wtime();
    
	// Sorting array with quick sort for every
	// chunk as called by process
	quicksort(data, 0, number_of_elements);

	// Stop the timer
  	 endTime = omp_get_wtime();

	printf("Sorting completed in time: %f secs\n", endTime-startTime);
	// Opening the other file as taken form input
	// and writing it to the file and giving it
	// as the output
    
	file = fopen(argv[1], "w");

	if (file == NULL) {
    	printf("Error in opening file... \n");
    	exit(-1);
	}

	// Printing the value of array in the file
	for (int i = 0; i < number_of_elements; i++) {
    	fprintf(file, "%d\n", data[i]);
	}

	// Closing the file
	fclose(file);

	printf("Sorted array has been printed in the output text file\n");   
    
	return 0;
}
