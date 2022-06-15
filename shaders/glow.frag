uniform sampler2D texture;

uniform vec4 redGlow;

uniform vec4 blueGlow;

uniform float globalGlowStr;

uniform vec4 baseColor;

uniform int setting;

void main()
{

    vec2 screenSize = vec2(1920, 1080);
    vec2 position = gl_TexCoord[0].xy / screenSize;
    vec4 pixel_color = baseColor;   //texture2D(texture, gl_TexCoord[0].xy);
    vec4 glowColor = vec4(0,0,0,0);

    float glowStrX = (gl_FragCoord.x/3.0)/screenSize.x;
    float glowStrY = 1.0;
    float glowStr = 1.0;

    vec4 colorDifference = vec4(0,0,0,1);
    
    if (setting != 0)
        glowStr = globalGlowStr;

    if (setting == 1)
    {
        glowColor = redGlow;
        glowStrY = (gl_FragCoord.y)/(screenSize.y);
        glowStrY = 2.0 * glowStrY;
        if (glowStrY > 1.0)
            glowStrY = 2.0 - glowStrY;
    }
    else if (setting == 2 && gl_FragCoord.y > screenSize.y/2.0)
    {
        glowColor = redGlow;
        glowStrY = (gl_FragCoord.y - screenSize.y/2.0)/(screenSize.y - screenSize.y/2.0);
        glowStrX = (gl_FragCoord.x/2.0)/screenSize.x;
        glowStrY = 2.0 * glowStrY;
        if (glowStrY > 1.0)
            glowStrY = 2.0 - glowStrY;
    }
    else if (setting == 2 && gl_FragCoord.y < screenSize.y/2.0)
    {
        glowColor = blueGlow;
        glowStrY = (gl_FragCoord.y - screenSize.y/2.0)/(0.0 - screenSize.y/2.0);
        glowStrX = (gl_FragCoord.x/2.0)/screenSize.x;
        glowStrY = 2.0 * glowStrY;
        if (glowStrY > 1.0)
            glowStrY = 2.0 - glowStrY;
    }
    else if (setting == 2)
    {
        glowColor = vec4(0,0,0,1);
        glowStrY = 1.0;
    }

    colorDifference.r = glowColor.r - pixel_color.r;
    colorDifference.g = glowColor.g - pixel_color.g;
    colorDifference.b = glowColor.b - pixel_color.b;
    pixel_color.r = pixel_color.r + colorDifference.r * glowStrX * glowStrY * glowStr;
    pixel_color.g = pixel_color.g + colorDifference.g * glowStrX * glowStrY * glowStr;
    pixel_color.b = pixel_color.b + colorDifference.b * glowStrX * glowStrY * glowStr;

    gl_FragColor = pixel_color; 

}
