#version 460 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);
    if(texColor.a < 0.1)
        discard;
    if (texColor.r == 181f / 255f && texColor.g == 66f / 255f && texColor.b == 45f / 255f)
        texColor.rgb = vec3(0, 1 ,0);
    FragColor = ourColor * texColor;
}