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



bool mDotP(Matrix &mn, Matrix &np, Matrix &mp) {
	if (mn.returnColumns() == np.returnRows() && mp.returnRows() == mn.returnRows() && mp.returnColumns() == np.returnColumns()) {

		for (int x = 0; x < mn.returnRows(); x++) {
			for (int y = 0; y < np.returnColumns(); y++) {

				for (int z = 0; z < np.returnRows(); z++) {

					mp.set(x, y) += mn.get(x, z) * np.get(z, y);

				}

			}
		}


		return 1;
	}
	else {

		std::cout << mn.returnColumns() << ", " << np.returnRows() << std::endl;
		std::cout << mp.returnRows() << ", " << mn.returnRows() << std::endl;
		std::cout << np.returnColumns() << ", " << mp.returnColumns() << std::endl;

		return 0;
	}
	return 0;
}


