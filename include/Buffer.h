#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>

class Buffer {
public:
	Buffer();
	~Buffer();
	
	void create(GLfloat* vdata, unsigned int* idata);
	void bind();
	void unbind();

private:
	GLuint VAOId;
	GLuint VBO;
	GLuint IBO;
	int stride{3}; // x,y,z
};

#endif