#version 460

in vec2 texture_coordinates;

out vec4 final_color;

// mono-colored bitmap image of the glyph; you don't directly set this value
// like with other uniform variables, but you use
// glBindTexture(GL_TEXTURE_2D, <texture_id>) or
// glBindTextureUnit(<unit>, <texture_id>) to set it
uniform sampler2D glyph_texture;

uniform vec3 texture_color;// color for adjusting the final output color

void main()
{
    // sample the R component of the texture as the sampled alpha value
    float alpha = texture(glyph_texture, texture_coordinates).r;
    vec4 sampled = vec4(1.0, 1.0, 1.0, alpha);
    final_color = vec4(texture_color, 1.0) * sampled;
}
