#version 330 core

in vec4 fragColor;      // interpolated vertex color
in vec2 TexCoord;       // UV coordinates from vertex shader

out vec4 FragColor;     // final pixel colour

uniform sampler2D tex;  // texture sampler
uniform bool useTexture; // toggle between texture and color

void main()
{
    if (useTexture)
        FragColor = texture(tex, TexCoord);
    else
        FragColor = fragColor;
}
