#ifndef _OBJECTS_H
#define _OBJECTS_H
#include "simpleMatrices.h"
#include <vector>
#include <string>
#include <iostream>
#include <strstream>
#include <fstream>

typedef struct tagTriangle {

	float vertex[3];
	float normal[3];

} Triangle, * pTriangle;


class GameObject {
	public:

		Matrix* obj;
		Triangle* objFaces;
		int faceCount;

		GameObject(std::string path);
		~GameObject();

		bool importObj(std::string path);
		bool calculateNormals();
};

class Camera {
	private:
		Matrix projection;
	public:

		float x, y, z;

		Camera(int scW, int scH);
		~Camera();
		bool projectToScreen(Matrix& m, int scW, int scH);
};
#else
#endif 

