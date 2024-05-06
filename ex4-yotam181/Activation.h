// Activation.h
#include "Matrix.h"
#include <cmath>

using std::exp;

#ifndef ACTIVATION_H
#define ACTIVATION_H

namespace activation
{
    /**
     * @brief Function pointer type for activation functions.
     */
    typedef Matrix (*Activation_Func)(const Matrix& m);

    /**
     * @brief Applies the Rectified Linear Unit (ReLU) activation function to a matrix.
     * @param m The input matrix.
     * @return The result matrix after applying the ReLU activation function element-wise.
     */
    Matrix relu(const Matrix& m);

    /**
     * @brief Applies the softmax activation function to a matrix.
     * @param m The input matrix.
     * @return The result matrix after applying the softmax activation function element-wise.
     */
    Matrix softmax(const Matrix& m);
}

#endif //ACTIVATION_H
