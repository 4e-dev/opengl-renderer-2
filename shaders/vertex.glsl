#version 460
out vec3 color;

uniform mat4 MVP;
in vec3 vector_color;
in vec2 vector_position;

void main()
{
    gl_Position = MVP * vec4(vector_position, 0.0, 1.0);
    color = vector_color;
}
