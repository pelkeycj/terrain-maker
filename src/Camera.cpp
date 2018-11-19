#include "Camera.h"
#include <iostream>

Camera& Camera::instance() {
    static Camera* instance = new Camera();
    return *instance;
}

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	viewDir = glm::normalize(position - glm::vec3(0.0f, 0.0f, 0.0f));
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera() {}


void Camera::moveForward() {
	position += MOVE_DELTA * viewDir;

}

void Camera::moveBack() {
	position -= MOVE_DELTA * viewDir;
}

void Camera::moveLeft() {
	position -= MOVE_DELTA * glm::normalize(glm::cross(viewDir, up));
}

void Camera::moveRight() {
	position += MOVE_DELTA * glm::normalize(glm::cross(viewDir, up));
}

glm::mat4 Camera::look() {
    return glm::lookAt( position,
                        position + viewDir,
                        up);
}

//TODO see opengl tut to get this working


void Camera::update(const unsigned int shaderId, const unsigned int width, const unsigned int height) {
	glm::mat4 projection = glm::perspective(45.0f, ((float) width / (float) height), 0.1f, 20.0f);
	GLint loc = glGetUniformLocation(shaderId, "projection");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
	loc = glGetUniformLocation(shaderId, "view");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(look()));

	glm::mat4 model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
	loc = glGetUniformLocation(shaderId, "model");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
}