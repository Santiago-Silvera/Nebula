#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 currPos;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main() {

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - currPos);

    float ambient = 0.2f;
    float diffuse = max(dot(normal, lightDir), 0.0);

    float maxSpecular = 0.5f;
    vec3 viewDir = normalize(camPos - currPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specular = maxSpecular * spec;

    FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}