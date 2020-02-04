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

    Matrix parallel_adding(const Matrix& m1, int threads);
};

#endif
