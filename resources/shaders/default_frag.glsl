#version 460 core

in vec4 inout_vertex_color;
in vec2 inout_texture_coordinates;

layout (location = 0) out vec4 out_frag_color;

uniform sampler2D our_texture;

void main()
{
    // output just the vertex color
    //out_frag_color = vec4(inout_vertex_color.r, inout_vertex_color.g, inout_vertex_color.b, inout_vertex_color.a);

    // output just the texture
    //out_frag_color = texture(our_texture, inout_texture_coordinates);

    // output the texture mixed with vertex color
    out_frag_color = texture(our_texture, inout_texture_coordinates) * inout_vertex_color;
}
