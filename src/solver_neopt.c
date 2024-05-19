/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"

static void add(int n, double *A, double *B, double *res)
{
	for (int i = 0; i < n; ++i)
		res[i] = A[i] + B[i];
}

static void transpose_upper(int N, double *A, double *res)
{
	for (int i = 0; i < N; ++i)
		for (int j = i; j < N; ++j)
			res[j * N + i] = A[i * N + j];
}

static void transpose_simple(int N, double *A, double *res)
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			res[j * N + i] = A[i * N + j];
}

static void mul_lower(int N, double *A, double *B, double *res)
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k <= i; ++k)
				res[i * N + j] += A[i * N + k] * B[k * N + j]; 
}

static void mul_upper(int N, double *A, double *B, double *res)
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k <= j; ++k)
				res[i * N + j] += A[i * N + k] * B[k * N + j];
}

static void mul_simple(int N, double *A, double *B, double *res)
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
				res[i * N + j] += A[i * N + k] * B[k * N + j];
}

double* my_solver(int N, double *A, double* B) {
	int n = N * N;
	double *a_t = calloc(n, sizeof(*a_t));
	double *b_t = calloc(n, sizeof(*b_t));

	transpose_upper(N, A, a_t);
	transpose_simple(N, B, b_t);

	double *a_tb = calloc(n, sizeof(*a_tb));
	double *ba = calloc(n, sizeof(*ba));
	double *sum = calloc(n, sizeof(*sum));

	mul_lower(N, a_t, B, a_tb);
	mul_upper(N, B, A, ba);
	add(n, a_tb, ba, sum);

	double *res = calloc(n, sizeof(*res));
	mul_simple(N, sum, b_t, res);

	free(a_t);
	free(b_t);
	free(a_tb);
	free(ba);
	free(sum);

	return res;
}
