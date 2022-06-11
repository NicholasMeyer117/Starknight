uniform sampler2D texture;

uniform vec4 redGlow;

uniform vec4 baseColor;

uniform int setting;

void main()
{

vec2 screenSize = vec2(1920, 1080);
vec2 position = gl_TexCoord[0].xy / screenSize;
vec4 pixel_color = baseColor;//texture2D(texture, gl_TexCoord[0].xy);
//float percent = redGlow.a;

float glowStr = (gl_FragCoord.x/3.0)/screenSize.x;

vec4 colorDifference = vec4(0,0,0,1);
if (setting == 1)
{
    colorDifference.r = redGlow.r - pixel_color.r;
    colorDifference.g = redGlow.g - pixel_color.g;
    colorDifference.b = redGlow.b - pixel_color.b;
    pixel_color.r = pixel_color.r + colorDifference.r * glowStr;
    pixel_color.g = pixel_color.g + colorDifference.g * glowStr;
    pixel_color.b = pixel_color.b + colorDifference.b * glowStr;
}

if (setting == 2)
{
    if (gl_FragCoord.y > screenSize.y/2.0)
    {
    colorDifference.r = redGlow.r - pixel_color.r;
    colorDifference.g = redGlow.g - pixel_color.g;
    colorDifference.b = redGlow.b - pixel_color.b;
    pixel_color.r = pixel_color.r + colorDifference.r * glowStr;
    pixel_color.g = pixel_color.g + colorDifference.g * glowStr;
    pixel_color.b = pixel_color.b + colorDifference.b * glowStr;
    }
}



gl_FragColor = pixel_color; 

}
