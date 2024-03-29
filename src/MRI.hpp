#ifndef MRI_H
#define MRI_H

#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Camera.hpp"

using namespace std;

class MRI;

struct Vertex{
  glm::vec3 Position;
  float Color;
  Vertex(float x, float y, float z, float col)
  {
    Position = glm::vec3(x, y, z);
    Color = col;
  }
};

class Chunk
{
 public:
  Chunk();
  void init();
  void update(Camera &camera);
  unsigned char block(int x, int y, int z);

  void Cube();
  void CubeTop(int x, int y, int z, unsigned char block);
  void CubeBot(int x, int y, int z, unsigned char block);
  void CubeNorth(int x, int y, int z, unsigned char block);
  void CubeSouth(int x, int y, int z, unsigned char block);
  void CubeEast(int x, int y, int z, unsigned char block);
  void CubeWest(int x, int y, int z, unsigned char block);

  GLuint loadShader(const char *filepath, GLenum type);
  GLuint shaderProgram;
  
  int exists = 0;

  MRI* parent;
  unsigned char threshold = 140;

  vector<Vertex> newVertices;
  vector<unsigned int> newTriangles;

  glm::mat4 model;
  
  unsigned int VAO, VBO, EBO;
  
  unsigned int faceCount = 0;
  
  int chunkSizeX;
  int chunkSizeY;
  int chunkSizeZ;
  int chunkX;
  int chunkY;
  int chunkZ;
};

class MRI
{
 public:
  MRI(string path);
  void update(Camera &camera);
  
  //dimensions of the MRI file (in pixels, assumes 8bpp)
  static const int width = 181;
  static const int height = 217;
  static const int depth = 181;
  static const int chunkSize = 32;

  static const int chunkWidth = width / chunkSize + (width % chunkSize != 0);
  static const int chunkHeight = height / chunkSize + (height % chunkSize != 0);
  static const int chunkDepth = depth / chunkSize + (depth % chunkSize != 0);

  Chunk chunks[chunkWidth][chunkHeight][chunkDepth];
  
  unsigned char data[width][height][depth];
};
#endif
