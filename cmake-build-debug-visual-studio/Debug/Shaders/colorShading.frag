#version 130

in vec4 fragmentColor;
in vec2 fragmentPosition;
out vec4 color;

uniform float time;

void main() {
    color = vec4(cos(fragmentPosition.y/fragmentPosition.y*time),tan(fragmentPosition.x/fragmentPosition.y *time),sin(fragmentPosition.y/fragmentPosition.x*time), fragmentColor.a + time);
    //color = vec4(tan(fragmentPosition.y/fragmentPosition.x*time),tan(fragmentPosition.y/fragmentPosition.x*time),tan(fragmentPosition.y/fragmentPosition.x*time), fragmentColor.a + time);
}