#version 150
in float Color;

uniform vec3 wireColor;
uniform bool isWireframe;

out vec4 outColor;

void main()
{
    if(isWireframe)
    {
	outColor = vec4(wireColor, 1.0);
    }
    else
    {
	outColor = vec4(Color, Color, Color, 1.0);	
    }
}
