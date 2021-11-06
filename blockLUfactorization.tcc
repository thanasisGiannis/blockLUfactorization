#include <iostream>
#include <math.h>
#include "lapack_wrapper.hpp"

using namespace std;

template <typename D>
void matrix<D>::printMatrix(char S){

		int n = this->num_rows;
		int m = this->num_cols;
		D *A = this->Mat;
		int ldA = this->ldMat;
		cout << " ====================== " << endl;
		for(int i=0; i<m; i++){
			for(int j=0; j<n; j++){
				cout << S <<"(" << j+1 << "," << i+1 << ") = " << A[j+i*ldA] << endl;
			}
		}

}

template <typename D>
matrix<D>::matrix(int nRows,int nCols, D *fMat,int ldfMat){
		this->num_rows = nRows;
		this->num_cols = nCols;
		this->Mat      = fMat;
		this->ldMat    = ldfMat;

		this->createRandMatrix();
}

template <typename D>
void matrix<D>::createRandMatrix(){

		D  *A   = this->Mat;
		int ldA = this->ldMat;
		int nr  = this->num_rows;
		int nc  = this->num_cols;

		for(int i=0; i<nc; i++){
			for(int j=0;j<nr;j++){
					if(i==j){
						A[j+i*ldA] = (D)(10.0*max(nr,nc)*(0.5*(rand()%100)/100.0-0.5));
					}else{
						A[j+i*ldA] = (D)(0.5*(rand()%100)/100.0-0.5);
					}
			}
		}

}

template <typename D>
void matrix<D>::LU(){
	// at this point find a good blocking size
	this->LU(5);
}
template <typename D>
void matrix<D>::LU(int b){

		D  *A   = this->Mat;
		int ldA = this->ldMat;
		int nr  = this->num_rows;
		int nc  = this->num_cols;

		long long int *ipiv = (long long int*)malloc(b*sizeof(long long int));
		int info = -1;

		D one       = (D) 1.0;
		D minus_one = (D)-1.0;
		D zero      = (D) 0.0;
		int iters = min(ceil(nr/b),ceil(nc/b));
		int maxNr = ceil(nr/b);
		int maxNc = ceil(nc/b);

		cout << iters << " " << maxNr << " " << maxNc << " " << endl;
		for(int i=0; i<iters; i++){
	
			// update diagonal elements
			D *AII = (D*)(&A[i*b+i*b*ldA]);
			for(int j=0; j<i;j++){
					//AII = AII - LIJ  x UJI;
					D *LIJ = &A[i*b+j*b*ldA];
					D *UJI = &A[j*b+i*b*ldA];
					if(i==iters-1)
 						gemm('N','N', b+nr%b, b+nc%b, b, minus_one, LIJ,ldA, UJI, ldA, one,AII, ldA);	
					else
	 					gemm('N','N', b, b, b, minus_one, LIJ,ldA, UJI, ldA, one,AII, ldA);
			}
			// lu(A_)
			if(i==iters-1)
				getrf(b+nr%b, b+nc%b, AII, ldA, ipiv, info);
			else
				getrf(b, b, AII, ldA, ipiv, info);
			

			// update row wise
			// AJI = AJI - LJK x UKI
			for(int j=i+1; j<maxNr;j++){
					D *AJI = (D*)(&A[b*j+b*i*ldA]);
					for(int k=0;k<i;k++){
							D *LJK = &A[j*b+k*b*ldA];
							D *UKI = &A[k*b+i*b*ldA];
							
							if(j==maxNr-1)
			 					gemm('N','N', b+nr%b, b, b, minus_one, LJK, ldA, UKI, ldA, one, AJI,ldA);													
							else
			 					gemm('N','N', b, b, b, minus_one, LJK, ldA, UKI, ldA, one, AJI, ldA);
					}
					//AJI = AJI/UII;

					D *UII = (D*)(&A[i*b+i*b*ldA]);
					if(j==maxNr-1)
						trsm('R','U','N','N',b+nr%b,b,one,UII,ldA, AJI,ldA);
					else
						trsm('R','U','N','N',b,b,one,UII,ldA, AJI,ldA);
			}

			// update col wise
			// AIJ = AIJ - LIK x UKJ
			for(int j=i+1; j<maxNc;j++){
					D *AIJ = (D*)(&A[b*i+b*j*ldA]);
					for(int k=0;k<i;k++){
							D *LIK = &A[i*b+k*b*ldA];
							D *UKJ = &A[k*b+j*b*ldA];
							
							if(j==maxNr-1)
			 					gemm('N','N', b, b+nc%b, b, minus_one, LIK, ldA, UKJ, ldA, one, AIJ, ldA);
							else
			 					gemm('N','N', b, b, b, minus_one, LIK, ldA, UKJ, ldA, one, AIJ, ldA);
					}
					//AJI = AJI/UII;

					D *LII = (D*)(&A[i*b+i*b*ldA]);
					if(j==maxNr-1)
						trsm('L','L','N','U',b,b+nc%b,one,LII,ldA, AIJ,ldA);
					else
						trsm('L','L','N','U',b,b,one,LII,ldA, AIJ,ldA);
			}
	

		}	
	  
		free(ipiv);
}







#if 0

					cout << "========="<< endl;
					cout << "LIJ" << endl;
					for(int ii=0;ii<b;ii++){
							for(int jj=0;jj<b;jj++){
								cout << LIJ[ii+jj*ldA] << " ";
							}
							cout << endl;
					}

					cout << "UJI" << endl;
					for(int ii=0;ii<b;ii++){
							for(int jj=0;jj<b;jj++){
								cout << UJI[ii+jj*ldA] << " ";
							}
							cout << endl;
					}

					cout << "AIJ" << endl;
					for(int ii=0;ii<b;ii++){
							for(int jj=0;jj<b;jj++){
								cout << A_[ii+jj*ldA] << " ";
							}
							cout << endl;
					}

					cout << "AIJ" << endl;
					for(int ii=0;ii<b;ii++){
							for(int jj=0;jj<b;jj++){
								cout << A_[ii+jj*ldA] << " ";
							}
							cout << endl;
					}

#endif

















