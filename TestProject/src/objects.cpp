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

Camera::Camera(Matrix& m, float w, float h) : projection(m), width(w), height(h){

	Matrix projection(4, 4);
	float fNear = 1.0f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fAspectRatio = (float) h / (float) w;
	float fFOVRad = 1.0f / tanf(fFov * 0.5f / 180.0f * gPI);

	projection.set(0, 0) = fAspectRatio * fFOVRad;
	projection.set(1, 1) = fFOVRad;
	projection.set(2, 2) = fFar / (fFar - fNear);
	projection.set(2, 3) = 1.0f;
	projection.set(3, 2) = -(fFar * fNear) / (fFar - fNear);
	projection.set(3, 3) = 0.0f;

}


Camera::~Camera(){

}