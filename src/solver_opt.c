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

static void a_tb(int N, double *A, double *B, double *res)
{
	for (int i = 0; i < N; ++i) {
		register double *a_t = &A[i];
		for (int j = 0; j < N; ++j) {
			register double sum = 0.0;

			register double *pa_t = a_t;
			register double *pb = &B[j];

			for (int k = 0; k <= i; ++k) {
				sum += (*pa_t) * (*pb);
				pa_t += N;
				pb += N;
			}
			res[i * N + j] = sum;
		}
	}
}

static void ba(int N, double *A, double *B, double *res)
{
	for (int i = 0; i < N; ++i) {
		register double *b = &B[i * N];
		for (int j = 0; j < N; ++j) {
			register double sum = 0.0;

			register double *pb = b;
			register double *pa = &A[j];

			for (int k = 0; k <= j; ++k) {
				sum += (*pb) * (*pa);
				pa += N;
				++pb;
			}
			res[i * N + j] = sum;
		}
	}
}

static void mul_transpose(int N, double *A, double *B, double *res)
{
	for (int i = 0; i < N; ++i) {
		register double *a = &A[i * N];
		for (int j = 0; j < N; ++j) {
			register double sum = 0.0;

			register double *pa = a;
			register double *pb = &B[j * N];

			for (int k = 0; k < N; ++k) {
				sum += (*pb) * (*pa);
				++pa;
				++pb;
			}
			res[i * N + j] = sum;
		}
	}
}

double* my_solver(int N, double *A, double* B) {
	int n = N * N;

	double *a_tb_res = calloc(n, sizeof(*a_tb_res));
	double *ba_res = calloc(n, sizeof(*ba_res));
	double *sum = calloc(n, sizeof(*sum));

	a_tb(N, A, B, a_tb_res);
	ba(N, A, B, ba_res);
	add(n, a_tb_res, ba_res, sum);
	
	double *res = calloc(n, sizeof(*res));
	mul_transpose(N, sum, B, res);

	free(a_tb_res);
	free(ba_res);
	free(sum);

	return res;	
}
