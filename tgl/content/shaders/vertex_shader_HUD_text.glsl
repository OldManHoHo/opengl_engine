#version 330 core

uniform vec4 params;
uniform vec3 color;
uniform vec2 tex_offset_1;
uniform vec2 tex_offset_2;

out vec3 out_color;
out vec2 tex_coord;
out vec2 tex_offset_1_f;
out vec2 tex_offset_2_f;

//const vec2 quadVertices[4] = vec2[4]( vec2(-1.0, -1.0), vec2(1.0, -1.0), vec2(-1.0, 1.0), vec2(1.0, 1.0) };
uniform vec2 quadVertices[4] = vec2[]( vec2(0.0, 0.0), vec2(1.0, 0.0), vec2(0.0, 1.0), vec2(1, 1) );
//const vec2 quadVertices[4] = { vec2(0, 0), vec2(1.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 1.0) };
void main()
{
    gl_Position = vec4(2.0*(params.x*quadVertices[gl_VertexID].x + params.z)-1.0, 2.0*(params.y*quadVertices[gl_VertexID].y + params.w)-1.0, -1.0, 1.0);
	tex_coord = vec2(quadVertices[gl_VertexID].x, -quadVertices[gl_VertexID].y);
	out_color = color;
	tex_offset_1_f = tex_offset_1;
	tex_offset_2_f = tex_offset_2;
}