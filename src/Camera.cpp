#include "Camera.h"

Camera& Camera::instance() {
    static Camera* instance = new Camera();
    return *instance;
}

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	viewDir = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	oldMousePos = glm::vec2(0, 0);
}

Camera::~Camera() {}

void Camera::mouseLook(int x, int y) {
	float xoffset = x - oldMousePos.x;
	float yoffset = y - oldMousePos.y;
	oldMousePos.x = x;
	oldMousePos.y = y;

	float sensitivity = 0.5f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	viewDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	viewDir.y = sin(glm::radians(pitch));
	viewDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	viewDir = glm::normalize(viewDir);
}

void Camera::moveUp() {
	position.y += MOVE_DELTA;
}

void Camera::moveDown() {
	position.y -= MOVE_DELTA;
}


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


void Camera::update(const unsigned int shaderId, const unsigned int width, const unsigned int height) {
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), ((float) width / (float) height), 0.1f, 100.0f);
	GLint loc = glGetUniformLocation(shaderId, "projection");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
	
	loc = glGetUniformLocation(shaderId, "view");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(look()));

	glm::mat4 model = glm::mat4(1.0f); 
	loc = glGetUniformLocation(shaderId, "model");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
}