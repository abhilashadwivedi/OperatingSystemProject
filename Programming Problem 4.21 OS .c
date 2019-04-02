#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void main(int argc,char* argv[])
{
	printf("\t\t\tA Multithreading Program !! \n");
	while(argc<=1)
	{
		printf("\t\t\tNumber of arguments entered is incorrect!!\n");
		printf("\t\t\tEnter Correct Set of input Next Time!!");
		exit(-1);
	}
	
}
