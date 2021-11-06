template <typename D>
class matrix {        
  public:  
    matrix(int,int, D*,int);//{cout << "Hello" << endl;}
    ~matrix(){}
    void LU();
    void LU(int);
    void printMatrix(char );
  private:
    int  num_rows; // number of matrix rows
    int  num_cols; // number of matrix columns
    D   *Mat;
    int  ldMat;
    
    void createRandMatrix();
};










