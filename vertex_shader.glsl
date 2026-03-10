#version 330 core
layout (location = 0) in vec2 in_Position;   // 2D position
layout (location = 1) in vec4 in_Color;      // RGBA colour

out vec4 fragColor; // pass to fragment shader

void main()
{
    gl_Position = vec4(in_Position, 0.0, 1.0); // convert 2D to clip space
    fragColor = in_Color;                      // forward colour
}
