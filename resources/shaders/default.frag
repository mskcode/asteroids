#version 460 core

in vec4 vertex_color;
out vec4 final_color;

void main()
{
    final_color = vec4(vertex_color.r, vertex_color.g, vertex_color.b, 1.0f);
}
