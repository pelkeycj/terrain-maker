#include "Terrain.h"

Terrain::Terrain() {
	for (int z = 0; z < Z_SEGMENTS; z++) {
		for (int x = 0; x < X_SEGMENTS; x++) {
			vertices.push_back(Vertex(x, 0.0f, z));
		}
	}

	for (int z = 0; z < Z_SEGMENTS-1; z++) {
		for (int x = 0; x < X_SEGMENTS-1; x++) {
			indices.push_back(x + (z * Z_SEGMENTS));
			indices.push_back(x + (x * Z_SEGMENTS) + X_SEGMENTS);
			indices.push_back(z + (z * Z_SEGMENTS) + 1);

			indices.push_back(x + (z * Z_SEGMENTS) + 1);
			indices.push_back(x + (z * Z_SEGMENTS) + Z_SEGMENTS);
			indices.push_back(x + (z * Z_SEGMENTS) + Z_SEGMENTS + 1);
		}
	}
	//TODO segfault here -> probably bad indices
	//buffer.create((GLfloat*) vertices.data(), indices.data());
}

Terrain::~Terrain() {}

void Terrain::update() {
	buffer.bind();
}

void Terrain::render() {
	glDrawElements(GL_TRIANGLES,
		indices.size(),
		GL_UNSIGNED_INT,
		nullptr);
}