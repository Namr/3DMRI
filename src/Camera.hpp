#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <vector>
#include <stdlib.h>

class Camera
{
public:
  glm::mat4 view;
  glm::mat4 proj;
  Camera();
};

#endif
