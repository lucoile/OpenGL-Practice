#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 TexCoord;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projectionMatrix = mat4(1.0f);

void main()
{
    gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(aPos, 1.0f);
    vertexColor = vec4(aColor, 1.0f);
    TexCoord = aTexCoord;
}
