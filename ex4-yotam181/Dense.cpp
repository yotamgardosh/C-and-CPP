
#include "Dense.h"

Matrix Dense::get_weights () const
{
  return _weights;
}
Matrix Dense::get_bias () const
{
  return _bias;
}
Activation_Func Dense::get_activation () const
{
  return activation_function;
}
Dense::Dense (const Matrix& weights, const  Matrix &bias, Activation_Func
activation_func): _weights(weights), _bias(bias), activation_function
(activation_func) {}


Matrix Dense::operator()(const Matrix &input_m) const
{
    Matrix applied_weights = get_weights() * input_m;
    Matrix plus_bias = applied_weights + get_bias();
    Matrix output_m = get_activation()(plus_bias);
    return output_m;
}
