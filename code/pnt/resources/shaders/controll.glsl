#version 410 core

// Definitions
struct pnPatch {
    float b210;
    float b120;
    float b021;
    float b012;
    float b102;
    float b201;
    float b111;
};

// Variable in
layout(vertices = 3) out;

//layout(location = 0) in vec3 inputNormals[];
layout(location = 0) in vec3 vsNormals[];

// Variable out
layout(location = 0) out vec3 tcsNormals[3];
layout(location = 3) out pnPatch tcsPatches[3];


// Uniform in
//uniform float tessLevelOuter;
//uniform float tessLevelInner;

float P1 = gl_in[0].gl_Position[gl_InvocationID];
float P2 = gl_in[1].gl_Position[gl_InvocationID];
float P3 = gl_in[2].gl_Position[gl_InvocationID];

float N1 = vsNormals[1][gl_InvocationID];
float N2 = vsNormals[2][gl_InvocationID];
float N3 = vsNormals[3][gl_InvocationID];


////Project a point on a plane
float wij(int i, int j){
    return dot((gl_in[j].gl_Position.xyz - gl_in[i].gl_Position.xyz),
        vsNormals[i]);
}

void computeGeomtryControlPoints() {
    tcsPatches[gl_InvocationID].b210 = (2.0 * P1 + P2 - wij(1, 2) * N1) / 3.0;
    tcsPatches[gl_InvocationID].b120 = (2.0 * P2 + P1 - wij(2, 1) * N2) / 3.0;
    tcsPatches[gl_InvocationID].b021 = (2.0 * P2 + P3 - wij(2, 3) * N2) / 3.0;
    tcsPatches[gl_InvocationID].b012 = (2.0 * P3 + P2 - wij(3, 2) * N3) / 3.0;
    tcsPatches[gl_InvocationID].b102 = (2.0 * P3 + P1 - wij(3, 1) * N3) / 3.0;
    tcsPatches[gl_InvocationID].b201 = (2.0 * P1 + P3 - wij(1, 3) * N1) / 3.0;

    float E = (
        tcsPatches[gl_InvocationID].b210 +
        tcsPatches[gl_InvocationID].b120 +
        tcsPatches[gl_InvocationID].b021 +
        tcsPatches[gl_InvocationID].b012 +
        tcsPatches[gl_InvocationID].b102 +
        tcsPatches[gl_InvocationID].b201) / 6.0;

    float V = (P1 + P2 + P3) / 3.0;

    tcsPatches[gl_InvocationID].b111 = E + (E - V)/2.0;
}

void passThroughToTES(){
    tcsNormals[gl_InvocationID] = vsNormals[gl_InvocationID];
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}

void setTesselationLevels(float inner, float outer){
    if (gl_InvocationID == 0) {
            gl_TessLevelInner[0] = inner;
            gl_TessLevelOuter[0] = outer;
            gl_TessLevelOuter[1] = outer;
            gl_TessLevelOuter[2] = outer;
    }
}

void main(void)
{
    setTesselationLevels(2.0, 1.0);
    computeGeomtryControlPoints();
    passThroughToTES();
}

