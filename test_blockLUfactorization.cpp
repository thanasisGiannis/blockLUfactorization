#include <iostream>
#include "blockLUfactorization.hpp"
#include "blockLUfactorization.tcc"
#include <vector>

#include <thread>
#include <chrono>

using namespace std;
using std::this_thread::sleep_for;
using namespace std::chrono_literals;

int main() {
  int rows,cols,b;
  cout << "Please insert dimension of matrix " << endl;
  cout << "Number of rows: ";
  cin >> rows;
  cout << "Number of columns: ";
  cin >> cols;

  cout << "Block size: ";
  cin >> b;

	float *dataMat = (float*)malloc(rows*cols*sizeof(float));
  matrix<float> *A = new matrix<float>(rows,cols,dataMat,rows);
	A->printMatrix('A');
	A->LU();
	sleep_for(300ms);
  A->printMatrix('B');



/*
  A->createRandomMatrix();
  A->viewRandMatrix();
  A->LU_blas3(b);
*/

	free(dataMat);
  delete A;

  return 0;
}

