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

