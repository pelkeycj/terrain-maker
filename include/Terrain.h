#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "Buffer.h"

#include <stdlib.h>
#include <math.h>

const int X_SEGMENTS = 500;
const int Z_SEGMENTS = 500;

class Terrain {
public:
	Terrain();
	~Terrain();
	void init();
	void update();
	void render();
	void edit(float radius, float delta, glm::vec3 cameraPos, glm::vec3 cameraDir);

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
				float change = delta * 1.0f/sqrt(sqrt(distance));
				change *= (1.0f + ((rand() % 20) -10) / 100.0f);
				y += std::min(delta, change);
				y = std::max(0.0f, y);
			}	
		}
	};

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Buffer buffer;
};

#endif