#ifndef MY_MATRIX_MATRIX_H
#define MY_MATRIX_MATRIX_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <stdexcept>

class Matrix {
public:
	Matrix(int, int, bool = false);
	Matrix(const Matrix&);
	~Matrix();
	int getW() const;
	int getK() const;
	double getFromPosition(int, int) const;
	Matrix& setAtPosition(int, int, double);
	bool isSameSize(const Matrix&) const;
	bool operator==(const Matrix&) const;
	Matrix& operator=(const Matrix&);
	Matrix operator+(const Matrix&) const;
	Matrix operator-(const Matrix&) const;
	Matrix operator*(const Matrix&) const;
	Matrix operator*(const double&) const;
	Matrix operator^(const int&) const;
	Matrix swapRows(const int&, const int&);
	Matrix swapCols(const int&, const int&);
	Matrix& print();

   friend std::ostream& operator<<(std::ostream&, const Matrix&);

private:
	double randomDouble(const double&, const double&);

private:
	int w, k;
	double **m;
};

#endif //MY_MATRIX_MATRIX_H
