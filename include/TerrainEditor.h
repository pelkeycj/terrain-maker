#ifndef TERRAINEDITOR_H
#define TERRAINEDITOR_H

#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else 
	#include <SDL.h>
#endif

#include <glad/glad.h>
#include <string>
#include <fstream>

#include "Camera.h"
#include "Terrain.h"


const int WIDTH = 640;
const int HEIGHT = 480;

class TerrainEditor {
public:
	TerrainEditor();
	~TerrainEditor();
	void run();

private:
	void render();
	void update();
	void handleKeyDown(SDL_Event& event);
	unsigned int createShader(std::string source, bool vertex);

	SDL_Window* window;
	SDL_GLContext context;

	unsigned int shaderId;
	Terrain terrain;
};

#endif