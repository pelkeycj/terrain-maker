#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include <glad/glad.h>

const float MOVE_DELTA = 1.0f;

class Camera {
public:
	static Camera& instance();
	Camera();
	~Camera();

	void moveForward();
	void moveBack();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void update(const unsigned int shaderId, const unsigned int width, const unsigned int height);
	void mouseLook(int x, int y);

	glm::vec3 getPosition();
	glm::vec3 getDirection();

private:
	glm::mat4 look();


	float pitch{0}, yaw{0};
	glm::vec2 oldMousePos;
	glm::vec3 position;
	glm::vec3 viewDir;
	glm::vec3 up;
	glm::mat4 projection;
};

#endif