#include "Matrix.h"
#include <cstdlib>
#include <thread>

Matrix::Matrix(const int N, const int M){
  this->N = N;
  this->M = M;
  this->matrix = new int*[N];
  for(int i = 0; i < N; i++){
    matrix[i] = new int[M];
  }
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      matrix[i][j] = rand() % 1000;
    }
  }
}

Matrix::Matrix(const Matrix& m){
  this->N = m.N;
  this->M = m.M;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      this->matrix[i][j] = m.matrix[i][j];
    }
  } 
}

Matrix::~Matrix(){
  for(int i = 0; i < N; i++){
    delete [] matrix[i];
  }
  delete matrix;
}

Matrix Matrix::operator+(const Matrix& m){
  Matrix result(m.N, m.M);
  for(int i = 0; i < m.N; i++){
    for(int j = 0; j < m.M; j++){
      result.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
    }
  }
  return result;
}

std::ostream& operator<< (std::ostream &out, const Matrix& m){
  for(int i = 0; i < m.N; i++){
    for(int j = 0; j < m.M; j++){
      out << m.matrix[i][j] << " ";
    }
    out << '\n';
  }
  return out;
}

int** Matrix::getMatrix() const{
  return this->matrix;
}

Matrix Matrix::parallel_adding(const Matrix& m, int threads){
  for(int i = 0; i < threads; i++){
    for(int j = i; j < i+threads; j++){
      for(int k = 0; k < m.M; k++){
        this->matrix[j][k] += m.matrix[j][k];
      }
    }
  }
}
