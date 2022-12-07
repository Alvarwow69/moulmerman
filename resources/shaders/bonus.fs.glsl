#version 460 core

struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    int type;

    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

/*struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};*/

#define MAX_LIGHT 5

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Light lights[MAX_LIGHT];
uniform Material material;

out vec4 FragColor;

vec3 ProcessDirectionalLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 dirLight = normalize(-light.position);
    float diff = max(dot(normal, dirLight), 0.0);
    vec3 reflectDir = reflect(-dirLight, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambiant = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * material.specular;
    return (ambiant + diffuse + specular);
}

vec3 ProcessPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 dirLight = normalize(light.position - FragPos);
    float diff = max(dot(normal, dirLight), 0.0);
    vec3 reflectDir = reflect(-dirLight, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * material.specular;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 ProcessLight()
{
    vec3 result;
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    if (lights[0].type == 2)
    result = ProcessPointLight(lights[0], norm, FragPos, viewDir);
    else if (lights[0].type == 1)
    result = ProcessDirectionalLight(lights[0], norm, viewDir);
    for(int i = 1; i < MAX_LIGHT; i++) {
        if (lights[i].type == 2)
        result += ProcessPointLight(lights[i], norm, FragPos, viewDir);
        else if (lights[i].type == 1)
        result += ProcessDirectionalLight(lights[i], norm, viewDir);
    }
    return (result);
}

void main()
{
    vec4 result;
    if (lights[0].type != -1)
        result = vec4(ProcessLight(), 1.0);
    else
        result = texture(material.diffuse, TexCoords);
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = result;
}

// calculates the color when using a spot light.
/*vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}*/
