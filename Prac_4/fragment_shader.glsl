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
        // Sample the alpha map (assuming red channel contains the mask)
        // 0.0 = Dimple, 1.0 = Regular surface
        float mask = texture(alphaTex, TexCoord).r;

        // When enabled: dimples (mask near 0) are transparent (alphaValue), 
        // regular surface (mask near 1) is fully opaque (1.0).
        finalColor.a = mix(alphaValue, 1.0, mask);
    }
    else
    {
        // When disabled: entire ball is semi-transparent according to alphaValue.
        // finalColor.a is already fragColor.a (alphaValue)
    }

    FragColor = finalColor;
}

