#version 150

in vec3 Color;
in vec2 Texcord;

out vec4 outColor;

uniform sampler2D tex;

void main() {
    outColor = texture(tex, Texcord);
    //outColor = texture(tex, Texcord) * vec4(Color, 1.0);
    //outColor = vec4(Color, 1.0);
}
