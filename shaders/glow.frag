#version 130

uniform sampler2D texture;

uniform vec4 redGlow;

uniform vec4 blueGlow;

uniform float globalGlowStr;

uniform vec4 baseColor;

uniform int setting;

uniform vec2 shipCoords;

highp float NOISE_GRANULARITY = 0.5/255.0;

highp float random(highp vec2 coords) {
   return fract(sin(dot(coords.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{

    vec2 screenSize = vec2(1920, 1080);
    highp vec2 position = gl_TexCoord[0].xy / screenSize;
    vec2 coords = gl_FragCoord.xy/screenSize;
    highp vec4 pixel_color = baseColor;   //texture2D(texture, gl_TexCoord[0].xy);
    vec4 glowColor = vec4(0,0,0,255);
    
    
    vec4 thrustColor = redGlow;
    vec2 shipPos = shipCoords;
    float thrustStrX = 0.0;
    float thrustStrY = 0.0;
    float thrustStr = 1.0;
    

    float glowStrX = (gl_FragCoord.x/2.0)/screenSize.x;
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
    
    shipPos.y = 1000 - shipPos.y;
    thrustStrX = (gl_FragCoord.x - (shipPos.x - 150.0))/((shipPos.x - 10.0) - (shipPos.x - 150.0));
    thrustStrY = (gl_FragCoord.y - (shipPos.y - 15.0))/((shipPos.y + 15.0) - (shipPos.y - 15.0));
    if (thrustStrX < 0.0 || thrustStrX > 1.0)
        thrustStrX = 0.0;
    thrustStrY = 2.0 * thrustStrY;
    if (thrustStrY < 0.0 || thrustStrY > 2.0)
        thrustStrY = 0.0;
    else if(thrustStrY > 1.0)
        thrustStrY = 2.0 - thrustStrY;
        
    
    colorDifference.r = thrustColor.r - pixel_color.r;
    colorDifference.g = thrustColor.g - pixel_color.g;
    colorDifference.b = thrustColor.b - pixel_color.b;
    pixel_color.r = pixel_color.r + colorDifference.r * thrustStrX * thrustStrY * thrustStr;
    pixel_color.g = pixel_color.g + colorDifference.g * thrustStrX * thrustStrY * thrustStr;
    pixel_color.b = pixel_color.b + colorDifference.b * thrustStrX * thrustStrY * thrustStr;

    pixel_color += mix(-NOISE_GRANULARITY, NOISE_GRANULARITY, random(coords));
    gl_FragColor = pixel_color;

}
