#version 330 core
out vec4 oColor;

in vec4 vertColor;
in vec2 vertTexCoordinates;
// uniform vec4 uColor;
uniform float time;
uniform sampler2D texSampler0;
uniform sampler2D texSampler1;

#define M_PI 3.1415926535897932384626433832795

void main()
{
    // oColor = mix(
    //     texture(texSampler0, vertTexCoordinates), 
    //     texture(texSampler1, vec2(1 - vertTexCoordinates.x, vertTexCoordinates.y)), cos(time)
    // );
    oColor = texture(texSampler1, vertTexCoordinates);
    if(oColor.a <= 1) {
        discard;
    }
}
