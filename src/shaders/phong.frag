# version 330 core

#define MAX 5


in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 fragColor;

uniform vec3 eye = vec3(0.0,0.0,3.0);
uniform vec3 lightPosition;

uniform int lightCount;

struct Light {
    vec3 position;
    vec3 attenuation;
};

uniform Light lights[MAX];


void main (void)
{
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
    vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);

    float constant = lights[0].attenuation.x;
    float linear = lights[0].attenuation.y;
    float quadratic = lights[0].attenuation.z;

    vec3 norm = normalize( ex_worldNormal );

    vec3 viewDir = normalize(eye - vec3(ex_worldPosition));

    vec3 lightDir = lights[0].position - vec3(ex_worldPosition);
    float distance = length(lightDir);

    vec3 reflectDir = reflect ( -lightDir , norm );

    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

    float spec = pow(max(dot(viewDir, normalize(reflectDir)), 0.0), 32);
    if (dot(norm,lightDir) < 0)
    {
        spec = 0.0;
    }

    float diffuse = max(dot(norm,normalize(lightDir)),0.0);
    vec4 diff = diffuse * vec4(1.0,1.0,1.0,1.0);
    
    fragColor = ambient + (diff * objectColor * attenuation ) + (spec *  attenuation *vec4 (1.0 ,1.0 ,1.0 ,1.0));
}