#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

using activation::Activation_Func;

/**
 * @class Dense
 * @brief Represents a dense layer in a neural network.
 */
class Dense
{
 private:
  Matrix _weights;          /**< The weight matrix of the layer. */
  Matrix _bias;             /**< The bias matrix of the layer. */
  Activation_Func activation_function; /**< The activation function of the layer. */

 public:
  /**
   * @brief Constructs a Dense layer with the given weight matrix, bias matrix, and activation function.
   * @param weights The weight matrix.
   * @param bias The bias matrix.
   * @param activation_func The activation function.
   */
  Dense(const Matrix& weights, const Matrix& bias, Activation_Func activation_func);

  /**
   * @brief Returns the weight matrix of the Dense layer.
   * @return The weight matrix.
   */
  Matrix get_weights() const;

  /**
   * @brief Returns the bias matrix of the Dense layer.
   * @return The bias matrix.
   */
  Matrix get_bias() const;

  /**
   * @brief Returns the activation function of the Dense layer.
   * @return The activation function.
   */
  Activation_Func get_activation() const;

  /**
   * @brief Applies the Dense layer to the input matrix and returns the result matrix.
   * @param input_m The input matrix.
   * @return The result matrix after applying the Dense layer.
   */
  Matrix operator()(const Matrix& input_m) const;
};

#endif //DENSE_H
