#version 330 core

layout (location = 0) in vec3 aPos;     // position variable with attribute 0
layout (location = 1) in vec3 aColor;    // color variable

out vec4 vertexColor; // color output to fragment shader

uniform float xOffset;

void main()
{
    gl_Position = vec4(aPos.x + xOffset, -aPos.y, aPos.z, 1.0);
    vertexColor = vec4(aPos, 1.0);
}


