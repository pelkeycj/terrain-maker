
// TerrainEditor.h
	// main program - init sdl + opengl, loop, etc

// Terrain.h
	// create flat heightmap
#include "TerrainEditor.h"

int main( int argc, char** argv) {
	TerrainEditor editor;
	if(argc == 2) {
		editor.startWithFile(argv[1]);
	} else {
		editor.start();
	}

	return 0;
}
