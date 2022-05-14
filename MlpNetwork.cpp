//
// Created by עודד ועלני on 11/05/2022.
//
#include "MlpNetwork.h"
#define DEFULT_DIGIT_VALUE {11,0}
MlpNetwork::MlpNetwork (Matrix *weights, Matrix *bias)
{
  for (int i = 0; i < 4; ++i)
    {
      w[i] = weights[i];
      b[i] = bias[i];
    }
}

Dense MlpNetwork::layer_number (int i)
{
  if(i<3)
    {
      return Dense(w[i],b[i],relu);
    }
  return Dense(w[i],b[i],softmax);
}

digit MlpNetwork::operator() (Matrix &a)
{
  Matrix temp = (layer_number(0)(a));
  temp = layer_number(1) (temp);
  temp = layer_number(2) (temp);
  temp = layer_number(3) (temp);
  digit return_value = DEFULT_DIGIT_VALUE;
  for (unsigned int i = 0; i < (unsigned int) temp.get_rows (); ++i)
    {
      if (return_value.probability < temp[(int) i])
        {
          return_value = {i, temp[i]};
        }
    }
  return return_value;
}

