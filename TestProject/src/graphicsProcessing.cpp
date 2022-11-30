#ifndef _GRAPHICSPROCESSING
#define _GRAPHICSPROCESSING

#include <math.h>
#include "..\headers\graphicsProcessing.h"

#else
#endif

bool mTranslate(Matrix &m, float x, float y, float z) {
	if (m.returnRows() == 4) {
		Matrix translate(4, 4);
		translate.set(0, 0) = 1;
		translate.set(1, 1) = 1;
		translate.set(2, 2) = 1;
		translate.set(3, 3) = 1;

		translate.set(0, 3) = x;
		translate.set(1, 3) = y;
		translate.set(2, 3) = -z;

		Matrix out(m.returnRows(), m.returnColumns());
		matrixMultiply(translate, m, out);

		return copyMatrixContents(out, m);

	}
	else return false;
}

bool mScale(Matrix& m, float x, float y, float z) {
	
	if (m.returnRows() == 4) {

		Matrix scale(4, 4);
		scale.set(0, 0) = 1 * x;
		scale.set(1, 1) = 1 * y;
		scale.set(2, 2) = 1 * z;
		scale.set(3, 3) = 1;

		Matrix out(m.returnRows(), m.returnColumns());
		matrixMultiply(scale, m, out);

		return copyMatrixContents(out, m);
	}
	else return false;

}

bool mRotate(Matrix &m, float xAxisDeg, float yAxisDeg, float zAxisDeg) {

	if (m.returnRows() != 4) {
		return false;
	}
	Matrix xRotation(4, 4);

	xRotation.set(0, 0) = 1;
	xRotation.set(1, 1) = cosf((xAxisDeg * gPI)/ 180);
	xRotation.set(2, 1) = -sinf((xAxisDeg * gPI) / 180);
	xRotation.set(2, 2) = cosf((xAxisDeg * gPI) / 180);
	xRotation.set(1, 2) = sinf((xAxisDeg * gPI) / 180);
	xRotation.set(3, 3) = 1;

	Matrix yRotation(4, 4);

	yRotation.set(0, 0) = cosf((yAxisDeg * gPI) / 180);
	yRotation.set(1, 1) = 1;
	yRotation.set(0, 2) = -sinf((yAxisDeg * gPI) / 180);
	yRotation.set(2, 2) = cosf((yAxisDeg * gPI) / 180);
	yRotation.set(2, 0) = sinf((yAxisDeg * gPI) / 180);
	yRotation.set(3, 3) = 1;

	Matrix zRotation(4, 4);

	zRotation.set(0, 0) = cosf((zAxisDeg * gPI) / 180);
	zRotation.set(1, 1) = cosf((zAxisDeg * gPI) / 180);
	zRotation.set(1, 0) = sinf((zAxisDeg * gPI) / 180);
	zRotation.set(2, 2) = 1;
	zRotation.set(0, 1) = -sinf((zAxisDeg * gPI) / 180);
	zRotation.set(3, 3) = 1;

	Matrix xOut(m.returnRows(), m.returnColumns());
	Matrix yXOut(m.returnRows(), m.returnColumns());
	Matrix out(m.returnRows(), m.returnColumns());

	matrixMultiply(xRotation, m, xOut);
	matrixMultiply(yRotation, xOut, yXOut);
	matrixMultiply(zRotation, yXOut, out);

	return copyMatrixContents(out, m);

}

bool projectToScreen(Matrix& m, int scWidth, int scHeight) {

	if (m.returnRows() != 4) {
		return false;
	}

	Matrix projection(4, 4);
	float fNear = 1.0f;
	float fFar = 1000.0f; 
	float fFov = 90.0f;
	float fAspectRatio = (float) scHeight / (float) scWidth;
	float fFOVRad = 1.0f / tanf(fFov * 0.5f / 180.0f * gPI);

	projection.set(0, 0) = fAspectRatio * fFOVRad;
	projection.set(1, 1) = fFOVRad;
	projection.set(2, 2) = fFar / (fFar - fNear);
	projection.set(2, 3) = 1.0f;
	projection.set(3, 2) = -(fFar * fNear) / (fFar - fNear);
	projection.set(3, 3) = 0.0f;

	Matrix out(m.returnRows(), m.returnColumns());
	matrixMultiply(projection, m, out);

	for (int i = 0; i < out.returnColumns(); i++) {
		if (out.get(3, i) != 0.0f)
		{
			out.set(0, i) /= out.get(3, i);
			out.set(1, i) /= out.get(3, i);
			out.set(2, i) /= out.get(3, i);

		}

	}

	mScale(out, 0.5 * scWidth, 0.5 * scHeight, 1);
	return copyMatrixContents(out, m);
}