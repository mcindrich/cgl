#version 330 core
layout(location = 0) in vec3 iPos;
layout(location = 1) in vec3 iColor;
layout(location = 2) in vec2 iTexCoordinates;

out vec4 vertColor;
out vec2 vertTexCoordinates;

void main() {
    gl_Position = vec4(-iPos, 1.0f);
    vertColor = vec4(iColor, 1.0f);
    vertTexCoordinates = iTexCoordinates;
}