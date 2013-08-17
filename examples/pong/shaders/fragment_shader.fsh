#version 120

varying vec3 Color;
varying vec2 Texcord;

uniform sampler2D tex;

void main() {
    gl_FragColor = texture2D(tex, Texcord);// * vec4(Color, 1.0);
}