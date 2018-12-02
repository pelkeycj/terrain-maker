#include "Terrain.h"

// create a flat terrain mesh
Terrain::Terrain() {
	for (int z = 0; z < Z_SEGMENTS; z++) {
		for (int x = 0; x < X_SEGMENTS; x++) {
			vertices.push_back(Vertex(x, 0.0f , z));
		}
	}

    for (unsigned int z = 0; z < Z_SEGMENTS-1; z++) {
    	for (unsigned int x = 0; x < X_SEGMENTS-1; x++ ) {
            int vertexIndex = (z * X_SEGMENTS) + x;

            indices.push_back(vertexIndex);
            indices.push_back(vertexIndex + X_SEGMENTS + 1);
            indices.push_back(vertexIndex + 1);

            indices.push_back(vertexIndex);
            indices.push_back(vertexIndex + X_SEGMENTS);
            indices.push_back(vertexIndex + X_SEGMENTS + 1);
        }
    }
}

Terrain::~Terrain() {}

void Terrain::init() {
	buffer.create(vertices.size(), (GLfloat*) vertices.data(), indices.size(), indices.data());
}

void Terrain::update() {
	buffer.bind();
}

void Terrain::render() {
	glDrawElements(GL_TRIANGLES,
		indices.size(),
		GL_UNSIGNED_INT,
		nullptr);
}

void Terrain::edit(float radius, float delta, glm::vec3 cameraPos, glm::vec3 cameraDir) {
	glm::vec3 normalized = glm::normalize(cameraDir);
	for (auto& v : vertices) {
		v.edit(radius, delta, cameraPos, normalized);
	}

	buffer.addVertexData(vertices.size(), (GLfloat*) vertices.data());
}