//
// Created by עודד ועלני on 11/05/2022.
//
#include "MlpNetwork.h"
#define DEFULT_DIGIT_VALUE {11,0}
MlpNetwork::MlpNetwork (Matrix *weights, Matrix *bias)
{
  layers[0] = new Dense (weights[0], bias[0], relu);
  layers[1] = new Dense (weights[1], bias[1], relu);
  layers[2] = new Dense (weights[2], bias[2], relu);
  layers[3] = new Dense (weights[3], bias[3], softmax);
}

digit MlpNetwork::operator() (Matrix &a)
{
  Matrix temp = ((*layers[0])(a));
  temp = (*layers[1])(temp);
  temp = (*layers[2])(temp);
  temp = (*layers[3])(temp);
  digit return_value = DEFULT_DIGIT_VALUE;
  for (unsigned int i = 0; i < (unsigned int)temp.get_rows(); ++i)
    {
      if(return_value.probability < temp[(int)i])
        {
          return_value = {i,temp[i]};
        }
    }
  return return_value;
}

