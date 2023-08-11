#version 460 core

in vec4 inout_vertex_color;
in vec2 inout_texture_coordinates;

layout (location = 0) out vec4 out_frag_color;

uniform sampler2D our_texture;

void main()
{
    out_frag_color = vec4(inout_vertex_color.r, inout_vertex_color.g, inout_vertex_color.b, inout_vertex_color.a);
    //out_frag_color = texture(our_texture, inout_texture_coordinates);
}
