# version 330 core

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 fragColor;


void main (void)
{
    vec3 norm = normalize( ex_worldNormal );

    vec3 lightPosition= vec3(0.0,0.0,0.0);

    vec3 viewDir = normalize(vec3(0.0,0.0,-1.0) - vec3(ex_worldPosition));

    vec3 lightDir = lightPosition - vec3(ex_worldPosition);
    vec3 reflectDir = reflect ( -lightDir , norm );
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);

    // vec4 specular = specularStrength * spec * lightColor ;;
    vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);

    float diffuse = max(dot(norm,lightDir),0.0);
    vec3 diff = diffuse * vec3(1.0,1.0,1.0);
    
    fragColor = ambient + (vec4(diff,1.0) * objectColor ) + (spec * vec4 (1.0 ,1.0 ,1.0 ,1.0));
}