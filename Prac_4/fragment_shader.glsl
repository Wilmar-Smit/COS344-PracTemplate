#version 330 core

in vec4 fragColor;      
in vec2 TexCoord;       

out vec4 FragColor;    


uniform sampler2D tex;
uniform bool useTexture; 


uniform sampler2D displacementTex; 
uniform bool useDisplacement; 

// Alpha texture
uniform sampler2D alphaTex; 
uniform bool useAlpha; 

void main()
{
    vec4 finalColor = fragColor;
    

    if (useTexture)
    {
        vec4 sampled = texture(tex, TexCoord);
        // Keep alpha from incoming color; texture only provides RGB.
        finalColor = vec4(sampled.rgb, fragColor.a);
    }
    
  
    if (useAlpha)
    {
        vec4 alphaSampled = texture(alphaTex, TexCoord);
  
        finalColor.a *= alphaSampled.r; 
    }
    
    FragColor = finalColor;
}
