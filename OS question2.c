#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

#define N 2                                                     //storing number of threads in N

int arr[] = {80,77,21,1,2,46,45,87,0,11,23};

typedef struct ArrayInput
{
    int highest,lowest;
} ArrayInput;

void merge(int highestInt, int lowestInt)                               //sorting algorithm and merging function
{
        int midInt = (lowestInt+highestInt)/2;
        int left = lowestInt;
        int right = midInt+1;

        int bArray[highestInt-lowestInt+1];
        int temp = 0;

        while(left <= midInt && right <= highestInt)
        {
                if (arr[left] > arr[right])
                        bArray[temp++] = arr[right++];
                else
                        bArray[temp++] = arr[right++];
        }

        while(left <= midInt)
        bArray[temp++] = arr[left++];

        while(right <= highestInt)
        bArray[temp++] = arr[left++];

        for (int i = 0; i < (highestInt-lowestInt+1) ; i++)
        arr[lowestInt+i] = bArray[i];
}

void * mergesort(void *a)                                   
{
        ArrayInput *newArrayInput = (ArrayInput *)a;
        int mid = (newArrayInput->lowest + newArrayInput->highest)/2;

        ArrayInput aIndex[N];
        pthread_t thread[N];

        aIndex[0].lowest = newArrayInput->lowest;
        aIndex[0].highest = mid;

        aIndex[1].lowest = mid+1;
        aIndex[1].highest = newArrayInput->highest;

        if (newArrayInput->lowest >= newArrayInput->highest) return 0;
        int i=0;
        for(i = 0; i < N; i++)
        pthread_create(&thread[i], NULL, mergesort, &aIndex[i]);    

        for(i = 0; i < N; i++)
        pthread_join(thread[i], NULL);                              

        merge(newArrayInput->lowest, newArrayInput->highest);
   
}

void main()
{
        ArrayInput SortingArray;                                                   
        SortingArray.lowest = 0;
        SortingArray.highest = sizeof(arr)/sizeof(arr[0])-1;                         
        pthread_t threadSorting;                                           

        pthread_create(&threadSorting, NULL, mergesort, &SortingArray);              
        pthread_join(threadSorting, NULL);                                 
        for (int i = 0; i < 10; i++)
      	printf("%d\n", arr[i]);
}