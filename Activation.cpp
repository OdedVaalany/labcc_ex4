//
// Created by עודד ועלני on 11/05/2022.
//
#include "Activation.h"
#include <cmath>
namespace activation
{
    Matrix &relu (Matrix &a)
    {
      for (int i = 0; i < a.get_rows (); ++i)
        {
          if (a[i] < 0)
            {
              a[i] = 0;
            }
        }
      return a;
    }
    Matrix &softmax (Matrix &a)
    {
      float sum = 0;
      for (int i = 0; i < a.get_rows (); ++i)
        {
          sum += a[i] = std::exp (a[i]);
        }
      a = a * (1 / sum);
      return a;
    }
}
