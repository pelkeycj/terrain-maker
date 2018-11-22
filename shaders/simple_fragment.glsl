#version 330 core
out vec4 FragColor;

in vec3 pos;

uniform vec3 cameraPos;
uniform vec3 cameraDir;
uniform float radius;

void main() {

	vec3 p = cameraPos - vec3(pos.x, pos.y, pos.z);
	float v = dot(normalize(cameraDir), p);
	float dist = sqrt(dot(p, p) - (v * v));

	if (dist < radius) {
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	} else {
		float height = pos.y  / 10.0;
		FragColor = vec4(height, height, height, 1.0);
	}
}