#version 460 core

in vec4 inout_vertex_color;
in vec2 inout_texture_coordinates;

layout (location = 0) out vec4 out_frag_color;
layout (location = 1) out vec4 out_frag_color2;

uniform sampler2D our_texture;

void main()
{
    out_frag_color = vec4(inout_vertex_color.r, inout_vertex_color.g, inout_vertex_color.b, inout_vertex_color.a);
    // FIXME currently this is not used for anything, it's here to prevent
    //   in_texture_coordinates attribute from being optimized out from
    //   default_vert.glsl
    out_frag_color2 = texture(our_texture, inout_texture_coordinates);
}
