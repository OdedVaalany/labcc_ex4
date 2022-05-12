#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

namespace activation
{
    typedef Matrix& (*activation_func) (Matrix &a);
    Matrix& relu (Matrix &a);
    Matrix& softmax (Matrix &a);
}

#endif //ACTIVATION_H