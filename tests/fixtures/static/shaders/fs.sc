@input {
    vec4 v_color0 : COLOR0;
    vec2 v_texcoord0 : TEXCOORD0;
}

#include <bgfx_shader.sh>

SAMPLER2D(s_texture, 0);

void main()
{
	gl_FragColor = texture2D(s_texture, v_texcoord0).rgba * v_color0;
}
