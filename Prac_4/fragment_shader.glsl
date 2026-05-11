#version 330 core

in vec4 fragColor;      
in vec2 TexCoord;       

out vec4 FragColor;    

uniform sampler2D tex;
uniform bool useTexture; 

// Alpha texture
uniform sampler2D alphaTex; 
uniform bool useAlpha; 
uniform float alphaValue;

void main()
{
    // Start with the base color (which includes the CPU-calculated light and alphaValue)
    vec4 finalColor = fragColor;

    // Apply color texture if enabled
    if (useTexture)
    {
        vec4 sampled = texture(tex, TexCoord);
        // Keep alpha from fragColor (alphaValue)
        finalColor = vec4(sampled.rgb, fragColor.a);
    }

    // Apply alpha texture requirements
    if (useAlpha)
    {
        
      
        float mask = texture(alphaTex, TexCoord).r;
        finalColor.a = mix(alphaValue, 1.0, mask);
    }
    else
    {
        // When disabled: entire ball is semi-transparent according to alphaValue.
        // finalColor.a is already fragColor.a (alphaValue)
    }

    FragColor = finalColor;
}

