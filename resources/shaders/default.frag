#version 460 core

in vec3 vertex_color;
out vec4 final_color;

void main()
{
    final_color = vec4(vertex_color.x, vertex_color.y, vertex_color.z, 1.0f);
}
