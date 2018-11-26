#version 330 core

uniform vec4 params;
uniform vec3 color;

out vec3 out_color;

//const vec2 quadVertices[4] = { vec2(-1.0, -1.0), vec2(1.0, -1.0), vec2(-1.0, 1.0), vec2(1.0, 1.0) };
const vec2 quadVertices[4] = { vec2(0, 0), vec2(1.0, 0), vec2(0, 1.0), vec2(1.0, 1.0) };
void main()
{
    gl_Position = vec4(2.0*(params.x*quadVertices[gl_VertexID].x + params.z)-1.0, 2.0*(params.y*quadVertices[gl_VertexID].y + params.w)-1.0, -1.0, 1.0);
	out_color = color;
}