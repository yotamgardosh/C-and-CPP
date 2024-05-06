#include "MlpNetwork.h"

MlpNetwork::MlpNetwork (const Matrix *weights, const Matrix *biases):
  dense1(weights[0], biases[0], activation::relu),
  dense2(weights[1], biases[1], activation::relu),
  dense3(weights[2], biases[2], activation::relu),
  dense4(weights[3], biases[3], activation::softmax){}


digit MlpNetwork::operator() (const Matrix &input_m)
{
  Matrix presubmit_error = input_m;
  presubmit_error.vectorize();
  Matrix r1 = dense1(presubmit_error);
  Matrix r2 = dense2(r1);
  Matrix r3 = dense3(r2);
  Matrix r4 = dense4(r3);

  unsigned int pred = r4.argmax();
  digit res = (digit){pred, r4[pred]};
  return res;
}
