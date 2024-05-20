/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <cblas.h>

double* my_solver(int N, double *A, double *B) {
	int n = N * N;

	double *a_tb = calloc(n, sizeof(*a_tb));
	cblas_dcopy(n, B, 1, a_tb, 1);
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, a_tb, N);

	double *ba = calloc(n, sizeof(*ba));
	cblas_dcopy(n, B, 1, ba, 1);
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, ba, N);

	double *sum = calloc(n, sizeof(*sum));
	cblas_dcopy(n, ba, 1, sum, 1);
	cblas_daxpy(n, 1, a_tb, 1, sum, 1);

	double *res = calloc(n, sizeof(*res));
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1, sum, N, B, N, 0, res, N);

	free(a_tb);
	free(ba);
	free(sum);

	return res;
}
