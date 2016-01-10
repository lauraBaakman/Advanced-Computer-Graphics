#version 410 core

// Variable in
layout(vertices = 3) out;

//layout(location = 0) in vec3 inputNormals[];
layout(location = 0) in vec3 vsNormals[];

// Variable out
layout(location = 0) out vec3 tcsNormals[3];

// Uniform in
//uniform float tessLevelOuter;
//uniform float tessLevelInner;

struct pnPatch {
    float b210;
    float b120;
    float b021;
    float b012;
    float b102;
    float b201;
    float b111;
};

////Project a point on a plane
float wij(int i, int j){
    return dot((gl_in[j].gl_Position.xyz - gl_in[i].gl_Position.xyz),
        vsNormals[i]);
}

void main(void)
{
    if (gl_InvocationID == 0) {
            gl_TessLevelInner[0] = 2.0;

            gl_TessLevelOuter[0] = 2.0;
            gl_TessLevelOuter[1] = 2.0;
            gl_TessLevelOuter[2] = 2.0;
    }


    tcsNormals[gl_InvocationID] = vsNormals[gl_InvocationID];
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}

