#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

namespace activation
{
    typedef Matrix (*activation_func) ( const Matrix &a);
    Matrix relu (const Matrix &a);
    Matrix softmax (const Matrix &a);
}

#endif //ACTIVATION_H