#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense {
 private:
  Matrix _weights;
  Matrix _bias;
  activation::activation_func _fun;
 public:
  Dense (Matrix &weights, Matrix &bias, activation::activation_func func);
  Matrix get_weights ();
  Matrix get_bias ();
  activation::activation_func get_activation ();
  Matrix operator() (Matrix &a);
};

#endif //DENSE_H
