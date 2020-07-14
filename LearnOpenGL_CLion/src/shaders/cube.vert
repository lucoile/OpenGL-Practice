#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 vertexColor;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 MVP;
uniform mat4 model;


void main()
{
    gl_Position = MVP * vec4(aPos, 1.0f);
    vertexColor = vec3(1.0f, 0.5f, 0.31f);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
}
