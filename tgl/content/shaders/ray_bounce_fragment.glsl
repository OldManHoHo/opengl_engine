#version 330 core

// Ouput data
layout(location = 0) out vec3 fragmentdepth;

void main(){
    // Not really needed, OpenGL does it anyway
    fragmentdepth.r = gl_FragCoord.z;
}