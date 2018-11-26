
#version 330 core
in vec3 out_color;
in vec2 tex_coord;
out vec4 FragColor;

uniform sampler2D texture0;

void main()
{
	FragColor = texture(texture0, tex_coord);
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