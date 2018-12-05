#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "Buffer.h"
#include "objFileLoader.h"

#include <stdlib.h>
#include <math.h>

const int X_SEGMENTS = 200;
const int Z_SEGMENTS = 200;

class Terrain {
public:
	Terrain();
	Terrain(std::string fileName);
	~Terrain();
	void init();
	void update();
	void render();
	void edit(float radius, float delta, glm::vec3 cameraPos, glm::vec3 cameraDir);
	void saveFile();
	void loadFile(std::string fileName);


private:

	struct Vertex {
		float x, y, z;

		Vertex(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z) {}

		// distance algorithm from
		// https://www.opengl.org/discussion_boards/showthread.php/138743-distance-between-a-line-and-a-point-in-3d
		void edit(float radius, float delta, glm::vec3& cameraPos, glm::vec3& cameraDir) {
			glm::vec3 p = cameraPos - glm::vec3(x, y, z);
			float distance = sqrt(glm::dot(p, p) - pow(glm::dot(cameraDir, p), 2));

			if (distance < radius) {
				float change = delta * 1.0f/sqrt(distance);
				y += std::min(delta, change);
				y = std::max(0.0f, y);
			}
		}

		float getX() {
			return x;
		}
		float getY() {
			return y;
		}
		float getZ() {
			return z;
		}
	};

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Buffer buffer;
	std::vector<GLfloat> vertexList;
	Face faceList;
};

#endif
