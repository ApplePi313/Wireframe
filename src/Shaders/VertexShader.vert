#version 400 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

out vec3 color;

uniform vec2 resize;

uniform vec2 screenDimensions;

uniform vec2 coords;

vec3 convertedPos;

void main() {
    convertedPos = vec3(pos.xy * resize, pos.z);

    convertedPos = convertedPos + vec3(coords, 0.0f);

    convertedPos = vec3((convertedPos.x - screenDimensions.x/2.0f) / (screenDimensions.x/2.0f), -(convertedPos.y - screenDimensions.y/2.0f) / (screenDimensions.y/2.0f), pos.z);

    gl_Position = vec4(convertedPos, 1.0f);
    color = col;
}