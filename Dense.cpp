//
// Created by עודד ועלני on 11/05/2022.
//
#include "Dense.h"

Dense::Dense(Matrix& weights,Matrix& bias,activation::activation_func func)
{
  _weights = weights;
  _bias = bias;
  _fun = func;
}
Matrix Dense::get_weights()
{
  return _weights;
}
Matrix Dense::get_bias()
{
  return _bias;
}
activation::activation_func Dense::get_activation()
{
  return _fun;
}
Matrix Dense::operator()(Matrix& a)
{
  return _fun(_weights * a + _bias);
}
