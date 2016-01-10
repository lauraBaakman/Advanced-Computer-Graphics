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

//Variable in
layout (triangles, fractional_odd_spacing, ccw) in;

layout(location = 0) in vec3 tcsNormals[];
layout(location = 3) in pnPatch tcsPatches[];

//Variable out
layout(location = 0) out vec3 tesNormal;

float u = gl_TessCoord.x;
float u2 = pow(u, 2.0);

float v = gl_TessCoord.y;
float v2 = pow(v, 2.0);

float w = gl_TessCoord.z;
float w2 = pow(w, 2.0);

void interpolateGeometricComponent(){
    vec3 b300 = gl_in[0].gl_Position.xyz;
    vec3 b030 = gl_in[1].gl_Position.xyz;
    vec3 b003 = gl_in[2].gl_Position.xyz;

    vec3 b210 = vec3(tcsPatches[0].b210, tcsPatches[1].b210, tcsPatches[2].b210);
    vec3 b120 = vec3(tcsPatches[0].b120, tcsPatches[1].b120, tcsPatches[2].b120);
    vec3 b021 = vec3(tcsPatches[0].b021, tcsPatches[1].b021, tcsPatches[2].b021);
    vec3 b012 = vec3(tcsPatches[0].b012, tcsPatches[1].b012, tcsPatches[2].b012);
    vec3 b102 = vec3(tcsPatches[0].b102, tcsPatches[1].b102, tcsPatches[2].b102);
    vec3 b201 = vec3(tcsPatches[0].b201, tcsPatches[1].b201, tcsPatches[2].b201);

    vec3 b111 = vec3(tcsPatches[0].b111, tcsPatches[1].b111, tcsPatches[2].b111);

    float u3 = u2 * u;
    float v3 = v2 * v;
    float w3 = w2 * w;

    vec3 position = b300 * w3 + b030 * u3 + b003 * v3 +
        b210 * 3.0 * w2 * u +
        b120 * 3.0 * w * u2 +
        b201 * 3.0 * w2 * v +
        b021 * 3.0 * u2 * v +
        b102 * 3.0 * w * v2 +
        b012 * 3.0 * u * v2 +
        b111 * 6.0 * w * u * v;
    gl_Position = vec4(position, 1.0);
}

void interpolateNormalComponent(){
    vec3 n200 = tcsNormals[0];
    vec3 n020 = tcsNormals[1];
    vec3 n002 = tcsNormals[2];

    vec3 n110 = normalize(vec3(tcsPatches[0].n110, tcsPatches[1].n110, tcsPatches[2].n110));
    vec3 n011 = normalize(vec3(tcsPatches[0].n011, tcsPatches[1].n011, tcsPatches[2].n011));
    vec3 n101 = normalize(vec3(tcsPatches[0].n101, tcsPatches[1].n101, tcsPatches[2].n101));

    tesNormal = normalize(n200 * w2 + n020 * u2 + n002 * v2 +
        n110 * w * u + n011 * u * v + n101 * w * v);
}

void main(void)
{
//     gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +
//                       (gl_TessCoord.y * gl_in[1].gl_Position) +
//                       (gl_TessCoord.z * gl_in[2].gl_Position);

    interpolateGeometricComponent();
    interpolateNormalComponent();
}

