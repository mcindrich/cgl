#version 330 core
out vec4 oColor;

uniform vec4 uColor;

void main()
{
    // oColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    oColor = uColor;
} 