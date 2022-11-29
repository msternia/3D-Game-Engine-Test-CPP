#ifndef _SIMPLEMATRICES
#define _SIMPLEMATRICES

#include "simpleMatrices.h"
#include <iostream>

#else
#endif

Matrix::Matrix(int x, int y) : rows(x), columns(y) {

	matrix = new float* [x];

	for (int i = 0; i < x; i++) {
		matrix[i] = new float[y];
		for (int u = 0; u < y; u++) {
			matrix[i][u] = 0;
		}
	}

}

Matrix::~Matrix() {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

float Matrix::get(int x, int y) {
	return matrix[x][y];
}

float& Matrix::set(int x, int y) {
	return (matrix[x][y]);
}

int Matrix::returnRows() {
	return rows;
}

int Matrix::returnColumns() {
	return columns;
}

void Matrix::display() {
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < columns; y++) {
			std::cout << matrix[x][y] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}



bool matrixMultiply(Matrix &mn, Matrix &np, Matrix &mp) {

	for (int m = 0; m < mp.returnRows(); m++) {
		for (int p = 0; p < mp.returnColumns(); p++) {
			mp.set(m, p) = 0;
		}
	}

	if (mn.returnColumns() == np.returnRows() && mp.returnRows() == mn.returnRows() && mp.returnColumns() == np.returnColumns()) {

		for (int m = 0; m < mn.returnRows(); m++) {
			for (int p = 0; p < np.returnColumns(); p++) {

				for (int n = 0; n < np.returnRows(); n++) {

					mp.set(m, p) += mn.get(m, n) * np.get(n, p);

				}

			}
		}

		return true;
	}
	else return false;
}

bool copyMatrixContents(Matrix &original, Matrix &copy) {

	if (original.returnColumns() == copy.returnColumns() && original.returnRows() == copy.returnRows()) {
		for (int i = 0; i < original.returnRows(); i++) {
			for (int u = 0; u < original.returnColumns(); u++) {
				copy.set(i, u) = original.get(i, u);
			}
		}

		return true;
	}
	else return false;

}

