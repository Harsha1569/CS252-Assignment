#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

// variables containing statistical values are defined globally
int min;
int max;
float average;
float median;
float var;
float std_dev;

int n;

// Thread to calculate minimum value among given list of numbers
void *Minimum(void *arg)
{
	int i;
	int *e = (int *)arg;
	min = *e;
	for (i = 0; i < n; i++)
	{
		if (e[i] < min)
		{
			min = *(e + i);
		}
	}
	pthread_exit(NULL);
}

// Thread to calculate maximum value among given list of numbers
void *Maximum(void *arg)
{
	int i;
	int *e = (int *)arg;
	max = *e;
	for (i = 0; i < n; i++)
	{
		if (e[i] > max)
		{
			max = *(e + i);
		}
	}
	pthread_exit(NULL);
}

// Thread to calculate average & standard deviation values among given list of numbers
void *Average(void *arg)
{
	int i;
	int *e = (int *)arg;
	for (i = 0; i < n; i++)
	{
		average += e[i];
	}
	average = average / n;
	for (i = 0; i < n; i++)
	{
		var += pow((e[i] - average), 2);
	}

	var = var / n;

	/* square root of variance is SD */
	std_dev = sqrt(var);
	pthread_exit(NULL);
}

// Thread to calculate median value among given list of numbers
void *Median(void *arg)
{
	int i;
	int j;
	int temp;
	int *e = (int *)arg;
	/* sort the given inputs to find median */
	for (i = 0; i < n - 1; i++)
	{
		for (j = i; j < n; j++)
		{
			if (e[i] > e[j])
			{
				temp = e[i];
				e[i] = e[j];
				e[j] = temp;
			}
		}
	}

	/* calculate the median */
	if ((n + 1) % 2 == 0)
	{
		median = e[((n + 1) / 2) - 1];
	}
	else
	{
		median = ((float)e[((n + 1) / 2) - 1] + e[((n + 2) / 2) - 1]) / 2;
	}
	pthread_exit(NULL);
}

int main()
{
	int i;
	printf("Enter Number of Elements \n"); // Taking input from command line for number of elements
	scanf("%d", &n);
	printf("Enter Elements \n");
	int *arg = (int *)malloc(sizeof(int) * n); // Taking input from command line for the element and dynamically allocating memory to store them 
	for (i = 0; i < n; i++)
	{
		scanf("%d", (arg + i));
	}
	// Creating 4 objects of worker threads
	pthread_t threadHandle[4]; 
	// Creating threads
	pthread_create(&threadHandle[0], NULL, Minimum, (void *)arg);
	pthread_create(&threadHandle[1], NULL, Maximum, (void *)arg);
	pthread_create(&threadHandle[2], NULL, Average, (void *)arg);
	pthread_create(&threadHandle[3], NULL, Median, (void *)arg);
	for (i = 0; i < 4; i++)
	{
		pthread_join(threadHandle[i], NULL);
	}
	printf("\nThe average value is %f\nThe minimum value is %d\nThe maximum value is %d\nThe median value is %f\nThe standard deviation value is %f\n", average, min, max, median, std_dev);
}
