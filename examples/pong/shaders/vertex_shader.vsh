#version 120

attribute vec2 position;
attribute vec3 color;

uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;

varying vec3 Color;

void main() {
  Color = color;
  gl_Position = projection * camera * model * vec4(position, 0.0, 1.0);
}