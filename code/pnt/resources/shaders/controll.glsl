#version 410

layout(vertices = 3) out;

//uniform float tessLevelOuter;
//uniform float tessLevelInner;

void main(void)
{
    if (gl_InvocationID == 0)
        {
            gl_TessLevelInner[0] = 2.0;
            gl_TessLevelOuter[0] = 2.0;
            gl_TessLevelOuter[1] = 2.0;
            gl_TessLevelOuter[2] = 2.0;
        }

        gl_out[gl_InvocationID].gl_Position =
            gl_in[gl_InvocationID].gl_Position;
}

