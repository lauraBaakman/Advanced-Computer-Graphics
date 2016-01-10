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

//Variable in
layout (triangles) in;

layout(location = 0) in vec3 tcsNormals[];
layout(location = 3) in pnPatch tcsPatches[];

//Variable out
//in vec3 vColor[3];

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

float u = gl_TessCoord.x;
float v = gl_TessCoord.y;
float w = gl_TessCoord.z;


void main(void)
{
    //Maak een functie!
    float u2 = u * u;
    float u3 = u2 * u;
    float v2 = v * v;
    float v3 = v2 * v;
    float w2 = w * w;
    float w3 = w2 * w;

//     gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +
//                       (gl_TessCoord.y * gl_in[1].gl_Position) +
//                       (gl_TessCoord.z * gl_in[2].gl_Position);

    vec3 position = b300 * w3 + b030 * u3 + b003 * v3 +
        b210 * 3.0 * w2 * u +
        b120 * 3.0 * w * u2 +
        b210 * 3.0 * w2 * v +
        b021 * 3.0 * u2 * v +
        b102 * 3.0 * w * v2 +
        b012 * 3.0 * u * v2 +
        b111 * 6.0 * w * u * v;
    gl_Position = vec4(position, 1.0);

}

