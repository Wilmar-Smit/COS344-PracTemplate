#version 330 core
layout (location = 0) in vec2 in_Position;

void main(void) {
    // Expand 2D input into 4D clip-space coordinates
    gl_Position = vec4(in_Position, 0.0, 1.0);
}
