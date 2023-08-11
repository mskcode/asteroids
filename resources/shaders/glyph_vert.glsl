#version 460

layout (location = 0)  in vec4 in_vertex; // <vec2 position>, <vec2 texture>

out vec2 inout_texture_coordinates;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(in_vertex.xy, 0.0f, 1.0f);
    inout_texture_coordinates = in_vertex.zw;
}
