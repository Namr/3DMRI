#version 150
in vec2 texCoords;
in vec3 position;
in vec3 color;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 Color;
out vec2 TexCoords;

void main()
{
    Color = color;
    TexCoords = texCoords;
    gl_Position = proj * view * model * vec4(position, 1.0);
}
