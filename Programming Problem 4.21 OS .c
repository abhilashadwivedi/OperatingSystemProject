#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<process.h>


void *max_func(void *max);
void *min_func(void *min);
void *avg_func(void *avg);


int maximum , minimum;
double average;

typedef struct dataTaken
{
    int size;
    int *values;
}dataTaken;
void main(int argc,char* argv[])
{
	printf("\t\t\tA Multithreading Program !! \n");
	while(argc<=1)
	{
		printf("\t\t\tNumber of arguments entered is incorrect!!\n");
		printf("\t\t\tEnter Correct Set of input Next Time!!");
		exit(-1);
	}
	int newArray[argc-1];
	for(int i=0 ; i<(argc-1);i++)
	{
		newArray[i]=atoi(argv[i+1]); //Converting string argument into int 
	}

	dataTaken datain={argc-1 , newArray};

	pthread_t workerThread1 , workerThread2 , workerThread3;
    int  t_Create1, t_Create2, t_Create3;
 
    printf("Running Program: %s\n", argv[0]);
    
 
    t_Create1 = pthread_create(&workerThread1, NULL, &avg_func, (void *) &datain);
    if(t_Create1!=0)
    {
        printf("Thread 1 is not created.");
        exit(-1);
    }
 
    t_Create2 = pthread_create(&workerThread2, NULL, &min_func, (void *) &datain);
    if(t_Create2!=0)
    {
        printf("Thread 2 is not created.");
        exit(-1);
    }
     
    t_Create3 = pthread_create(&workerThread3, NULL, &max_func, (void *) &datain);
    if(t_Create3!=0)
    {
        printf("Thread 3 is not created.");
        exit(-1);
    }
    pthread_join(workerThread1, NULL);
    pthread_join(workerThread2, NULL);
    pthread_join(workerThread3, NULL);
 	
 	printf("The average of all Data Input:  %g\n", average);
    printf("The minimum of all Data Input:  %d\n", minimum);
    printf("The maximum of all Data Input:  %d\n", maximum);
}




void *max_func(void *max)
{
    dataTaken * newSet;
    newSet = (dataTaken *) max;
    
    int sizeNew = newSet->size;
    
    maximum = newSet->values[0];
    
    for(int i = 1; i < sizeNew; i++)
    {
        if(maximum < newSet->values[i])
        {
            maximum = newSet->values[i];
        }
    }
}

void *min_func(void *min)
{
    dataTaken * newSet;
    newSet = (dataTaken *) min;
    
    int sizeNew = newSet->size;
    
    minimum = (newSet->values[0]);
    for(int i = 1; i < sizeNew; i++)
    {
        if(minimum > (newSet->values[i]))
        {
            minimum = (newSet->values[i]);
        }
    }
}
void *avg_func(void *avg)
{
    dataTaken * newSet;
    newSet = (dataTaken *) avg;
    
    int sizeNew = newSet->size;

    
    for(int i = 0; i < sizeNew; i++)
    {
        average += (newSet->values[i]);    
    }                               
        average = (int)(average / sizeNew);          
}
