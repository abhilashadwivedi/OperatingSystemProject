#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<process.h>

int N = 2 ;                                               //storing number of threads in N

int arr[] = {10,9,8,7,6,5,4,3,2,1};

typedef struct Arraystruct
{
    int highest,lowest;
} ArrayInput;

void merge(int highestElement, int LowestElement)                               //sorting algorithm and merging function
{
        int midElement = (LowestElement+highestElement)/2;
        int left = LowestElement;
        int right = midElement+1;

        int bArray[highestElement-LowestElement+1];
        int temp = 0;

        while(left <= midElement && right <= highestElement)
        {
                if (arr[left] > arr[right])
                        bArray[temp++] = arr[right++];
                else
                        bArray[temp++] = arr[right++];
        }

        while(left <= midElement)
        bArray[temp++] = arr[left++];

        while(right <= highestElement)
        bArray[temp++] = arr[left++];

        for (int i = 0; i < (highestElement-LowestElement+1) ; i++)
        arr[LowestElement+i] = bArray[i];
}

void *mergesort(void *a)                                   
{
        ArrayInput *newArrayInput = (ArrayInput *)a;
        int mid = (newArrayInput->lowest + newArrayInput->highest)/2;
        
        ArrayInput aIndex[N];
        pthread_t thread[N];

        aIndex[0].lowest = newArrayInput->lowest;
        aIndex[0].highest = mid;

        aIndex[1].lowest = mid+1;
        aIndex[1].highest = newArrayInput->highest;

        if (newArrayInput->lowest >= newArrayInput->highest) 
            return 0;

        int i;
        for(i = 0; i < N; i++)
        pthread_create(&thread[i], NULL, mergesort, &aIndex[i]);    

        for(i = 0; i < N; i++)
        pthread_join(thread[i], NULL);                              

        merge(newArrayInput->highest, newArrayInput->lowest);
   
}

void main()
{
        ArrayInput SortingArray;                                                   
        SortingArray.lowest = 0;
        SortingArray.highest = sizeof(arr)/sizeof(arr[0])-1;
       //printf("%d\n",SortingArray.highest );                         
        pthread_t threadSorting;                                           

        pthread_create(&threadSorting, NULL,&mergesort, &SortingArray);              
        pthread_join(threadSorting, NULL);                                 
        for (int i = 0; i < 10; i++)
      	printf("%d\t", arr[i]);
    printf("completed");
    
}
