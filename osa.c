#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<assert.h>
#include<stdbool.h>


int min_arg2(int, int);
int min_arg3(int, int, int);

void fill(int*, int);
void fill2( int**, size_t, size_t);

void __test_fill__( int *v, int len);
int OSA(char* , char* , size_t, size_t);
void __test_OSA__(char*, char*, size_t, size_t);


void display(int * arr, size_t len);
void display2( int** arr, size_t m, size_t n);


int main(int c, char* argv[])
{

	printf("running __test_OSA__\n");
	__test_OSA__( argv[1], argv[2], strlen(argv[1]), strlen(argv[2]));
	
	return 1;
}

/* 

Optimal string alignment distance.
Based off Wikipedia, Wagner-Ficher DP algorithm

*/

void __test_OSA__(char* a, char* b, size_t len_a, size_t len_b)
{
	int i = OSA(a, b, len_a, len_b);
}

int OSA(char* a, char* b, size_t len_a, size_t len_b)
{

	assert( len_a == strlen(a));
	assert( len_b == strlen(b));

	
	int i= 1, j = 1, cost = 0 ;


	
	int ** d = (int**) malloc( sizeof(int*)*(len_a+1));
	
	for(i = 0; i <= len_a; i++)
	{
		d[i] = (int*) malloc( sizeof(int)*len_b+1);
		fill(d[i], len_b+1);
	//	__test_fill__(d[i], len_b+1);
	}


	for( i = 0; i <= len_a; i++)
		d[i][0] = i;

	for( j = 0; j <= len_b; j++)
		d[0][j] = j;
		

	for( i = 1; i <= len_a; i++)
	{
		for(j = 1; j <= len_b;j++)
		{
			if( a[i]==b[j] )
			{
				cost = 0;
			}
			else
			{
				cost = 1;
			}
			d[i][j] = min_arg3( d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1] + cost);	
			
			if(  (i > 1 && j > 1) && ( a[i]==b[j-1] && a[i-1]==b[j]) )
			{
				d[i][j] = min_arg2( d[i][j], d[i-2][j-2] + cost);
			}
		}
	}


	display2(d, len_a+1, len_b+1);
	
	printf("%d\n", d[len_a-1][len_b-1]); 


	for(i = 0; i < len_a+1; i++)
	{
		free(d[i] );
	}
	free(d);
}

void display2( int** arr, size_t m, size_t n)
{
	int i, j;
	for(i = 0; i < m; i++)
	{
		for(j = 0; j< n; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");	
	}
}


void display(int * arr, size_t len)
{

	printf("object @: %p\n", arr);
	while( len--)
	{
		printf("%d ", *arr++);
	}
	printf("\n");
}


void fill2( int** matrix, size_t m, size_t n)
{
	int i = 0, j =0;
	for(; i < m; i++)
	{
		for(; j< n; j++)
		{
			matrix[i][j] = 0;
		}
	}
}


void fill( int *vector, int len)
{
	
	int i = 0;
	
	while(len)
	{
		*vector = 0;
		vector++;
		len--;
	}
}

void __test_fill__( int *vector, int len)
{
	int i = 0;
	while(len)
	{
		if( *vector != 0)
		{
			printf("Fail: __test_fill__  vect[%d]=%d should be %d\n",i, *vector, i);
			goto ERROR;

		}
		len--;
		vector++;
	}
	
	printf("Pass: __test_fill__\n");
	return;

	ERROR:
		return;
}

int min_arg2( int a, int b)
{
	if( a <= b)
		return a;

	return b;
}

int min_arg3( int a, int b, int c)
{

	if( a <= b && a <= c)
		return a;

	if( b <= a && b <= c)
		return b;

	return c;
}

