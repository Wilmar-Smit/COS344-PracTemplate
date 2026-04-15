#version 330 core

in vec4 fragColor;      // comes from the vertex shader
out vec4 FragColor;     // final pixel colour

void main()
{
    FragColor = fragColor;
}
