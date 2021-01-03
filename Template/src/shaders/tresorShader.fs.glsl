#version 300 es

precision mediump float;

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadric;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirlight;
uniform SpotLight spotlight;

uniform vec3 uObjColor;

out vec4 fFragColor;

vec3 CalcDirLight(DirLight light, vec3 vNormal_vs, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 vNormal_vs, vec3 vPosition_vs, vec3 viewDir);

void main() {
    vec3 Normal = normalize(vNormal_vs);
    vec3 viewDir = normalize(viewPos - vPosition_vs);

    vec3 resultat = (CalcDirLight(dirlight, Normal, viewDir) + CalcSpotLight(spotlight, Normal, vPosition_vs, viewDir)) * uObjColor;
    fFragColor = vec4(resultat, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.);

    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 ambient = light.ambient * material.ambient;
    vec3 specular = light.specular * (spec * material.specular);

    vec3 resulat = ambient + diffuse + specular;
    return resulat;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 position, vec3 viewDir){
    vec3 lightDir = normalize(-light.position - position);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.);

    float distance = length(light.position - position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadric * (distance*distance));

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 ambient = light.ambient * material.ambient;
    vec3 specular = light.specular * (spec * material.specular);

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    vec3 resulat = ambient + diffuse + specular;
    return resulat;
}