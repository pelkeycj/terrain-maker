#include "TerrainEditor.h"
#include <iostream>


TerrainEditor::TerrainEditor() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window = SDL_CreateWindow("Terrain Editor",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);

	gladLoadGLLoader(SDL_GL_GetProcAddress);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	unsigned int vert, frag;
	shaderId = glCreateProgram();
	vert = createShader("./shaders/simple_vertex.glsl", true);
	frag = createShader("./shaders/simple_fragment.glsl", false);
	glAttachShader(shaderId, vert);
	glAttachShader(shaderId, frag);
	glLinkProgram(shaderId);
	glUseProgram(shaderId);
	glDeleteShader(vert);
	glDeleteShader(frag);
	//-------------------------------------------------------

}

TerrainEditor::~TerrainEditor() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}



void TerrainEditor::update() {
	glUseProgram(shaderId);
	GLuint loc = glGetUniformLocation(shaderId, "radius");
	glUniform1f(loc, radius);

	if (editing) {
		terrain.edit(radius, delta, Camera::instance().getPosition(), Camera::instance().getDirection());
	}

	terrain.update();
	Camera::instance().update(shaderId, WIDTH, HEIGHT);
}

void TerrainEditor::render() {
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, mode);
	terrain.render();

	SDL_Delay(50);
}

void TerrainEditor::handleKeydown(SDL_Event& event) {
	switch (event.key.keysym.sym) {
		case SDLK_t:
			if (mode == GL_FILL) {
				mode = GL_LINE;
			} else {
				mode = GL_FILL;
			}
			break;
		case SDLK_a:
		case SDLK_LEFT:
			Camera::instance().moveLeft();
			break;
		case SDLK_d:
		case SDLK_RIGHT:
			Camera::instance().moveRight();
			break;
		case SDLK_w:
		case SDLK_UP:
			Camera::instance().moveForward();
			break;
		case SDLK_s:
		case SDLK_DOWN:
			Camera::instance().moveBack();
			break;
		case SDLK_TAB:
			Camera::instance().moveUp();
			break;
		case SDLK_SPACE:
			Camera::instance().moveDown();
			break;
		case SDLK_n:
			terrain.saveFile();
			break;
		default:
			break;
	}
}

void TerrainEditor::changeRadius(bool increase) {
	if (increase) {
		radius += 1.0f;
	} else {
		radius = std::max(1.0f, radius - 1.0f);
	}
}


void TerrainEditor::setDelta(bool increase) {
	if ((increase && delta < 0) || (!increase && delta > 0)) {
		delta *= -1;
	}
}

// Uses the saved file to create a terrain
void TerrainEditor::startWithFile(std::string fileName) {
	terrain = Terrain(fileName);
	terrain.init();
	run();
}

void TerrainEditor::start() {
	terrain.init();
	run();
}

void TerrainEditor::run() {
	bool quit = false;
	SDL_Event e;

	while (!quit) {
		while(SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					handleKeydown(e);
					break;
				case SDL_MOUSEMOTION:
					Camera::instance().mouseLook(e.motion.x, e.motion.y);
					break;
				case SDL_MOUSEBUTTONDOWN:
					editing = true;
					setDelta(e.button.button == SDL_BUTTON_LEFT);
					break;
				case SDL_MOUSEBUTTONUP:
					editing = false;
					break;
				case SDL_MOUSEWHEEL:
					changeRadius(e.wheel.y > 0);
					break;
				default:
					break;
			}
		}

		update();
		render();
		SDL_GL_SwapWindow(window);
	}
}


unsigned int TerrainEditor::createShader(std::string source, bool vertex) {
	unsigned int shaderId;
	if (vertex) {
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	} else {
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
	}

	std::ifstream file(source);
	std::string shaderSource = "";
	std::string line;
	while (getline(file, line)) {
		shaderSource += line + '\n';
	}

	const char* src = shaderSource.c_str();
	glShaderSource(shaderId, 1, &src, NULL);
	glCompileShader(shaderId);

	int succ;
	char info[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &succ);
	if (succ == GL_FALSE) {
		glGetShaderInfoLog(shaderId, 512, NULL, info);
		std::cout << "ERROR " << info << std::endl;
	}
	return shaderId;
}
