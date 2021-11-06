#include "lapack_wrapper.hpp"
#include <mkl.h>
#include <iostream>
using namespace std;

void getrf(int M, int N, double *A, int LDA, long long int *IPIV, int &INFO){

		MKL_INT ldA  = LDA;
		MKL_INT m    = M;
		MKL_INT n    = N;
		MKL_INT info = INFO;

		dgetrf_(&m,&n,A,&ldA,IPIV,&info);
		INFO = info;

}

void getrf(int M, int N, float *A, int LDA, long long int *IPIV, int &INFO){

		MKL_INT ldA  = LDA;
		MKL_INT m    = M;
		MKL_INT n    = N;
		MKL_INT info = INFO;

		sgetrf_(&m,&n,A,&ldA,IPIV,&info);
		INFO = info;
}

void gemm(char TA, char TB, int M, int N, int K, double alpha,
		double *A,int LDA, double *B, int LDB, double beta, double *C, int LDC){
	MKL_INT m = M;
	MKL_INT n = N;
	MKL_INT k = K;

	MKL_INT ldA = LDA;
	MKL_INT ldB = LDB;
	MKL_INT ldC = LDC;

	CBLAS_TRANSPOSE tA,tB; 
	if(TA == 'N')
		tA = CblasNoTrans;
	else
		tA = CblasTrans;

	if(TB == 'N')
		tB = CblasNoTrans;
	else
		tB = CblasTrans;

	cblas_dgemm(CblasColMajor,tA,tB,m,n,k,alpha,A,ldA,B,ldB,beta,C,ldC);	

}	

void gemm(char TA, char TB, int M, int N, int K, float alpha,
		float *A,int LDA, float *B, int LDB, float beta, float *C, int LDC){

	MKL_INT m = M;
	MKL_INT n = N;
	MKL_INT k = K;

	MKL_INT ldA = LDA;
	MKL_INT ldB = LDB;
	MKL_INT ldC = LDC;

	CBLAS_TRANSPOSE tA,tB; 
	if(TA == 'N')
		tA = CblasNoTrans;
	else
		tA = CblasTrans;

	if(TB == 'N')
		tB = CblasNoTrans;
	else
		tB = CblasTrans;

	cblas_sgemm(CblasColMajor,tA,tB,m,n,k,alpha,A,ldA,B,ldB,beta,C,ldC);	


}	


void trsm(char SIDE,char UPLO,char TRANSA,char DIAG,int M,int N,float alpha,
					float *A,int LDA, float *B,int LDB){

		MKL_INT m   = M;
		MKL_INT n   = N;
		MKL_INT ldA = LDA;
		MKL_INT ldB = LDB;

		strsm(&SIDE,&UPLO,&TRANSA,&DIAG, &m, &n, &alpha, A, &ldA, B, &ldB);
}	




