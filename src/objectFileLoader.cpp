#include <vector>
#include "../include/objFileLoader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


  // Constructor
  objFileLoader::objFileLoader(std::string fileName) {
    std::ifstream inFile;
    inFile.open(fileName);
    int i = 0;
    // get the height and width
    if(inFile.is_open()){
      std::string line;   // A string object.
      std::vector<GLuint> vert;
      std::vector<GLuint> vertn;
      std::vector<GLuint> vertt;
      int counter = 0;

      // Go through lines.
      while(getline(inFile,line)){
        std::string intAsString = line;
        // add a new vertex
        GLfloat stringAsFloat = 0;
        // If line starts with v parse vertexes
        if(line.at(0) == 'v' && line.at(1) != 'n' && line.at(1) != 't') {
          std::stringstream ss(line.substr(2));
          ss>>stringAsFloat;
          vertexList.push_back(stringAsFloat);
          ss>>stringAsFloat;
          vertexList.push_back(stringAsFloat);
          ss>>stringAsFloat;
          vertexList.push_back(stringAsFloat);
          // if line starts with f then parse faces
        } else if (line.at(0) == 'f') {
          int v1,vt1,vn1;
          int v2,vt2,vn2;
          int v3,vt3,vn3;

          const char* newLine=line.c_str();
          sscanf (newLine, "f %i/%i/%i",&v1,&v2,&v3);
          GLuint V1 = v1 - 1;
          GLuint V2 = v2 - 1;
          GLuint V3 = v3 - 1;

          vert.push_back(V1);
          vert.push_back(V2);
          vert.push_back(V3);

          faceList.vertexIndexes = vert;
      }
    }
  }
    // Closes the file we are reading from
    inFile.close();
  }
  // Desctructor
  objFileLoader::~objFileLoader() {
  }
  // Return the stored vertex data
  std::vector<GLfloat> objFileLoader::getVertexes() {
    return vertexList;
  }
  // Return the stored faces
  Face objFileLoader::getFaces() {
    return faceList;
  }
