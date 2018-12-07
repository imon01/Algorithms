#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>


void string_permut(char*, size_t);

int permut(int n);
void swap( char*, int, int);
void __test_strings__(char*, char*);


int hash (char * str, int, int);
void rabin_karp( char*, char*);
void fill(  int * arr, size_t len);
void kmp(char* word, char * text, size_t len_w, size_t len_t);

void heaps_perm(char* s, size_t len);
void print_matrix(int**, int, int);
void rotate_matrix(int**, int, int);
void __test__rotate_matrix( int);

int main(int argc, char* argv[])
{

	__test_strings__(argv[1], argv[2]);

	return 0;
}



void print_matrix(int** A, int M, int N)
{

	printf("\n");
	for(int i = 0; i < M; i++)
	{
		for( int j = 0; j< N; j++)
			printf("%d ", A[i][j]);
		printf("\n");
	}
}


void rotate_matrix(int** A, int M, int N)
{

	assert(M==N);


	int layer = 0, i = 0, cache = 0;
	int n = N -1, MAX_LAYERS = N/2;
	int start = 0, end = N -1, offset = 0;


	while(  layer <  MAX_LAYERS )
	{
		start = layer;
		i = start;
		while( i < end)
		{
			cache = A[start][start + i];
			A[start][ start + i] = A[end-i][start];
			A[end-i][start]= A[end][end-i];	
			A[end][end-i]= A[start+i][end];
			A[start + i][end]= cache;	
			i++;	
		}
		end--;
		layer++;	
	}
}



void __test__rotate_matrix(int N)
{


	int ** A = (int**) malloc( sizeof(int*)*N);

	int i = 0, c = 1, j = 0;
	for(; i < N; i++)
	{
		A[i] = (int*) malloc( sizeof(int)*N);
		for(j = 0; j< N; j++)
			A[i][j] = c++;
	}


	print_matrix( A, N, N);


	rotate_matrix(A, N, N);


	print_matrix( A, N, N);
}


void __test_strings__(char *s, char* s2)
{
	rabin_karp( s2, s);
	kmp( s, s2, strlen(s), strlen(s2));	
}

void string_permut(char* str, size_t len);
{
	assert(len == strlen(str));

}


//All Permutations of string s of length len(s)
void heaps_perm(char* s, size_t len)
{
	assert(len==strlen(s));


	char cost[len];
	bzero(cost, len);

	int i = 0, perms =1;
	printf("%s\n", s);

	while( i < len  )	
	{
		if( cost[i] < i)
		{
			if( i %2 == 0)
			{
				swap(s, 0, i);
			}
			else
			{
				swap(s, cost[i], i);
			}
			printf("%s\n", s);
			cost[i]++;
			i = 0;
			perms++;
		}
		else
		{
			cost[i] = 0;
			i++;
		}
	}
	printf("\ntotal permutations: %d\n", perms);	
}

int permut(int n)
{
	int numer = 1, save_n = n;
	
	while(n)
	{
		numer *=n;
		n--;
	}

	printf("permuations: %d for n=%d\n", numer, save_n);
	return numer;
	
}

void swap(char *arr, int i,int k)
{
	char t = arr[i];
	arr[i] = arr[k];
	arr[k] = t;	
}




// KMP substring match alg
void kmp(char* word, char * text, size_t len_w, size_t len_t)
{
	printf("KMP algorithm\n");	


	int j = 0, k = 0, nP = 0;
	int T [len_t + 1];
	int P[len_t];


	fill(P, len_t);
	fill(T, len_t + 1);


	T[0] = -1;

	int start_index = 0;	
	while( j < len_t)
	{
		if( word[k] == text[j] )
		{
			j++;
			k++;
			
			if( k == len_w)
			{
				start_index = j - k;	
				P[nP] = j;
				nP++;
				break;	
				k = T[k];
	
			}
		}
		else
		{
			k = T[k];
			if( k < 0)
			{
				j++;
				k++;
			}
		}
	}	

	if( start_index)
	{
		printf("substring match: [%d, %lu]\n", start_index, start_index + len_w);
	
		len_w += start_index;
		while( start_index < len_w)
		{
			text[start_index++] = '-';
		}
		printf("%s\n", text);
	}
}



void fill(  int * arr, size_t len)
{
	while(len--)
	{
		arr[len] = 0;
	}
}



int hash (char * str, int i, int k)
{
	int h = 7;
	

	while( i < k)
	{
		h = h*31 + str[i];
		i++;
	}

	return h;
}	


void rabin_karp(char* str, char* pattern)
{
	printf("Rabin-Karm algorithm\n");
	size_t str_len= strlen(str);
	size_t pat_len = strlen(pattern);
	size_t k = str_len - pat_len ;
	int i = 0;
	char found = 0;
	int hash_pattern = hash(pattern, 0, pat_len);
	int iter_hash = 0;

	printf("\t target hash %d\n", hash_pattern);

	
	while( i < k)
	{
		iter_hash = hash( str, i, (i+pat_len));
		printf("\t\t scanned hash %d\n", iter_hash);
		if( iter_hash == hash_pattern)
		{	
			found = 1;
			break;
		}	
		i++;
	}

	if( found)
		printf("pattern found\n");

	else
		printf("pattern not found\n");
}	
