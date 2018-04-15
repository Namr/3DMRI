#version 150

in vec2 TexCoords;
in vec3 Color;

uniform sampler2D texPuppy;

out vec4 outColor;

void main()
{
    outColor = texture(texPuppy,TexCoords);
}
