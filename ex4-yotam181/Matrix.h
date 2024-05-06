// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <ostream>
#include <istream>

using std::cout;
using std::endl;
using std::sqrt;
using std::ostream;
using std::istream;


/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;

/**
 * @class Matrix
 * @brief Represents a matrix of floating-point numbers and provides various matrix operations.
 */
class Matrix
{
 private:
  int _rows;   ///< Number of rows in the matrix.
  int _cols;   ///< Number of columns in the matrix.

 public:
  float* _data; ///< 2D array represented in 1 dimension.

  /**
   * @brief Default constructor. Creates an empty matrix.
   */
  Matrix();

  /**
   * @brief Creates a matrix with the specified number of rows and columns.
   * @param rows The number of rows in the matrix.
   * @param cols The number of columns in the matrix.
   */
  Matrix(int rows, int cols);

  /**
   * @brief Copy constructor. Creates a matrix as a copy of another matrix.
   * @param m The matrix to be copied.
   */
  Matrix(const Matrix& m);

  /**
   * @brief Destructor. Deallocates the memory used by the matrix.
   */
  ~Matrix();

  /**
   * @brief Gets the number of rows in the matrix.
   * @return The number of rows.
   */
  int get_rows() const;

  /**
   * @brief Gets the number of columns in the matrix.
   * @return The number of columns.
   */
  int get_cols() const;

  /**
   * @brief Transposes the matrix, swapping rows and columns.
   * @return A reference to the transposed matrix.
   */
  Matrix& transpose();

  /**
   * @brief Vectorizes the matrix, converting it to a column vector.
   * @return A reference to the vectorized matrix.
   */
  Matrix& vectorize();

  /**
   * @brief Computes the dot product between two matrices.
   * @param m The matrix to compute the dot product with.
   * @return A new matrix resulting from the dot product.
   */
  Matrix dot(Matrix m) const;

  /**
   * @brief Computes the Frobenius norm of the matrix.
   * @return The Frobenius norm.
   */
  float norm() const;

  /**
   * @brief Finds the index of the maximum element in the matrix.
   * @return The index of the maximum element.
   */
  int argmax() const;

  /**
   * @brief Computes the sum of all elements in the matrix.
   * @return The sum of all elements.
   */
  float sum() const;

  /**
   * @brief Prints the matrix in a plain format.
   */
  void plain_print() const;

  /**
   * @brief Assignment operator. Assigns the contents of another matrix to this matrix.
   * @param rhs The matrix to assign from.
   * @return A reference to this matrix after assignment.
   */
  Matrix& operator=(const Matrix& rhs);

  /**
   * @brief Compound addition assignment operator. Adds another matrix to this matrix.
   * @param rhs The matrix to add.
   * @return A reference to this matrix after addition.
   */
  Matrix& operator+=(const Matrix& rhs);

  /**
   * @brief Accesses the element at the specified row and column in the matrix.
   * @param row The row index.
   * @param col The column index.
   * @return A reference to the element at the specified position.
   */
  float& operator()(int row, int col) const;

  /**
   * @brief Accesses the element at the specified index in the matrix.
   * @param i The index.
   * @return A reference to the element at the specified index.
   */
  float& operator[](int i);

  /**
   * @brief Accesses the element at the specified index in the matrix (read-only).
   * @param i The index.
   * @return The element at the specified index.
   */
  float operator[](int i) const;

  /**
   * @brief Adds two matrices.
   * @param lhs The left-hand side matrix.
   * @param rhs The right-hand side matrix.
   * @return A new matrix resulting from the addition.
   */
  friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);

  /**
   * @brief Multiplies two matrices.
   * @param lhs The left-hand side matrix.
   * @param rhs The right-hand side matrix.
   * @return A new matrix resulting from the multiplication.
   */
  friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

  /**
   * @brief Multiplies a matrix by a scalar value.
   * @param lhs The matrix.
   * @param c The scalar value.
   * @return A new matrix resulting from the multiplication.
   */
  friend Matrix operator*(const Matrix& lhs, float c);

  /**
   * @brief Multiplies a scalar value by a matrix.
   * @param c The scalar value.
   * @param rhs The matrix.
   * @return A new matrix resulting from the multiplication.
   */
  friend Matrix operator*(float c, const Matrix& rhs);

  /**
   * @brief Writes the matrix to the output stream.
   * @param os The output stream.
   * @param m The matrix.
   * @return The output stream after writing the matrix.
   */
  friend ostream& operator<<(ostream& os, const Matrix& m);

  /**
   * @brief Reads the matrix from the input stream.
   * @param is The input stream.
   * @param m The matrix.
   * @return The input stream after reading the matrix.
   */
  friend istream& operator>>(istream& is, Matrix& m);
};

#endif //MATRIX_H