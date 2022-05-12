//
// Created by עודד ועלני on 11/05/2022.
//

#include "Matrix.h"
#include "cmath"
#include <fstream>
#define LENGTH_ERROR_MSG "The matrix isn't in the same dimension"
#define RUNTIME_ERROR_MSG "Invalid input"
#define PRINT_LOWER_VALUE 0.1

Matrix::Matrix (int row, int cols)
{
  val = new float[row * cols];
  for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < cols; ++j)
        {
          val[j + (i * cols)] = 0;
        }
    }
  dim.cols = cols;
  dim.rows = row;
}

Matrix::Matrix ()
{
  dim.cols =1;
  dim.rows = 1;
  val = new (std::nothrow) float[1];
  val[0] = 0;
}

Matrix::Matrix (const Matrix &mat)
{
  val = new float[mat.get_rows () * mat.get_cols ()];
  dim.rows = mat.get_rows ();
  dim.cols = mat.get_cols ();
  for (int i = 0; i < get_rows () * get_cols (); i++)
    {
      val[i] = mat[i];
    }
}

Matrix::~Matrix ()
{
  delete[] val;
}

int Matrix::get_rows () const
{
  return dim.rows;
}

int Matrix::get_cols () const
{
  return dim.cols;
}

Matrix &Matrix::transpose ()
{
  int tdim = dim.cols;
  dim.cols = dim.rows;
  dim.rows = tdim;
  float *temp = new float[get_cols () * get_rows ()];
  for (int i = 0; i < get_rows (); ++i)
    {
      for (int j = 0; j < get_cols (); ++j)
        {
          temp[i + (j * get_rows ())] = val[j + (i * get_cols ())];
        }
    }
  for (int i = 0; i < get_cols () * get_rows (); ++i)
    {
      val[i] = temp[i];
    }
    delete[] temp;
    return (*this);
}

Matrix &Matrix::vectorize ()
{
  dim.rows *= dim.cols;
  dim.cols = 1;
  return (*this);
}

void Matrix::plain_print () const
{
  for (int i = 0; i < dim.rows; ++i)
    {
      for (int j = 0; j < dim.cols; ++j)
        {
          std::cout << val[j + (i * dim.cols)] << " ";
        }
      std::cout << std::endl;
    }
}

Matrix &Matrix::dot (Matrix &m)
{
  if (m.get_rows () != dim.rows || dim.cols != m.get_cols ())
    {
      throw std::out_of_range ("The matrix dosen't have the same dimensions");
    }
  Matrix *temp = new Matrix (m);
  for (int i = 0; i < dim.rows; ++i)
    {
      for (int j = 0; j < dim.cols; ++j)
        {
          (*temp) (i, j) *= val[j + (i * dim.cols)];
        }
    }
  return (*temp);
}

float Matrix::norm () const
{
  double sum = 0;
  for (int i = 0; i < dim.rows; ++i)
    {
      for (int j = 0; j < dim.cols; ++j)
        {
          sum += (*this) (i, j) * (*this) (i, j);
        }
    }
  return (float) std::sqrt (sum);
}

float Matrix::operator() (int row, int col) const
{
  if (row < 0 || row >= dim.rows || col < 0 || col >= dim.cols)
    {
      throw std::out_of_range ("index out of range");
    }
  return val[col + (dim.cols * row)];
}

float &Matrix::operator() (int row, int col)
{
  if (row < 0 || row >= dim.rows || col < 0 || col >= dim.cols)
    {
      throw std::out_of_range ("index out of range");
    }
  return val[col + (dim.cols * row)];
}

Matrix &operator+ (const Matrix &a, const Matrix &b)
{
  if (b.get_rows () != a.get_rows () || a.get_cols () != b.get_cols ())
    {
      throw std::length_error ("The matrix dosen't have the same dimensions");
    }
  Matrix *temp = new Matrix (b);
  for (int i = 0; i < a.get_rows (); ++i)
    {
      for (int j = 0; j < a.get_cols (); ++j)
        {
          (*temp) (i, j) += a (i, j);
        }
    }
  return *temp;
}

Matrix &operator* (const Matrix &a, const Matrix &b)
{
  if (a.get_cols () != b.get_rows ())
    {
      throw std::length_error ("The cols and"
                               " rows of the matrix need to be the same");
    }
  Matrix *temp = new Matrix (a.get_rows (), b.get_cols ());
  for (int i = 0; i < temp->get_rows (); ++i)
    {
      for (int j = 0; j < temp->get_cols (); ++j)
        {
          for (int k = 0; k < b.get_rows (); ++k)
            {
              (*temp) (i, j) += a (i, k) * b (k, j);
            }
        }
    }
  return *temp;
}

Matrix &operator* (const Matrix &a, const float &c)
{
  Matrix *temp = new Matrix (a);
  for (int i = 0; i < temp->get_rows (); ++i)
    {
      for (int j = 0; j < temp->get_cols (); ++j)
        {

          (*temp) (i, j) *= c;
        }
    }
  return (*temp);
}

Matrix &operator* (const float &c, const Matrix &a)
{
  Matrix *temp = new Matrix (a);
  for (int i = 0; i < temp->get_rows (); ++i)
    {
      for (int j = 0; j < temp->get_cols (); ++j)
        {

          (*temp) (i, j) *= c;
        }
    }
  return (*temp);
}

Matrix &Matrix::operator+= (const Matrix &b)
{
  if (b.get_rows () != get_rows () || get_cols () != b.get_cols ())
    {
      throw std::length_error (LENGTH_ERROR_MSG);
    }
  for (int i = 0; i < get_rows (); ++i)
    {
      for (int j = 0; j < get_cols (); ++j)
        {
          (*this) (i, j) += b (i, j);
        }
    }
  return *this;
}

float &Matrix::operator[] (const int &i)
{
  if (i < 0 || i >= dim.rows * dim.cols)
    {
      throw std::out_of_range ("Index out of range");
    }
  return val[i];
}

float Matrix::operator[] (const int &i) const
{
  if (i < 0 || i >= dim.rows * dim.cols)
    {
      throw std::out_of_range ("Index out of range");
    }
  return val[i];
}

std::ostream &operator<< (std::ostream &pr, const Matrix &a)
{
  for (int i = 0; i < a.get_rows (); ++i)
    {
      for (int j = 0; j < a.get_cols (); ++j)
        {
          if (a (i, j) > PRINT_LOWER_VALUE)
            {
              pr << "**";
            }
          else
            {
              pr << " ";
            }
        }
      std::cout << std::endl;
    }
  return pr;
}

std::ifstream &operator>> (std::ifstream &re, Matrix &a)
{
  re.read ((char *) (a.val), sizeof (float) * a.get_rows () * a.get_cols ());
  if (!re)
    {
      throw std::runtime_error (RUNTIME_ERROR_MSG);
    }
  std::cout << a;
  return re;
}

Matrix &Matrix::operator= (const Matrix &b)
{
  if (this != &b)
    {
      delete[] val;
      val = new float[b.get_cols () * b.get_rows ()];
      this->dim.cols = b.get_cols ();
      this->dim.rows = b.get_rows ();
      for (int i = 0; i < b.get_cols () * b.get_rows (); ++i)
        {
          this->val[i] = b[i];
        }
    }
  return *this;
}