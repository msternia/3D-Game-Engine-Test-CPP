#ifndef _GRAPHICSPROCESSING_H
#define _GRAPHICSPROCESSING_H
#include "simpleMatrices.h"

//https://www.youtube.com/watch?v=7WlAIwd-jGk
//https://metalbyexample.com/linear-algebra/


class Camera{
	public:
		Matrix projection;

		float width;
		float height;

		Camera(Matrix &m, float w, float h);

};

bool mTranslate(Matrix &m, float x, float y, float z);

bool mScale(Matrix &m, float x, float y, float z);

bool mRotate(Matrix &m, float xAxis, float yAxis, float zAxis);

bool projectToScreen(Matrix &m, int scWidth, int scHeight);


typedef struct tagTriangle {

	 float p[3][3];

} Triangle, *pTriangle;

#else
#endif
