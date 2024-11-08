# version 330 core

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 fragColor;

uniform vec3 eye = vec3(0.0,0.0,3.0);
uniform vec3 lightPosition;


void main (void)
{
    vec3 norm = normalize( ex_worldNormal );

    //vec3 lightPosition= vec3(0.0,0.0,0.0);
    vec3 viewDir = normalize(eye - vec3(ex_worldPosition));

    vec3 lightDir = lightPosition - vec3(ex_worldPosition);
    vec3 reflectDir = reflect ( -lightDir , norm );

    float spec = pow(max(dot(viewDir, normalize(reflectDir)), 0.0), 32);
    if (dot(norm,lightDir) < 0)
    {
        spec = 0.0;
    }

    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);

    // vec4 specular = specularStrength * spec * lightColor ;;
    vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);

    float diffuse = max(dot(norm,normalize(lightDir)),0.0);
    vec4 diff = diffuse * vec4(1.0,1.0,1.0,1.0);
    
    fragColor = ambient + (diff * objectColor ) + (spec * vec4 (1.0 ,1.0 ,1.0 ,1.0));
}