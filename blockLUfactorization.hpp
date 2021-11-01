class matrix {        
  public:    
    matrix();
    int numRows();
    int numColumns();
    
  protected:
    int rows; // number of matrix rows
    int cols; // number of matrix columns
    void* data;
    void* L;
    void* U;
};



class Dmatrix: public matrix {        
  public:    
    Dmatrix(int trows, int tcols);
    ~Dmatrix();
    void createRandomMatrix();    
    void viewRandMatrix();

};







