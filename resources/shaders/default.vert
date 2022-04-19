#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out vec4 vertex_color;

uniform mat4 camera_matrix;

void main()
{
    vertex_color = color;
    gl_Position = camera_matrix * vec4(position.x, position.y, position.z, 1.0f);
}
