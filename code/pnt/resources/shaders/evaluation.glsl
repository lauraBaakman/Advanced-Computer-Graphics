#version 410

layout (triangles) in;

//in vec3 vColor[3];
out vec3 eColor;


void main(void)
{
//    eColor = vColor;
    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +
                      (gl_TessCoord.y * gl_in[1].gl_Position) +
                      (gl_TessCoord.z * gl_in[2].gl_Position);

}

