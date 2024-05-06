//
// Created by yotam on 12/06/2023.
//
#include "Matrix.h"

#define THRESHOLD 0.1


//     default constructors
Matrix::Matrix ()
{
  _cols = 1;
  _rows = 1;
  _data = new float[1];
  _data[0] = 0;
}

//     constructor
Matrix::Matrix (int rows, int cols)
{
  if(rows < 1 || cols < 1)
  {
    throw std::length_error("invalid matrix dimensions for operation");
  }
  _cols = cols;
  _rows = rows;
  _data = new float[rows * cols];
  for (int i = 0; i < _rows * _cols; ++i) {
    _data[i] = 0;
  }
}

//    cpy constructor
Matrix::Matrix(const Matrix& m)
{
  _cols = m.get_cols();
  _rows = m.get_rows();
  _data = new float[_rows * _cols];
  for (int i = 0; i < _rows * _cols; ++i) {
    _data[i] = m._data[i];
  }
}

Matrix::~Matrix ()
{
  delete[] _data;
}

int Matrix::get_rows() const
{
  return _rows;
}

int Matrix::get_cols() const
{
  return _cols;
}

Matrix& Matrix::transpose()
{
  int trans_rows = _rows;
  int trans_cols = _cols;
  float* transposed = new float[trans_rows * trans_cols];
  for (int i = 0; i < _rows; i++)
  {
    for(int j = 0; j < _cols; j++)
    {
      transposed[j*_rows+i] = _data[i * _cols + j];
    }
  }
  delete[] _data;
  _data = transposed;
  int temp = _rows;
  _rows = _cols;
  _cols = temp;
  return *this;

}


Matrix& Matrix::vectorize()
{
  _rows = _cols*_rows;
  _cols = 1;
  return *this;
}

void Matrix::plain_print() const
{
  for(int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      cout << _data[i*_rows + j] << " ";
    }
    cout << endl;
  }
}

Matrix Matrix::dot(Matrix m) const
{
 if(!(_rows == m.get_rows() && _cols == m.get_cols()))
 {
   throw std::length_error("invalid matrix dimensions for operation");
 }
 Matrix new_m(_rows, _cols);
 for(int i = 0; i < _rows*_cols; i++)
 {
   new_m._data[i] = this->_data[i]*m._data[i];
 }
  return new_m;
}


float Matrix::norm () const
{
  float sum = 0.0;
  for(int i = 1; i < _rows*_cols; i++)
  {
    sum+= (_data[i]*_data[i]);
  }
  return sqrt(sum);
}


int Matrix::argmax () const
{
  float max = _data[0];
  int max_ind = 0;
  for(int i = 1; i < _rows*_cols; i++)
  {
    if(_data[i] > max)
    {
      max = _data[i];
      max_ind = i;
    }
  }
  return max_ind;
}

Matrix operator+ (const Matrix &lhs, const Matrix &rhs)
{
  if(!(lhs.get_rows() == rhs.get_rows() && lhs.get_cols() == rhs.get_cols()))
  {
    throw std::length_error("invalid matrix dimensions for operation");
  }
  int r = lhs.get_rows();
  int c = lhs.get_cols();
  Matrix added_m(r, c);
  for(int i = 0; i < r*c; i++)
  {
    added_m._data[i] = lhs._data[i] + rhs._data[i];
  }
  return added_m;
}

Matrix & Matrix::operator= (const Matrix & rhs)
    // no need to check validity of dims
{
  if(this != &rhs)
  {
    delete[] _data;
    _rows = rhs.get_rows();
    _cols = rhs.get_cols();
    _data = new float[_rows*_cols];
    for(int i =0; i <_rows*_cols; i++)
    {
      _data[i] = rhs._data[i];
    }
  }
  return *this;
}


Matrix &Matrix::operator+= (const Matrix &rhs)
{
  if(!(_rows == rhs.get_rows() && _cols == rhs.get_cols()))
  {
    throw std::length_error("invalid matrix dimensions for operation");
  }
  for(int i = 1; i < _rows*_cols; i++)
  {
    _data[i] += rhs._data[i];
  }
  return *this;
}

Matrix operator* (const Matrix &lhs, const Matrix &rhs)
{
  if(lhs.get_cols() != rhs.get_rows())
  {
    throw std::length_error("invalid matrix dimensions for operation");
  }
  Matrix mul_m(lhs.get_rows(), rhs.get_cols()); //mxn * nxm -> m*m
  for(int i = 0; i < lhs.get_rows(); i++)
  {
    for(int j = 0; j < rhs.get_cols(); j++)
    {
      for(int k = 0; k < lhs.get_cols(); k++)
      {
        int dest = i * mul_m.get_cols() + j;
        int access_one = i*lhs.get_cols() + k;
        int access_two = k*rhs.get_cols() + j;
        mul_m._data[dest] += lhs._data[access_one] * rhs._data[access_two];
      }
    }
  }
  return mul_m;
}

Matrix operator* (const Matrix &lhs, float c)
{
  Matrix m(lhs._rows, lhs._cols);
  for(int i = 0; i < lhs._rows*lhs._cols; i++)
  {
    m._data[i] = lhs._data[i]*c;
  }
  return m;
}

Matrix operator* (float c, const Matrix &rhs)
{
  return rhs*c;
}


float& Matrix::operator() (int row, int col) const
{
  if(0 > row || _rows <= row || 0 > col || _cols <= col)
  {
    throw std::out_of_range("invalid coordinates");
  }
  return _data[row*_rows + col];
}

// used for implementing data e.g. m[i] = 3.0
float& Matrix::operator[](int i) {
  if(i < 0 || i >= _rows*_cols)
  {
    throw std::out_of_range("index out of bounds");
  }
  return _data[i] ;
}

// used for reading data e.g. float x = m[i]
float Matrix::operator[](int i) const
{
  if(i < 0 || i >= _rows*_cols)
  {
    throw std::out_of_range("index out of bounds");
  }
  return _data[i];
}

ostream &operator<< (ostream &os, const Matrix &m)
{
  int row = m.get_rows ();
  int col = m.get_cols ();
  for (int i = 0; i < row; ++i)
  {
    for (int j = 0; j < col; ++j)
    {
       if(m(i,j) > THRESHOLD)
       {
         os << "**";
       }
       else
       {
         os << "  ";
       }
    }
    os << "\n";
  }
  os << endl;
  return os;
}


std::istream& operator>> (std::istream& is, Matrix& m)
{
  is.seekg(0, std::ios_base::end);
  std::streampos input_size = is.tellg();
  std::streampos mat_size = m.get_rows() * m.get_cols() * sizeof(float);

  if (input_size < mat_size)
  {
    throw std::runtime_error("unable to read values from input stream");
  }

  is.seekg(0, std::ios_base::beg);
  is.read(reinterpret_cast<char*>(m._data), mat_size);

  if (!is)
  {
    throw std::runtime_error("unable to read values from input stream");
  }

  return is;
}


float Matrix::sum() const {
    float sum = 0.0;
    for (int i = 0; i < _rows*_cols; ++i) {
        sum += _data[i];
    }
    return sum;
}




