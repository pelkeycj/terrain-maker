#include "TerrainEditor.h"
#include <iostream>


//TODOs:
// - create flat terrain heightmap
// - do magic to find verts to increase in height based on clicks
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

	terrain.init();

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
	terrain.update();
	Camera::instance().update(shaderId, WIDTH, HEIGHT);
}

void TerrainEditor::render() {
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	terrain.render();

	SDL_Delay(50);
}

void handleKeydown(SDL_Event& event) {
	switch (event.key.keysym.sym) {
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
		default:
			break;
	}
}


//TODO distance between verts and line 
// https://www.opengl.org/discussion_boards/showthread.php/138743-distance-between-a-line-and-a-point-in-3d
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
				case SDL_MOUSEWHEEL:
					terrain.edit(Camera::instance().getPosition(), Camera::instance().getDirection());
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



// TODO pull out
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