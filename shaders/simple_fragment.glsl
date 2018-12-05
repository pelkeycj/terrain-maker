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

	if (pos.y <= 0.0) {
		FragColor = vec4(0.0, 0.0, 1.0, 1.0);
	} else if (pos.y < 2) {
		FragColor = vec4(194/255.0, 178/255.0, 128/255.0, 1.0);
	} else if (pos.y < 20) {
		float height = pos.y  / 40.0 + 0.1;
		FragColor = vec4(0.0, height, 0.0, 1.0);
	} else if (pos.y < 25) {
		FragColor = vec4(150/255.0, 75/255.0, 0.0, 1.0);
	} else {
		FragColor = vec4(1.0);
	}

	if (dist < radius) {
		FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	} 
}