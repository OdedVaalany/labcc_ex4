// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims {
    int rows, cols;
} matrix_dims;

class Matrix {
 public:
  Matrix (int row, int cols);
  Matrix ();
  Matrix (const Matrix &mat);
  ~Matrix ();
  int get_rows () const;
  int get_cols () const;
  Matrix& transpose ();
  float operator() (int row, int col) const;
  float &operator() (int row, int col);
  Matrix &vectorize ();
  void plain_print () const;
  float norm () const;
  Matrix &dot (Matrix &m);
  Matrix &operator= (const Matrix &b);
  friend Matrix &operator+ (const Matrix &a, const Matrix &b);
  friend Matrix &operator* (const Matrix &a, const Matrix &b);
  friend Matrix &operator* (const Matrix &a, const float &c);
  friend Matrix &operator* (const float &c, const Matrix &a);
  Matrix &operator+= (const Matrix &b);
  float &operator[] (const int &i);
  float operator[] (const int &i) const;
  friend std::ostream &operator<< (std::ostream &pr, const Matrix &a);
  friend std::ifstream &operator>> (std::ifstream &re, Matrix &a);
 private:
  float *val;
  matrix_dims dim = {0, 0};
};

#endif //MATRIX_H