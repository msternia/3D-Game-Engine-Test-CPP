#ifndef _GRAPHICSPROCESSING_H
#define _GRAPHICSPROCESSING_H
#define gPI 3.14159265359

#include "simpleMatrices.h"

//https://www.youtube.com/watch?v=7WlAIwd-jGk
//https://metalbyexample.com/linear-algebra/

bool mTranslate(Matrix &m, float x, float y, float z);

bool mScale(Matrix &m, float x, float y, float z);

bool mRotate(Matrix &m, float xAxis, float yAxis, float zAxis);

bool projectToScreen(Matrix &m, int scWidth, int scHeight);

#else
#endif
