#version 330 core

layout(location = 0) in vec3 in_Position;   // position
layout(location = 1) in vec4 in_Color;      // color
layout(location = 2) in vec2 in_TexCoord;   // UV coordinates
layout(location = 3) in vec3 in_Normal;     // Normal vector

out vec4 fragColor;
out vec2 TexCoord;

uniform sampler2D displacementTex;
uniform bool useDisplacement;
uniform float displacementStrength;
uniform vec3 shapeCenter;
uniform bool displaceTowardCenter;
uniform mat4 cameraMatrix;

void main() {
    vec3 position = in_Position;
    
    if (useDisplacement)
    {
        float displacement = texture(displacementTex, in_TexCoord).r;
        // Map [0, 1] to [-0.5, 0.5] and scale
        displacement = (displacement - 0.5) * displacementStrength;

        // Use the passed normal for displacement direction
        vec3 displacementDir = normalize(in_Normal);
        
        // Ensure displacementDir points AWAY from shapeCenter for consistent radial behavior
        vec3 outwardRadial = normalize(position - shapeCenter);
        if (dot(displacementDir, outwardRadial) < 0.0)
        {
            displacementDir = -displacementDir;
        }
        
        // If we want to displace toward center, move along -displacementDir
        float directionSign = displaceTowardCenter ? -1.0 : 1.0;
        
        position += displacementDir * displacement * directionSign;
        
        // Apply camera transformation after displacement
        gl_Position = cameraMatrix * vec4(position, 1.0);
    }
    else
    {
        // For non-displaced shapes, the CPU already applied the camera transformation
        gl_Position = vec4(position, 1.0);
    }
    
    fragColor = in_Color;
    TexCoord = in_TexCoord;  
}
