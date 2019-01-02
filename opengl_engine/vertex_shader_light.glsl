#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 in_normals;
layout(location = 2) in vec3 instance_pos;
layout(location = 3) in vec3 in_light_val;
layout(location = 10) in vec2 tex_coord;

out vec2 tex_coord_switch;
out vec3 normal_camspace;
out vec3 light_camspace;
out vec3 light_color;
out vec2 glpos;
out vec4 ShadowCoord;

out float cos;
out vec3 light_val;

uniform mat4 mesh;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 DepthBiasMVP;

uniform vec3 in_light_pos;
uniform vec3 in_light_color;

void main()
{
	vec3 light = normalize(vec3(10,-30,10));
	gl_Position = projection*view*model*mesh*vec4(aPos + instance_pos, 1.0);
	glpos = gl_Position.xy;
	//gl_Position = projection*view*model*mesh*vec4(aPos, 1.0);
	//cos = dot((mesh*model*vec4(in_normals,1.0)).xyz,light);
	normal_camspace = (vec4(in_normals,1.0)).xyz;
	light_camspace = in_light_pos;
	light_color = in_light_color;
	//cos = dot((view*model*mesh*vec4(in_normals,1.0)).xyz, view*vec4(light,1.0).xyz);
	tex_coord_switch = tex_coord;
	light_val = in_light_val;
	// Same, but with the light's view matrix
	ShadowCoord = DepthBiasMVP * vec4(aPos + instance_pos,1);
}