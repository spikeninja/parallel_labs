#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix{
  private:
    int **matrix;
    int N, M;

  public:
    Matrix(const int N, const int M);
    Matrix(const Matrix& m);
    ~Matrix();

    int **getMatrix() const;

    Matrix operator+(const Matrix& m);

    friend std::ostream& operator<<(std::ostream &out, const Matrix& m);

    void parallel_addition(Matrix& result, Matrix& m1, Matrix& m2, int threads, int lower_bound, int upper_bound);
};

#endif
