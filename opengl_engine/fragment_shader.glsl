
#version 330 core
out vec4 FragColor;

in vec2 tex_coord_switch;
in vec3 normal_camspace;
in vec3 light_camspace;
in vec2 glpos;

in float cos;

uniform sampler2D texture0;

void main()
{
	vec3 n = normalize(normal_camspace);
	vec3 l = normalize(light_camspace);
    FragColor = texture(texture0, tex_coord_switch);
	FragColor.xyz = FragColor.xyz*max(-dot(n,l),0.4);
	if (FragColor.a <= 0.0)
	{
		discard;
	}

	if ((FragColor.a < 0.8) && (mod(int(gl_FragCoord.x),4) <= int(FragColor.a*4) && mod(int(gl_FragCoord.y),4) >= 4-int(FragColor.a*4)))// || (mod(gl_FragCoord.x+1,2) == 1 && mod(gl_FragCoord.y,2) == 1)))
	{
		discard;
	}
}