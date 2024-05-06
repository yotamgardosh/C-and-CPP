#include "Activation.h"



Matrix activation::relu(const Matrix& m)
{
  Matrix relu_m(m.get_rows(), m.get_cols());
  for(int i = 0; i< m.get_rows()*m.get_cols(); i++)
  {
    if (m[i] < 0)
    {
      relu_m[i] = 0;
    }
    else
    {
      relu_m[i] = m[i];
    }

  }
  return relu_m;
}

Matrix activation::softmax (const Matrix &m)
{
  Matrix softmax_m(m.get_rows(), m.get_cols());
  float sum = 0.0;
  for(int i = 0; i< m.get_rows()*m.get_cols(); i++)
  {
    float exped_val = exp(m[i]);
    sum += exped_val;
    softmax_m[i] = exped_val;
  }
  sum = 1/sum;
  return sum*softmax_m;
}