#version 460 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform int hasTexture;

void main()
{
    if (hasTexture == 0) {
        FragColor = ourColor;
    } else {
        vec4 texColor = texture(ourTexture, TexCoord);
        if(texColor.a < 0.1)
        discard;
        FragColor = ourColor * texColor;
    }
}