//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

/**
 * @class MlpNetwork
 * @brief Represents a multilayer perceptron (MLP) network.
 */
class MlpNetwork
{
 private:
  Dense dense1; /**< The first dense layer of the network. */
  Dense dense2; /**< The second dense layer of the network. */
  Dense dense3; /**< The third dense layer of the network. */
  Dense dense4; /**< The fourth dense layer of the network. */

 public:
  /**
   * @brief Constructs an MLP network with the given weight and bias matrices.
   * @param weights An array of weight matrices for each dense layer.
   * @param biases An array of bias matrices for each dense layer.
   */
  MlpNetwork(const Matrix* weights, const Matrix* biases);

  /**
   * @brief Applies the MLP network to the input matrix and returns the digit classification result.
   * @param input_m The input matrix.
   * @return The digit classification result.
   */
  digit operator()(const Matrix& input_m);
};

#endif // MLPNETWORK_H