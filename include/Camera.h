#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <glad/glad.h>

const float MOVE_DELTA = 0.1f;

class Camera {
public:
	static Camera& instance();
	Camera();
	~Camera();

	void moveForward();
	void moveBack();
	void moveRight();
	void moveLeft();
	void update(const unsigned int shaderId, const unsigned int width, const unsigned int height);


private:
	glm::mat4 look();


	glm::vec3 position;
	glm::vec3 viewDir;
	glm::vec3 up;
	glm::mat4 projection;
};

#endif