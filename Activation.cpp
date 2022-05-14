//
// Created by עודד ועלני on 11/05/2022.
//
#include "Activation.h"
#include <cmath>
namespace activation
{
    Matrix relu (const Matrix &a)
    {
      Matrix temp = Matrix(a);
      for (int i = 0; i < a.get_rows (); ++i)
        {
          if (temp[i] < 0)
            {
              temp[i] = 0;
            }
        }
      return temp;
    }
    Matrix softmax (const Matrix &a)
    {
      Matrix temp = Matrix(a);
      float sum = 0;
      for (int i = 0; i < temp.get_rows (); ++i)
        {
          sum += temp[i] = std::exp (temp[i]);
        }
      temp = temp * (1 / sum);
      return temp;
    }
}
