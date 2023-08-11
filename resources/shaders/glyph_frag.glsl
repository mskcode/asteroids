#version 460

in vec2 inout_texture_coordinates;

layout (location = 0) out vec4 out_final_color;

// mono-colored bitmap image of the glyph; you don't directly set this value
// like with other uniform variables, but you use
// glBindTexture(GL_TEXTURE_2D, <texture_id>) or
// glBindTextureUnit(<unit>, <texture_id>) to set it
uniform sampler2D glyph_texture;

uniform vec3 texture_color; // color for adjusting the final output color

void main()
{
    // sample the R component of the texture as the sampled alpha value
    float alpha = texture(glyph_texture, inout_texture_coordinates).r;
    vec4 sampled = vec4(1.0, 1.0, 1.0, alpha);

    out_final_color = vec4(texture_color, 1.0) * sampled;
}
