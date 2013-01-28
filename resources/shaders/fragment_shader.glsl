#version 120

uniform vec3 triangleColor;

void main() {
    gl_FragColor = vec4(triangleColor, 1.0);
}