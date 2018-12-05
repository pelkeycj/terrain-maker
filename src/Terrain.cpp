#include "Terrain.h"
#include <iostream>
#include <fstream>

// create a flat terrain mesh
Terrain::Terrain() {
	srand(time(NULL));
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

// Creates a new terrain based on the saved terrain.
Terrain::Terrain(std::string fileName) {
	srand(time(NULL));
	vertices.clear();
	indices.clear();

	objFileLoader myObj = objFileLoader(fileName);
	faceList = myObj.getFaces();
	vertexList = myObj.getVertexes();

	for(int ii = 0; ii < vertexList.size(); ii+=3) {
		vertices.push_back(Vertex(vertexList[ii], vertexList[ii + 1], vertexList[ii + 2]));
	}

	for(int jj = 0; jj < faceList.vertexIndexes.size(); jj++) {
		indices.push_back(faceList.vertexIndexes[jj]);
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

// Saves out the current terrain as an .obj file.
void Terrain::saveFile() {
	std::ofstream out;
	out.open("example.obj");

	for (auto& v : vertices) {
		out << "v " << v.getX() << " " << v.getY() << " " << v.getZ() << std::endl;
	}

	for(int ii = 0; ii < indices.size(); ii+=3)  {
		out << "f " << indices.at(ii) + 1 << "/" << indices.at(ii + 1) + 1 <<
		"/" << indices.at(ii + 2) + 1 << std::endl;
	}

	out.close();

}
