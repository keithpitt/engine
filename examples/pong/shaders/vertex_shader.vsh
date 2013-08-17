#version 120

attribute vec2 position;
attribute vec3 color;
attribute vec2 texcord;

uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;

varying vec3 Color;
varying vec2 Texcord;

void main() {
  Color = color;
  Texcord = texcord;
  gl_Position = projection * camera * model * vec4(position, 0.0, 1.0);
}