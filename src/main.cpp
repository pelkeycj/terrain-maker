
// TerrainEditor.h
	// main program - init sdl + opengl, loop, etc

// Terrain.h
	// create flat heightmap
#include "TerrainEditor.h"

int main( int argc, char** argv) {
	TerrainEditor editor;
	if(argc == 2) {
		editor.startWithFile(argv[1]);
	} else if (argc == 3) {
		editor.startWithDimensions(std::stoi(argv[1]), std::stoi(argv[2]));
	} else {
		editor.start();
	}

	return 0;
}
