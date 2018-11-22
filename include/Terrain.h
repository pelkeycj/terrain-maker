#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <glad/glad.h>
#include "Buffer.h"

const int X_SEGMENTS = 100;
const int Z_SEGMENTS = 100;
class Terrain {
public:
	Terrain();
	~Terrain();
	void init();
	void update();
	void render();

private:
	
	struct Vertex {
		float x, y, z;

		Vertex(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z) {}
	};

	std::vector<Vertex> vertices;
	std::vector<float> verts;
	std::vector<unsigned int> indices;
	Buffer buffer;
};

#endif