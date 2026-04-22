#version 330 core

// Vertex attributes
layout(location = 0) in vec3 in_Position;   // position
layout(location = 1) in vec4 in_Color;      // color
layout(location = 2) in vec2 in_TexCoord;   // UV coordinates

// Outputs to fragment shader
out vec4 fragColor;
out vec2 TexCoord;

// Displacement mapping uniforms
uniform sampler2D displacementTex;
uniform bool useDisplacement;
uniform float displacementStrength;

void main() {
    vec3 position = in_Position;
    
   
    if (useDisplacement)
    {
        float displacement = texture(displacementTex, in_TexCoord).r;
      
        displacement = (displacement - 0.5) * displacementStrength;
        
        position.z -= displacement;
    }
    
    gl_Position = vec4(position, 1.0);
    fragColor = in_Color;
    TexCoord = in_TexCoord;  
}
