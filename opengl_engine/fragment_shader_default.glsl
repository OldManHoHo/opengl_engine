
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.5,0.5,0.5,1.0);

	if (FragColor.a <= 0.0)
	{
		discard;
	}

	if ((FragColor.a < 0.8) && (mod(int(gl_FragCoord.x),4) <= int(FragColor.a*4) && mod(int(gl_FragCoord.y),4) >= 4-int(FragColor.a*4)))// || (mod(gl_FragCoord.x+1,2) == 1 && mod(gl_FragCoord.y,2) == 1)))
	{
		discard;
	}
} 