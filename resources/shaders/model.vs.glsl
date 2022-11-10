#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec3 aBiTangente;
layout (location = 5) in vec3 aTangente;
layout (location = 6) in ivec4 boneIds;
layout (location = 7) in vec4 weights;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 totalPosition = vec4(0.0f);
    if (boneIds[0] != -1) {
        for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
        {
            if(boneIds[i] == -1)
            continue;
            if(boneIds[i] >= MAX_BONES)
            {
                totalPosition = vec4(aPos,1.0f);
                break;
            }
            vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(aPos,1.0f);
            totalPosition += localPosition * weights[i];
            vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * aNormal;
        }
        mat4 viewModel = view * model;
        FragPos = vec3(model * vec4(aPos, 1.0));
        gl_Position =  projection * viewModel * totalPosition;
    } else {
        FragPos = vec3(model * vec4(aPos, 1.0));
        gl_Position = projection * view * vec4(FragPos, 1.0);
    }
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
}