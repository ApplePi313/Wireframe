#version 400 core

in vec3 color;

out vec4 FragColor;

void main() {
    FragColor = vec4(color / 255.0f, 1.0f);
}