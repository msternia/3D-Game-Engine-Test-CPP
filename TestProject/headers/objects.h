#ifndef _OBJECTS_H
#define _OBJECTS_H
#include "simpleMatrices.h";
#include <vector>
#include <string>
#include <iostream>
#include <strstream>
#include <fstream>

typedef struct tagTriangle {

	float vertex[3];
	float normal;

} Triangle, * pTriangle;


class GameObject {
	public:

		Matrix* obj;
		Triangle* objFaces;
		int faceCount;

		GameObject(std::string path);
		~GameObject();

		bool importObj(std::string path);
};

class Camera {
	public:
		Matrix projection;

		float width;
		float height;

		Camera(Matrix& m, float w, float h);
		~Camera();
};
#else
#endif 

