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

    float n110;
    float n011;
    float n101;
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

float N1 = vsNormals[0][gl_InvocationID];
float N2 = vsNormals[1][gl_InvocationID];
float N3 = vsNormals[2][gl_InvocationID];


vec3 substractPoints(int i, int j){
    return (gl_in[i].gl_Position.xyz - gl_in[j].gl_Position.xyz);
}

// ###### GEOMETRY START ###### //
float wij(int i, int j){
    return dot((gl_in[j].gl_Position.xyz - gl_in[i].gl_Position.xyz),
        vsNormals[i]);
}

void computeGeomtryControlPoints() {
    tcsPatches[gl_InvocationID].b210 = (2.0 * P1 + P2 - wij(0, 1) * N1) / 3.0;
    tcsPatches[gl_InvocationID].b120 = (2.0 * P2 + P1 - wij(1, 0) * N2) / 3.0;
    tcsPatches[gl_InvocationID].b021 = (2.0 * P2 + P3 - wij(1, 2) * N2) / 3.0;
    tcsPatches[gl_InvocationID].b012 = (2.0 * P3 + P2 - wij(2, 1) * N3) / 3.0;
    tcsPatches[gl_InvocationID].b102 = (2.0 * P3 + P1 - wij(2, 0) * N3) / 3.0;
    tcsPatches[gl_InvocationID].b201 = (2.0 * P1 + P3 - wij(0, 2) * N1) / 3.0;

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

// ###### GEOMETRY END ######## //

// ###### NORMALS START ###### //
float vij(int i, int j){
    vec3 deltaP = substractPoints(j, i);

    float numerator = dot(deltaP, (vsNormals[i] + vsNormals[j]));
    float denominator = dot(deltaP, deltaP);

    return 2.0 * (numerator / denominator);
}

vec3 hij(int i, int j){
    return vsNormals[i] + vsNormals[j] - vij(i, j) * substractPoints(j, i);
}

float computeNormalControlPoint(int i, int j){
    vec3 h = hij(i, j);
    return h[gl_InvocationID] / length(h);
}

void computeNormalControlPoints(){
    tcsPatches[gl_InvocationID].n110 = computeNormalControlPoint(0, 1);
    tcsPatches[gl_InvocationID].n011 = computeNormalControlPoint(1, 2);
    tcsPatches[gl_InvocationID].n101 = computeNormalControlPoint(2, 0);
}

// ###### NORMALS END ######## //

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
    setTesselationLevels(1.0, 1.0);
    computeGeomtryControlPoints();
    computeNormalControlPoints();
    passThroughToTES();
}

