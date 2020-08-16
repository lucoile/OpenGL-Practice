#version 330 core
out vec4 FragColor;

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

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D shadowMap;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir)
{
    // set the bias based on the angle of the light hitting the surface
    float bias = max(0.01 * (1.0 - dot(fs_in.Normal, lightDir)), 0.005);

    // perform perspective divide to get coordinates in [-1,1]
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // scale coordinated to fit in [0,1]
    projCoords = projCoords * 0.5 + 0.5;

    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
//    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
    shadow = 0.0;

    return shadow;
}

void main()
{
    if (light.position == vec3(0.0f))
    {
        FragColor = texture(material.diffuse, fs_in.TexCoords);
    } else {
        vec3 color = texture(material.diffuse, fs_in.TexCoords).rgb;

        // ambient
        vec3 ambient = light.ambient * material.ambient;

        // diffuse
        vec3 norm = normalize(fs_in.Normal);
        vec3 lightDir = normalize(light.position - fs_in.FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = light.diffuse * diff;

        // specular
        vec3 viewDir = normalize(viewPos - fs_in.FragPos);
        float spec = 0.0;
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(fs_in.Normal, halfwayDir), 0.0), material.shininess);
        vec3 specular = light.specular * (spec * material.specular);

        // calculate shadow
        float shadow = ShadowCalculation(fs_in.FragPosLightSpace, lightDir);
        vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

        FragColor = vec4(lighting, 1.0);
    }
}

