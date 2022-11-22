#ifndef _GRAPHICSPROCESSING
#define _GRAPHICSPROCESSING
#define gPI 3.14159265359

#include <math.h>
#include "graphicsProcessing.h"

#else
#endif

Camera::Camera(Matrix &m, float w, float h) : projection(m), width(w), height(h){

	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fAspectRatio = h / w;
	float fFOVRad = 1.0f / tanf(fFov * 0.5f / 180.0f * gPI);


	m.set(0, 0) = fAspectRatio * fFOVRad;
	m.set(1, 1) = fAspectRatio * fFOVRad;
	m.set(2, 2) = fFar / (fFar - fNear);
	m.set(2, 3) = 1.0f;
	m.set(3, 2) = -fNear * fFar / (fFar - fNear);

}