#version 460
out vec4 fragment;

in vec3 color;
void main()
{
    fragment = vec4(color, 1.0);
}
