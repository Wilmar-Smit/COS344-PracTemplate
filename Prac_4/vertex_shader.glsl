#version 330 core

// Vertex attributes
layout(location = 0) in vec3 in_Position;   // position
layout(location = 1) in vec4 in_Color;      // color
layout(location = 2) in vec2 in_TexCoord;   // UV coordinates

// Outputs to fragment shader
out vec4 fragColor;
out vec2 TexCoord;

void main() {
    gl_Position = vec4(in_Position, 1.0);
    fragColor = in_Color;
    TexCoord = in_TexCoord;  // pass UVs forward
}
