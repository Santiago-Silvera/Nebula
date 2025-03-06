#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 currPos;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight() {

    vec3 lightVec = lightPos - currPos;
    float distance = length(lightVec);
    float a = 3.0f;
    float b = 0.7f;
    float inten = 1.0f / (a * distance + b * distance + 1.0f);

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightVec);

    float ambient = 0.2f;
    float diffuse = max(dot(normal, lightDir), 0.0);

    float maxSpecular = 0.5f;
    vec3 viewDir = normalize(camPos - currPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specular = maxSpecular * spec;
    return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 directionalLight() {

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(vec3(0.0f, 1.0f, 0.0f));

    float ambient = 0.2f;
    float diffuse = max(dot(normal, lightDir), 0.0);

    float maxSpecular = 0.5f;
    vec3 viewDir = normalize(camPos - currPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    float specular = maxSpecular * spec;
    return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;

}

vec4 spotLight() {
    
    // These are cosine values
    float outerCone = 0.90f;
    float innerCone = 0.95f;

    vec3 lightVec = lightPos - currPos;
    float distance = length(lightVec);
    float a = 0.1f;
    float inten = 1.0f / (a * distance * distance);

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightVec);

    float ambient = 0.3f;
    float diffuse = max(dot(normal, lightDir), 0.0);

    float maxSpecular = 0.5f;
    vec3 viewDir = normalize(camPos - currPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specular = maxSpecular * spec;

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
    float spot = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return (texture(diffuse0, texCoord) * (diffuse * inten * spot + ambient) + texture(specular0, texCoord).r * specular * inten * spot) * lightColor;
}

void main() {

    FragColor = spotLight();
}