#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>

int main()
{
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the elements: \n");
    for(int i = 0; i < n; i++)
    {
   	 scanf("%d",&arr[i]);
    }
    
    int max = INT_MIN, i;
    #pragma omp parallel for private(i) shared(max)
    for(i = 0; i < n; i++)
    {
   	 int sum = 0;
   	 for(int j = i; j < n; j++)
   	 {
   		 sum = sum + arr[j];
   		 
   		 #pragma omp critical
   		 if(sum > max)
   		 {
   			 max = sum;
   		 }
   	 }
    }
    printf("The maximum sum of a contiguous sub-array is: %d\n", max);
    return 0;
}
