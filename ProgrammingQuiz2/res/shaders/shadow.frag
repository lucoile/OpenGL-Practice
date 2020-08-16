#version 330 core

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

void main()
{
    gl_FragDepth = gl_FragCoord.z;
}