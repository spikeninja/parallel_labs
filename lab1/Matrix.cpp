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
      matrix[i][j] = rand() % 80 + 10;
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
/*
void Matrix::parallel_addition(Matrix& result, const Matrix& m1, const Matrix& m2, int lower_bound, int upper_bound){
  for(size_t i = lower_bound; i < upper_bound; i++){
    for(int j = 0; j < result.M; j++){
      result.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
    }
  } 
}
*/




/*
auto range = size(first_vec) / threads;
  for(int i = 0; i < threads; i++){
    auto start = i * range;
    auto firstBegin = begin(second_vec) + start;
    auto secondBegin = begin(second_vec) + start;
    auto resultBegin = begin(parallel_result) + start;

    auto firstEnd = firstBegin + range;
    threads.emplace_back(
      [firstBegin, firstEnd, secondBegin, resultBegin]()
      {
        std::transform(firstBegin, firstEnd, secondBegin, resultBegin, plus<int>());
      }
    )
  } 

for(int i = 0; i < threads; i++){
    for(int j = i; j < i+threads; j++){
      for(int k = 0; k < m1.M; k++){
        this->matrix[j][k] += m.matrix[j][k];
      }
    }
  }

*/