# version 330 core

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 fragColor;


void main (void)
{
    vec3 reflectDir = reflect ( -lightDir , norm );
    float spec = pow((max(dot( viewDir , reflectDir )),0.0), 32);
    // vec4 specular = specularStrength * spec * lightColor ;;
    vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);
    // lze upravit I = Ia + Id + Is
    fragColor = ambient + (diff * objectColor ) + (spec * vec4 (1.0 ,1.0 ,1.0 ,1.0));
}