#version 150
in vec3 position;
in float color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out float Color;

void main()
{
    Color = color;
    gl_Position = proj * view * model * vec4(position, 1.0);
}
