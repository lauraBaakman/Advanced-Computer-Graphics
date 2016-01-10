#version 410 core

//Variable in
layout (triangles) in;

layout(location = 0) in vec3 tcsNormals[];

//Variable out
//in vec3 vColor[3];

void main(void)
{
    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +
                      (gl_TessCoord.y * gl_in[1].gl_Position) +
                      (gl_TessCoord.z * gl_in[2].gl_Position);

}

