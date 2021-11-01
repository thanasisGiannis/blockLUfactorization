#include <iostream>
#include "blockLUfactorization.hpp"
#include <vector>

using namespace std;

int main() {
  int rows,cols;
  cout << "Please insert dimension of matrix " << endl;
  cout << "Number of rows: ";
  cin >> rows;
  cout << "Number of columns: ";
  cin >> cols;
  
  Dmatrix *A = new Dmatrix(rows,cols);
  A->createRandomMatrix();
  A->viewRandMatrix();
  

  delete A;
  return 0;
}

