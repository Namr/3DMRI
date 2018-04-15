#include "MRI.hpp"

Chunk::Chunk()
{
  exists = 1;
}

void Chunk::init()
{
  for(int z = 0; z < chunkSizeX; z++)
    {
      for(int y = 0; y < chunkSizeY; y++)
	{
	  for(int x = 0; x < chunkSizeZ; x++)
	    {
	      if(block(x, y, z) > threshold)
		{
		  if (block(x, y + 1, z) < threshold)
		    {
		      //block above is air
		      CubeTop(x, y, z, block(x, y, z));
		    }

		  if (block(x, y - 1, z) < threshold)
		    {
		      //block below is air
		      CubeBot(x, y, z, block(x, y, z));
		    }

		  if (block(x + 1, y, z) < threshold)
		    {
		      //block east is air
		      CubeEast(x, y, z, block(x, y, z));
		    }

		  if (block(x - 1, y, z) < threshold)
		    {
		      //block west is air
		      CubeWest(x, y, z, block(x, y, z));
		    }

		  if (block(x, y, z + 1) < threshold)
		    {
		      //block north is air
		      CubeNorth(x, y, z, block(x, y, z));
		    }

		  if (block(x, y, z - 1) < threshold)
		    {
		      //block south is air
		      CubeSouth(x, y, z, block(x, y, z));
		    }
		}
	    }
	}
    }

  model = glm::translate(model, glm::vec3( (float)chunkX, (float)chunkY, (float)chunkZ));
  
  //generate and bind the buffers assosiated with this chunk in order to assign vertices and color to the mesh
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  //load the shaders from their corresponding files
  GLuint vertexShader = loadShader("shaders/vertex.glsl",GL_VERTEX_SHADER);
  GLuint fragmentShader = loadShader("shaders/fragment.glsl",GL_FRAGMENT_SHADER);

  //compile the GPU programs
  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  //catch any errors
  GLint success;
  GLchar infoLog[512];
 
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
    {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR VERTEX SHADER COMPILE FAILED\n" << infoLog << std::endl;
    };

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
    {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "ERROR FRAGMENT SHADER COMPILE FAILED\n" << infoLog << std::endl;
    };
	
  //create a program from the shaders
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  
  //finilize the program and use it
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);
 
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  //set the array buffer to contain sections the size of a Vertex struct, and pass a pointer to the vector containing them
  glBufferData(GL_ARRAY_BUFFER, newVertices.size() * sizeof(Vertex), &newVertices[0], GL_STATIC_DRAW);  

  //pass and bind triangle data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, newTriangles.size() * sizeof(unsigned int), 
	       &newTriangles[0], GL_STATIC_DRAW);

  //pass vertex positions to shader program
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);	
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  //pass color to shader program
  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  glEnableVertexAttribArray(colAttrib);	
  glVertexAttribPointer(colAttrib, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    
  glBindVertexArray(0);
}

void Chunk::Cube()
{

  newTriangles.push_back(faceCount * 4); //1
  newTriangles.push_back(faceCount * 4 + 1); //2
  newTriangles.push_back(faceCount * 4 + 2); //3
  newTriangles.push_back(faceCount * 4); //1
  newTriangles.push_back(faceCount * 4 + 2); //3
  newTriangles.push_back(faceCount * 4 + 3); //4

  faceCount++; // Add this line
}

void Chunk::CubeTop(int x, int y, int z, unsigned char block)
{
  newVertices.push_back(Vertex(x, y, z + 1, (float) block / 255.0f));
  newVertices.push_back(Vertex(x + 1, y, z + 1, (float) block / 255.0f));
  newVertices.push_back(Vertex(x + 1, y, z, (float) block / 255.0f));
  newVertices.push_back(Vertex(x, y, z, (float) block / 255.0f));

  Cube();
}

void Chunk::CubeNorth(int x, int y, int z, unsigned char block)
{
  newVertices.push_back(Vertex(x + 1, y - 1, z + 1, (float) block / 255.0f));
  newVertices.push_back(Vertex(x + 1, y, z + 1, (float) block / 255.0f));
  newVertices.push_back(Vertex(x, y, z + 1, (float) block / 255.0f));
  newVertices.push_back(Vertex(x, y - 1, z + 1, (float) block / 255.0f));

  Cube();
}

