#ifndef _OBJECTS
#define _OBJECTS
#define _SILENCE_CXX17_STRSTREAM_DEPRECATION_WARNING

#include "..\headers\objects.h"
#include "..\headers\graphicsProcessing.h"
#include <math.h>
#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>
#include <strstream>
#include <fstream>



#else
#endif

GameObject::GameObject(std::string path){

	if (!importObj(path)) throw std::invalid_argument("Invalid path or corrupted OBJ file");

}

GameObject::~GameObject() {
	delete[] objFaces;
	delete obj;
}

bool GameObject::importObj(std::string path) {

	std::ifstream f(path);
	if (!f.is_open()) return false;

	int verts = 0;
	int faces = 0;

	while (!f.eof()) {
		char line[128];
		f.getline(line, 128);


		if (line[0] == 'v') {
			verts++;
		}

		if (line[0] == 'f') {
			faces++;
		}
	}

	f.clear();
	f.seekg(0);

	obj = new Matrix(4, verts);
	objFaces = new Triangle[faces];

	int vertPoint = 0;

	while (!f.eof()) {
		char line[128];
		f.getline(line, 128);

		std::strstream s;
		s << line;

		char next;
		if (line[0] == 'v') {
			s >> next >> obj->set(0, vertPoint) >> obj->set(1, vertPoint) >> obj->set(2, vertPoint);
			obj->set(3, vertPoint) = 1;
			vertPoint++;
		}

		if (line[0] == 'f') {

			int values[3];
			s >> next >> values[0] >> values[1] >> values[2];

			values[0]--;
			values[1]--;
			values[2]--;

			objFaces[faceCount].vertex[0] = values[0];
			objFaces[faceCount].vertex[1] = values[1];
			objFaces[faceCount].vertex[2] = values[2];

			faceCount++;
		}
		
	}

	return true;
}

bool GameObject::calculateNormals() {

	for (int i = 0; i < faceCount; i++) {
		int v1 = objFaces[i].vertex[0];
		int v2 = objFaces[i].vertex[1];
		int v3 = objFaces[i].vertex[2];

		float vectorA[3], vectorB[3];

		vectorA[0] = obj->get(0, v2) - obj->get(0, v1);
		vectorA[1] = obj->get(1, v2) - obj->get(1, v1);
		vectorA[2] = obj->get(2, v2) - obj->get(2, v1);

		vectorB[0] = obj->get(0, v3) - obj->get(0, v1);
		vectorB[1] = obj->get(1, v3) - obj->get(1, v1);
		vectorB[2] = obj->get(2, v3) - obj->get(2, v1);

		objFaces[i].normal[0] = vectorA[1] * vectorB[2] - vectorA[2] * vectorB[1];
		objFaces[i].normal[1] = vectorA[2] * vectorB[0] - vectorA[0] * vectorB[2];
		objFaces[i].normal[2] = vectorA[0] * vectorB[1] - vectorA[1] * vectorB[0];


		float normalise = sqrtf(objFaces[i].normal[0] * objFaces[i].normal[0] + objFaces[i].normal[1] * objFaces[i].normal[1] + objFaces[i].normal[2] * objFaces[i].normal[2]);
		
		if (normalise != 0) {
			objFaces[i].normal[0] /= normalise;
			objFaces[i].normal[1] /= normalise;
			objFaces[i].normal[2] /= normalise;
		}

	}

	return true;
}

Camera::Camera(int scW, int scH) : projection(4, 4), x(0), y(0), z(0) {

	float fNear = 1.0f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fAspectRatio = (float) scH / (float) scW;
	float fFOVRad = 1.0f / tanf(fFov * 0.5f / 180.0f * gPI);

	projection.set(0, 0) = fAspectRatio * fFOVRad;
	projection.set(1, 1) = -fFOVRad;
	projection.set(2, 2) = fFar / (fFar - fNear);
	projection.set(2, 3) = 1.0f;
	projection.set(3, 2) = -(fFar * fNear) / (fFar - fNear);
	projection.set(3, 3) = 0.0f;


}


Camera::~Camera(){

}

bool Camera::projectToScreen(Matrix& m, int scW, int scH) {

	if (m.returnRows() != 4) {
		return false;
	}

	Matrix cam(4, 4);
	copyMatrixContents(projection, cam);

	mTranslate(cam, -x, -y, 0);
	cam.set(3, 2) += z;
	cam.set(2, 3) += z;


	Matrix out(m.returnRows(), m.returnColumns());
	matrixMultiply(cam, m, out);

	

	for (int i = 0; i < out.returnColumns(); i++) {
		if (out.get(3, i) != 0.0f)
		{
			out.set(0, i) /= out.get(3, i);
			out.set(1, i) /= out.get(3, i);
			out.set(2, i) /= out.get(3, i);

		}

	}

	mScale(out, 0.5 * scW, 0.5 * scH, 1);
	return copyMatrixContents(out, m);
}