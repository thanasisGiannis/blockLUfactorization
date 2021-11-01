#include <iostream>
#include "blockLUfactorization.hpp"
#include <cstdlib>
using namespace std;


matrix::matrix(){}
/*
matrix::matrix(int trows, int tcols){
    	this->rows = trows;
    	this->cols = tcols;
}
*/
int matrix::numRows(){
	return this->rows;
}

int matrix::numColumns(){
	return this->cols;
}


void Dmatrix::createRandomMatrix(){
	int r = rows;
	int c = cols;
	double *d = (double*) data;
	for(int j=0; j<r*c; j++)
		d[j] = ((rand()%100)/100.0)-0.5;
}

void Dmatrix::viewRandMatrix(){
	double *d = (double*) data;
	for(int j=0; j<5; j++)
		cout << d[j] << endl;
}

Dmatrix::~Dmatrix(){
   	free(this->data);
}

Dmatrix::Dmatrix(int trows, int tcols){
		this->rows = trows;
    	this->cols = tcols;
    	this->data = (void*)malloc(trows*tcols*sizeof(double));
}