void Chunk::CubeEast(int x, int y, int z, unsigned char block)
{
  newVertices.push_back(Vertex(x + 1, y - 1, z, (float) block / 255.0f));
  newVertices.push_back(Vertex(x + 1, y, z, (float) block / 255.0f));
  newVertices.push_back(Vertex(x + 1, y, z + 1, (float) block / 255.0f));
  newVertices.push_back(Vertex(x + 1, y - 1, z + 1, (float) block / 255.0f));

  Cube();
}

void Chunk::CubeSouth(int x, int y, int z, unsigned char block)
{
  newVertices.push_back(Vertex(x, y - 1, z, (float) block / 255.0f));
  newVertices.push_back(Vertex(x, y, z, (float) block / 255.0f));
  newVertices.push_back(Vertex(x + 1, y, z, (float) block / 255.0f));
  newVertices.push_back(Vertex(x + 1, y - 1, z, (float) block / 255.0f));

  Cube();
}

void Chunk::CubeWest(int x, int y, int z, unsigned char block)
{
  newVertices.push_back(Vertex(x, y - 1, z + 1, (float) block / 255.0f));
  newVertices.push_back(Vertex(x, y, z + 1, (float) block / 255.0f));
  newVertices.push_back(Vertex(x, y, z, (float) block / 255.0f));
  newVertices.push_back(Vertex(x, y - 1, z, (float) block / 255.0f));
  
  Cube();
}

void Chunk::CubeBot(int x, int y, int z, unsigned char block)
{
  newVertices.push_back(Vertex(x, y - 1, z, (float) block / 255.0f));
  newVertices.push_back(Vertex(x + 1, y - 1, z, (float) block / 255.0f));
  newVertices.push_back(Vertex(x + 1, y - 1, z + 1, (float) block / 255.0f));
  newVertices.push_back(Vertex(x, y - 1, z + 1, (float) block / 255.0f));

  Cube();
}

void Chunk::update(Camera &camera)
{
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  GLint uniTrans = glGetUniformLocation(shaderProgram, "model");
  glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(model));
    
  GLint uniView = glGetUniformLocation(shaderProgram, "view");
  glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(camera.view));

  GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(camera.proj));

  glUniform1i(glGetUniformLocation(shaderProgram, "isWireframe"), false);
    
  glDrawElements(GL_TRIANGLES, newTriangles.size(), GL_UNSIGNED_INT, 0);

  
  glEnable(GL_POLYGON_OFFSET_LINE);
  glPolygonOffset(2,2);
    
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glm::vec3 wcolor = glm::vec3(0.0, 0.0, 0.0);
  
  glUniformMatrix3fv(glGetUniformLocation(shaderProgram, "wireColor"), 1, GL_FALSE, glm::value_ptr(wcolor));
  glUniform1i(glGetUniformLocation(shaderProgram, "isWireframe"), true);
  glDrawElements(GL_TRIANGLES, newTriangles.size(), GL_UNSIGNED_INT, 0);
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
}


unsigned char Chunk::block(int x, int y, int z)
{
  int realX = chunkX + x;
  int realY = chunkY + y;
  int realZ = chunkZ + z;

  if(realX <= 180 && realY <= 216 && realZ <= 180)
    {
      return parent->data[realX][realY][realZ];
    }
  return 0;
}

GLuint Chunk::loadShader(const char *filepath, GLenum type)
{
  FILE *file = fopen(filepath, "rb");
  if(!file) {
    return 0;
  }
 
  long len;
  if(fseek(file, 0, SEEK_END) != 0 ||
     (len = ftell(file)) == -1L) {
    fclose(file);
    return 0;
  }
  rewind(file);
 
  char *buffer = (char *) malloc(len);
  if(fread(buffer, 1, len, file) != len) {
    fclose(file);
    free(buffer);
    return 0;
  }
  fclose(file);
 
  GLuint shader = glCreateShader(type);
  if(shader == 0) {
    free(buffer);
    return 0;
  }
 
  glShaderSource(shader, 1,(const char * const *) &buffer, (GLint *) &len);
  free(buffer);
  return shader;
}
