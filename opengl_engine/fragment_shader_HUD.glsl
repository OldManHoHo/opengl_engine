
#version 330 core
in vec3 out_color;
out vec4 FragColor;

void main()
{
	FragColor.xyz = out_color;
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