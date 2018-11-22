#include "Buffer.h"

#include <iostream>

Buffer::Buffer() {}


Buffer::~Buffer() {}


// TODO use Dynamic draw and glBufferSubData() to update 
void Buffer::create(unsigned int vcount, GLfloat* vdata, unsigned int icount, unsigned int* idata) {
	glGenVertexArrays(1, &VAOId);
	glBindVertexArray(VAOId);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vcount * 3 * sizeof(float), vdata, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*stride, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, icount * sizeof(unsigned int), idata, GL_DYNAMIC_DRAW);
}

void Buffer::bind() {
	glBindVertexArray(VAOId);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
}

void Buffer::unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Buffer::addVertexData(unsigned int vcount, GLfloat* vdata) {
	glBufferData(GL_ARRAY_BUFFER, vcount * 3 * sizeof(float), vdata, GL_DYNAMIC_DRAW);
}