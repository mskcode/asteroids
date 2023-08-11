#version 460 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_vertex_color;
layout (location = 2) in vec2 in_texture_coordinates;

out vec4 inout_vertex_color;
out vec2 inout_texture_coordinates;

uniform mat4 camera_matrix;

void main()
{
    gl_Position = camera_matrix * vec4(in_position.x, in_position.y, in_position.z, 1.0f);

    inout_vertex_color = in_vertex_color;
    inout_texture_coordinates = in_texture_coordinates;
}
