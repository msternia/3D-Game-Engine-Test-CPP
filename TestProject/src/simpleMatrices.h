#ifndef _SIMPLEMATRICES_H
#define _SIMPLEMATRICES_H


class Matrix {
	private:
		float** matrix;
		const int rows;
		const int columns;

	public:
		Matrix(int x, int y);
		~Matrix();

		float get(int x, int y);
		float& set(int x, int y);

		int returnRows();
		int returnColumns();

		void display();
};

bool matrixMultiply(Matrix &mn, Matrix &np, Matrix &mp);

bool copyMatrixContents(Matrix &original, Matrix &copy);

#else
#endif