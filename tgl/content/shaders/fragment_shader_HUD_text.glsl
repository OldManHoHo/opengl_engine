
#version 330 core
in vec3 out_color;
in vec2 tex_coord;
out vec4 FragColor;
in vec2 tex_offset_1_f;
in vec2 tex_offset_2_f;

uniform sampler2D texture0;

void main()
{
	float diff_x = tex_offset_2_f.x - tex_offset_1_f.x;
	float diff_y = tex_offset_2_f.y - tex_offset_1_f.y;
	float new_x = tex_offset_1_f.x + tex_coord.x*diff_x;
	float new_y = tex_offset_1_f.y + tex_coord.y*diff_y;
	float val = texture(texture0, vec2(new_x,new_y)).r;
	if (val < 0.5)
	{
		discard;
	}
	else
	{
		FragColor.xyzw = vec4(1,1,1,1);
	}
	/*
	if (gl_FragCoord.x < 500 && gl_FragCoord.x > 100)
	{
		FragColor.xyz = vec3(0,0,0);
	}
	else
	{
		discard;
	}
	*/
}