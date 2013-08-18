#version 150

in vec2 position;
in vec3 color;
in vec2 texcord;

out vec3 Color;
out vec2 Texcord;

uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;

void main() {
  Color = color;
  Texcord = texcord;
  gl_Position = projection * camera * model * vec4(position, 0.0, 1.0);
}