#include <vector>
#include <string>
#include <glad/glad.h>


struct Face {
  std::vector<GLuint> vertexIndexes;
  std::vector<GLuint> vertexTextures;
  std::vector<GLuint> vertexNormalIndexes;
};


// This class loads data from a .obj file
class objFileLoader{
public:

    // Constructor
    objFileLoader(std::string fileName);
    // Desctructor
    ~objFileLoader();
    // Return the stored vertex data
    std::vector<GLfloat> getVertexes();
    // Return the stored vertex normal data
    std::vector<GLfloat> getVertexNormals();
    // Return the stored faces
    Face getFaces();
    // return stored textures
    std::vector<GLfloat> getTextures();
    // gets the mtl file
    std::string getMtlFile();
    // Generates the combined data
    void genCombinedData();
    // gets all the combinedData
    std::vector<GLfloat> getCombinedData();
    // gets all the combined indexes
    std::vector<GLuint> getCombinedIndexes();




private:

  std::vector<GLfloat> vertexList;
  std::vector<GLfloat> vertexNormalList;
  Face faceList;
  std::vector<GLfloat> tex;
  std::string mtlFileName;
  std::vector<GLfloat> combinedData;
  std::vector<GLuint> combinedIndexes;

};
